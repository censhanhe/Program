#ifndef		__PROM_PIPELINE_LINEPREPARE_H__
#define		__PROM_PIPELINE_LINEPREPARE_H__

namespace PROM
{
	class PL_LinePrepare : public Pipeline
	{
	public:
		GINL PL_LinePrepare(){}
		GINL ~PL_LinePrepare(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_LinePrepare");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);

			GAIA::CTN::Vector<GAIA::BL> listEraseTemp;
			DWARFS_MISC::TextLine::__LineType strLine, strLineTemp;
			PLC_FileCodeLinePrepare* pRet = GNIL;
			PLC_CommandParam* plc_commandparam = GNIL;
			PLC_FileCodeLine* plc_codeline = GNIL;
			plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNIL)
				goto FUNCTION_END;
			plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
			if(plc_codeline == GNIL)
				goto FUNCTION_END;

			/* Initialize result pipeline context. */
			pRet = new PLC_FileCodeLinePrepare;
			pRet->file_codelines_list = plc_codeline->file_codelines_list;
			for(GAIA::SIZE x = 0; x < pRet->file_codelines_list.size(); ++x)
				pRet->file_codelines_list[x].lines.enable_checkline(GAIA::False);

			/* Execute. */
			for(GAIA::SIZE x = 0; x < pRet->file_codelines_list.size(); ++x)
			{
				PLC_FileCodeLine::FileCodeLines& fcl = pRet->file_codelines_list[x];
				GAIA::BL bInString = GAIA::False;
				GAIA::BL bInMultiLineComment = GAIA::False;
				for(GAIA::SIZE y = 0; y < fcl.lines.size(); ++y)
				{
					strLine = strLineTemp = fcl.lines.get_line(y);
					listEraseTemp.resize(strLineTemp.size());
					listEraseTemp.reset(GAIA::False);
					GAIA::BL bInSingleLineComment = GAIA::False;
					GAIA::BL bSign = GAIA::True;
					GAIA::SIZE sLastNotBlankIndex = GINVALID;
					for(GAIA::SIZE z = 0; z < strLineTemp.size(); ++z)
					{
						DWARFS_MISC::TextLine::__CharType ch = strLineTemp[z];
						if(bInMultiLineComment)
						{
							if(ch == _T('/') && (z > 0 && strLineTemp[z - 1] == _T('*')))
							{
								bInMultiLineComment = GAIA::False;
								bSign = GAIA::True;
								sLastNotBlankIndex = z;
							}
							listEraseTemp[z] = GAIA::True; // Erase the multi line comment.
							continue;
						}
						if(bInSingleLineComment)
						{
							if(z + 1 == strLineTemp.size())
							{
								bInSingleLineComment = GAIA::False;
								bSign = GAIA::True;
								sLastNotBlankIndex = z;
							}
							listEraseTemp[z] = GAIA::True; // Erase the single line comment.
							continue;
						}
						if(bInString)
						{
							if(ch == _T('"'))
							{
								GAIA::SIZE flagcount = 0;
								GAIA::ALGO::prevcount(strLineTemp.front_ptr(), strLineTemp.front_ptr() + z - 1, _T('\\'), flagcount);
								if(z == 0 || flagcount % 2 == 0)
								{
									bInString = GAIA::False;
									bSign = GAIA::True;
									sLastNotBlankIndex = z;
								}
							}
							continue;
						}
						if(!PROM::is_blank_char(ch))
						{
							if(PROM::is_word_char(ch))
							{
								if(bSign)
								{
									if(z > sLastNotBlankIndex + 1)
									{
										GAIA::ALGO::set(
											listEraseTemp.front_ptr() + sLastNotBlankIndex + 1,
											GAIA::True,
											z - sLastNotBlankIndex - 1); // Erase blank between sign and word.
									}
								}
								else
								{
									if(z > sLastNotBlankIndex + 2)
									{
										GAIA::ALGO::set(
											listEraseTemp.front_ptr() + sLastNotBlankIndex + 2,
											GAIA::True,
											z - sLastNotBlankIndex - 2); // Erase blank between word and word.
									}
								}
								bSign = GAIA::False;
							}
							else
							{
								if(z > sLastNotBlankIndex + 1)
								{
									GAIA::ALGO::set(
										listEraseTemp.front_ptr() + sLastNotBlankIndex + 1,
										GAIA::True,
										z - sLastNotBlankIndex - 1); // Erase blank between sign and word or between sign and sign.
								}
								bSign = GAIA::True;
							}
							sLastNotBlankIndex = z;
						}
						if(ch == _T('/'))
						{
							if(z + 1 < strLineTemp.size())
							{
								if(strLineTemp[z + 1] == _T('/'))
								{
									listEraseTemp[z] = GAIA::True; // Erase the single line comment head.
									bInSingleLineComment = GAIA::True;
								}
								else if(strLineTemp[z + 1] == _T('*'))
								{
									listEraseTemp[z] = GAIA::True; // Erase the multi line comment head.
									bInMultiLineComment = GAIA::True;
								}
							}
						}
						if(ch == _T('"'))
							bInString = GAIA::True;
					}
					for(GAIA::SIZE z = 0; z < strLineTemp.size(); ++z)
					{
						if(strLineTemp[z] == _T('\r') || strLineTemp[z] == _T('\n'))
							listEraseTemp[z] = GAIA::True;
					}
					GAIA_AST(listEraseTemp.size() == strLine.size());
					GAIA_AST(listEraseTemp.size() == strLineTemp.size());
					GAIA::SIZE sWriteIndex = 0;
					for(GAIA::SIZE z = 0; z < strLineTemp.size(); ++z)
					{
						if(listEraseTemp[z])
							continue;
						strLine[sWriteIndex++] = strLineTemp[z];
					}
					strLine.resize(sWriteIndex);
					if(strLine != fcl.lines.get_line(y))
						fcl.lines.set_line(y, strLine);
				}
				GAIA_AST(!bInString);
			}

