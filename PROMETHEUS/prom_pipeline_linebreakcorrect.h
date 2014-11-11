#ifndef		__PROM_PIPELINE_LINEBREAKCORRECT_H__
#define		__PROM_PIPELINE_LINEBREAKCORRECT_H__

namespace PROM
{
	class PL_LineBreakCorrect : public Pipeline
	{
	public:
		GINL PL_LineBreakCorrect(){}
		GINL ~PL_LineBreakCorrect(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_LineBreakCorrect");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::STREAM::StreamBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);
			GAIA::CTN::TChars chs;
			PLC_Empty* pRet = GNIL;
			PLC_CommandParam* plc_commandparam = GNIL;
			PLC_File* plc_file = GNIL;
			PLC_FileCodeLine* plc_codeline = GNIL;
			plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNIL)
				goto FUNCTION_END;
			plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
			if(plc_file == GNIL)
				goto FUNCTION_END;
			plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
			if(plc_codeline == GNIL)
				goto FUNCTION_END;

			/* Initialize result pipeline context. */
			pRet = new PLC_Empty;

			/* Execute. */
			for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
			{
				const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
				if(GAIA::ALGO::stremp(pszCmd))
					continue;
				if(GAIA::ALGO::strcmp(pszCmd, _T("-linebreak")) == 0)
				{
					GAIA_AST(plc_commandparam->cmdparam.param_size(x) == 1);
					if(plc_commandparam->cmdparam.param_size(x) == 1)
					{
						chs = plc_commandparam->cmdparam.param(x, 0);
						break;
					}
				}
			}
			if(chs == _T("\\r\\n"))
				chs = _T(GAIA_FILELINEBREAK_RN);
			else if(chs == _T("\\n"))
				chs = _T(GAIA_FILELINEBREAK_N);
			else if(chs == _T("\\r"))
				chs = _T(GAIA_FILELINEBREAK_R);
			else
				chs.clear();
			if(!chs.empty())
			{
				GAIA::SIZE remove_rn = 0;
				GAIA::SIZE remove_n = 0;
				GAIA::SIZE remove_r = 0;
				GAIA::SIZE add = 0;
				GAIA::SIZE old_remove_rn = 0;
				GAIA::SIZE old_remove_n = 0;
				GAIA::SIZE old_remove_r = 0;
				GAIA::SIZE old_add = 0;
				GAIA::SIZE need_save = 0;
				DWARFS_MISC::TextLine::__LineType strTemp;
				for(GAIA::SIZE x = 0; x < plc_codeline->file_codelines_list.size(); ++x)
				{
					PLC_FileCodeLine::__FileCodelinesList::_datatype& t = plc_codeline->file_codelines_list[x];
					GAIA::BL bNeedSave = GAIA::False;
					for(GAIA::SIZE y = 0; y < t.lines.size(); ++y)
					{
						strTemp = t.lines.get_line(y);
						GAIA_AST(!strTemp.empty());
						if(strTemp.empty())
							continue;

						old_remove_rn = remove_rn;
						old_remove_n = remove_n;
						old_remove_r = remove_r;
						old_add = add;

						GAIA::BL bExistValidFlag = GAIA::False;
						if(strTemp.size () >= chs.size())
						{
							if(strTemp.rfind(GCCAST(const GAIA::TCH*)(chs.front_ptr()), strTemp.size() - 1) !=
								strTemp.size() - chs.size())
								++add;
							else
							{
								if(chs == _T("\n"))
								{
									if(strTemp.size() >= 2)
									{
										if(strTemp[strTemp.size() - 2] == _T('\r') &&
											strTemp[strTemp.size() - 1] == _T('\n'))
											++add;
										else
											bExistValidFlag = GAIA::True;
									}
									else
										bExistValidFlag = GAIA::True;
								}
								else
									bExistValidFlag = GAIA::True;
							}
						}
						else
							++add;

						remove_rn += strTemp.replace(_T(GAIA_FILELINEBREAK_RN), _T(""));
						remove_n += strTemp.replace(_T(GAIA_FILELINEBREAK_N), _T(""));
						remove_r += strTemp.replace(_T(GAIA_FILELINEBREAK_R), _T(""));
						strTemp += chs.front_ptr();

						if(bExistValidFlag)
						{
							if(chs == _T(GAIA_FILELINEBREAK_RN))
								--remove_rn;
							if(chs == _T(GAIA_FILELINEBREAK_N))
								--remove_n;
							if(chs == _T(GAIA_FILELINEBREAK_R))
								--remove_r;
						}
						t.lines.set_line(y, strTemp);

						if(remove_rn != old_remove_rn ||
							remove_n != old_remove_n ||
							remove_r != old_remove_r ||
							add != old_add)
							bNeedSave = GAIA::True;
					}
					if(bNeedSave)
					{
						plc_file->filelist[x].bNeedSave = GAIA::True;
						++need_save;
					}
				}

				GAIA::CTN::TChars tempchs;
				if(chs == _T(GAIA_FILELINEBREAK_RN))
					tempchs = _T("\\r\\n");
				else if(chs == _T(GAIA_FILELINEBREAK_N))
					tempchs = _T("\\n");
				else if(chs == _T(GAIA_FILELINEBREAK_R))
					tempchs = _T("\\r");
				else
					tempchs = _T("(InvalidCharacter)");
				prt << "\t\tAdd " << tempchs.front_ptr() << "=" << add << ".\n";
				prt << "\t\tRemove \\r\\n=" << remove_rn << ", \\n=" << remove_n << ", \\r=" << remove_r << ".\n";
				prt << "\t\tChange " << need_save << " files.\n";
			}

			/* Release. */
		FUNCTION_END:
			if(plc_commandparam != GNIL)
				plc_commandparam->Release();
			if(plc_file != GNIL)
				plc_file->Release();
			if(plc_codeline != GNIL)
				plc_codeline->Release();
			return pRet;
		}
	};
};

#endif