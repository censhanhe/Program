#ifndef		__PROM_PIPELINE_FORMAT_H__
#define		__PROM_PIPELINE_FORMAT_H__

namespace PROM
{
	class PL_Format : public Pipeline
	{
	public:
		GINL PL_Format(){}
		GINL ~PL_Format(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_Format");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNULL);
			GPCHR_ZERO_RET(size, GNULL);
			PLC_Empty* pRet = GNULL;
			PLC_CommandParam* plc_commandparam = GNULL;
			PLC_File* plc_file = GNULL;
			PLC_FileCodeLine* plc_codeline = GNULL;
			plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNULL)
				goto FUNCTION_END;
			plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
			if(plc_file == GNULL)
				goto FUNCTION_END;
			plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
			if(plc_codeline == GNULL)
				goto FUNCTION_END;

			/* Initialize result pipeline context. */
			pRet = new PLC_Empty;

			/* Execute. */
			GAIA::BL bFmt = GAIA::False;
			for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
			{
				const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
				if(GAIA::ALGO::stremp(pszCmd))
					continue;
				if(GAIA::ALGO::strcmp(pszCmd, _T("-fmt")) == 0)
				{
					bFmt = GAIA::True;
					break;
				}
			}
			if(bFmt)
			{
				typedef DWARFS_MISC::TextLine::__LineType __LineType;
				__LineType strLine;
				GAIA::SIZE remove_space_count = 0;
				GAIA::SIZE remove_tab_count = 0;
				GAIA::SIZE line_change_count = 0;
				GAIA::SIZE file_change_count = 0;
				for(GAIA::SIZE x = 0; x < plc_codeline->file_codelines_list.size(); ++x)
				{
					GAIA::BL bFileChanged = GAIA::False;
					PLC_FileCodeLine::FileCodeLines& fcl = plc_codeline->file_codelines_list[x];

					/* Line inside based code-format. */
					for(GAIA::SIZE y = 0; y < fcl.lines.size(); ++y)
					{
						strLine = fcl.lines.get_line(y);
						if(strLine.empty())
							continue;
						GAIA::BL bLineChanged = GAIA::False;

						/* Get line break flag. */
						GAIA::TCH szLineBreak[3];
						if(strLine.back() == _T('\n'))
						{
							if(strLine.size() > 1)
							{
								if(strLine[strLine.size() - 2] == _T('\r'))
									GAIA::ALGO::strcpy(szLineBreak, _T("\r\n"));
								else
									GAIA::ALGO::strcpy(szLineBreak, _T("\n"));
							}
							else
								GAIA::ALGO::strcpy(szLineBreak, _T("\n"));
						}
						else if(strLine.back() == _T('\r'))
							GAIA::ALGO::strcpy(szLineBreak, _T("\r"));
						if(GAIA::ALGO::strlen(szLineBreak) == 2)
							strLine.resize(strLine.size() - 2);
						else
							strLine.resize(strLine.size() - 1);

						/* Delete space or tab at line tail. */
						__LineType::it itback = strLine.back_it();
						for(; !itback.empty(); --itback)
						{
							if(*itback != _T(' ') && *itback != _T('\t'))
								break;
							if(*itback == _T(' '))
							{
								++remove_space_count;
								bLineChanged = GAIA::True;
							}
							else if(*itback == _T('\t'))
							{
								++remove_tab_count;
								bLineChanged = GAIA::True;
							}
							GAIA_AST(strLine.size() > 0);
							strLine.resize(strLine.size() - 1);
						}

						/* Remove continuation-space. */
						GAIA::TCH chOld = _T('\0');
						for(GAIA::SIZE z = 0; z < strLine.size(); ++z)
						{
							if(strLine[z] == _T(' '))
							{
								if(chOld == _T(' '))
								{
									strLine.erase_index(z);
									--z;
									++remove_space_count;
									bLineChanged = GAIA::True;
								}
							}
							chOld = strLine[z];
						}

						/* Update the line. */
						if(bLineChanged)
						{
							strLine += szLineBreak;
							fcl.lines.set_line(y, strLine);
							++line_change_count;
							bFileChanged = GAIA::True;
						}
					}

					/* Line outside based code-format. */

					/* Set need save. */
					if(bFileChanged)
					{
						plc_file->filelist[x].bNeedSave = GAIA::True;
						++file_change_count;
					}
				}
				prt << "\t\tCode line formated!" << "\n";
				prt << "\t\tRemove space = " << remove_space_count << ", remove tab = " << remove_tab_count << ".\n";
				prt << "\t\tThere are " << line_change_count << " line changed, and " << file_change_count << " file changed.\n";
			}

		FUNCTION_END:
			if(plc_commandparam != GNULL)
				plc_commandparam->Release();
			if(plc_file != GNULL)
				plc_file->Release();
			if(plc_codeline != GNULL)
				plc_codeline->Release();
			return pRet;
		}
	};
};

#endif