		FUNCTION_END:
			if(plc_commandparam != GNIL)
				plc_commandparam->Release();
			if(plc_codeline != GNIL)
				plc_codeline->Release();
			return pRet;
		}
		virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FSYS::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
		{
			/* Parameter check up. */
			GAIA_AST(pPLC != GNIL);
			if(pPLC == GNIL)
				return GAIA::False;

			GAIA_AST(!GAIA::ALGO::stremp(pPLC->GetName()));
			if(GAIA::ALGO::stremp(pPLC->GetName()))
				return GAIA::False;

			PLC_FileCodeLinePrepare* plc_filecodelineprepare = static_cast<PLC_FileCodeLinePrepare*>(pPLC);
			if(plc_filecodelineprepare == GNIL)
				return GAIA::False;
			if(GAIA::ALGO::strcmp(pPLC->GetName(), _T("Prom:PLC_FileCodeLinePrepare")) != 0)
				return GAIA::False;

			for(GAIA::SIZE x = 0; x < plc_filecodelineprepare->file_codelines_list.size(); ++x)
			{
				PLC_FileCodeLine::FileCodeLines& fcl = plc_filecodelineprepare->file_codelines_list[x];
				for(GAIA::SIZE y = 0; y < fcl.lines.size(); ++y)
				{
					const DWARFS_MISC::TextLine::__CharType* pszLine = fcl.lines.get_line(y);
					if(pszLine == GNIL)
						continue;
					if(pszLine[0] != _T('\0'))
						pFile->Write(pszLine, GAIA::ALGO::strlen(pszLine) * sizeof(DWARFS_MISC::TextLine::__CharType));
					pFile->Write(fcl.lines.lineflag(), GAIA::ALGO::strlen(fcl.lines.lineflag()) * sizeof(DWARFS_MISC::TextLine::__CharType));
				}
			}

			return GAIA::True;
		}
	};
};

#endif