#ifndef		__PROM_PIPELINE_WORDSTAT_H__
#define		__PROM_PIPELINE_WORDSTAT_H__

namespace PROM
{
	class PL_WordStat : public Pipeline
	{
	public:
		GINL PL_WordStat(){}
		GINL ~PL_WordStat(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_WordStat");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNULL);
			GPCHR_ZERO_RET(size, GNULL);

			PLC_Word* pRet = GNULL;
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
			pRet = new PLC_Word;

			/* Execute. */
			GAIA::BL bWordStat = GAIA::False;
			for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
			{
				const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
				if(GAIA::ALGORITHM::stremp(pszCmd))
					continue;
				if(GAIA::ALGORITHM::strcmp(pszCmd, _T("-wordstat")) == 0)
				{
					bWordStat = GAIA::True;
					break;
				}
			}
			if(bWordStat)
			{
				DWARFS_MISC::TextLine::__LineType strLine;
				PLC_Word::Word word;
				for(GAIA::SIZE x = 0; x < plc_codeline->file_codelines_list.size(); ++x)
				{
					DWARFS_MISC::TextLine& l = plc_codeline->file_codelines_list[x].lines;
					for(GAIA::SIZE y = 0; y < l.size(); ++y)
					{
						strLine = l.get_line(y);
						if(strLine.empty())
							continue;
						static const GAIA::SIZE EMPTY_FLAG = 0;
						static const GAIA::SIZE CHAR_FLAG = 1;
						static const GAIA::SIZE SIGN_FLAG = 2;
						GAIA::SIZE lastflag = EMPTY_FLAG;
						GAIA::SIZE flag_changed_index = 0;
						for(GAIA::SIZE z = 0; z < strLine.size(); ++z)
						{
							GAIA::SIZE newflag;
							if(strLine[z] == _T('\t') || strLine[z] == _T(' ') || strLine[z] == _T('\r') || strLine[z] == _T('\n'))
								newflag = EMPTY_FLAG;
							else if(
								GAIA::ALGORITHM::isalpha(strLine[z]) ||
								GAIA::ALGORITHM::isdigit(strLine[z]) ||
								strLine[z] == _T('_') ||
								strLine[z] == _T('.') && z + 1 < strLine.size() && GAIA::ALGORITHM::isdigit(strLine[z + 1]))
								newflag = CHAR_FLAG;
							else
								newflag = SIGN_FLAG;

							if(newflag != lastflag)
							{
								if(lastflag != EMPTY_FLAG)
								{
									word.strWord = strLine;
									word.strWord.mid(flag_changed_index, z > flag_changed_index ? z - 1 : z);
									PLC_Word::Word* pWord = pRet->wordset.find(word);
									if(pWord == GNULL)
									{
										word.uExistCount = 1;
										pRet->wordset.insert(word);
									}
									else
										++pWord->uExistCount;
								}
								lastflag = newflag;
								flag_changed_index = z;
							}
							else
							{
								if(lastflag == SIGN_FLAG)
								{
									if(z != flag_changed_index)
									{
										static const GAIA::TCH* LINK_SIGN_LIST[] =
										{
											_T(">>"), _T("<<"),
											_T("++"), _T("--"),
											_T("+="), _T("-="), _T("*="), _T("/="),
											_T("=="), _T("!="), _T(">="), _T("<=")
										};
										GAIA::BL bLink = GAIA::False;
										for(GAIA::SIZE t = 0; t < sizeofarray(LINK_SIGN_LIST); ++t)
										{
											if(strLine[flag_changed_index] == LINK_SIGN_LIST[t][0] &&
												strLine[z] == LINK_SIGN_LIST[t][1])
											{
												bLink = GAIA::True;
												break;
											}
										}
										if(!bLink)
										{
											word.strWord = strLine;
											word.strWord.mid(flag_changed_index, z > flag_changed_index ? z - 1 : z);
											PLC_Word::Word* pWord = pRet->wordset.find(word);
											if(pWord == GNULL)
											{
												word.uExistCount = 1;
												pRet->wordset.insert(word);
											}
											else
												++pWord->uExistCount;
											flag_changed_index = z;
										}
									}
								}
							}
						}
					}
				}
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
		virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
		{
			/* Parameter check up. */
			GAIA_AST(pPLC != GNULL);
			if(pPLC == GNULL)
				return GAIA::False;

			GAIA_AST(!GAIA::ALGORITHM::stremp(pPLC->GetName()));
			if(GAIA::ALGORITHM::stremp(pPLC->GetName()))
				return GAIA::False;

			PLC_Word* plc_word = static_cast<PLC_Word*>(pPLC);
			if(plc_word == GNULL)
				return GAIA::False;
			if(GAIA::ALGORITHM::strcmp(pPLC->GetName(), _T("Prom:PLC_Word")) != 0)
				return GAIA::False;
			if(pFile != GNULL && pFile->Tell() == 0)
			{
			#if GAIA_CHARSET == GAIA_CHARSET_UNICODE
				pFile->Write(GAIA::UTF16LE_FILEHEAD, sizeof(GAIA::UTF16LE_FILEHEAD));
			#endif
			}
			GAIA::SIZE index = 0;
			PLC_Word::__WordSetType::it it = plc_word->wordset.front_it();
			while(!it.empty())
			{
				PLC_Word::Word& word = *it;
				if(pFile != GNULL)
				{
					GAIA::TCH szTemp[32];
					GAIA::ALGORITHM::int2str(index++, szTemp);
					pFile->Write(_T("["), sizeof(GAIA::TCH));
					pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp) * sizeof(GAIA::TCH));
					pFile->Write(_T("] \""), sizeof(GAIA::TCH) * 3);
					pFile->Write(word.strWord.front_ptr(), word.strWord.size() * sizeof(__WordType::_datatype));
					pFile->Write(_T("\", Count = "), sizeof(_T("\", Count = ")) - sizeof(GAIA::TCH));
					GAIA::ALGORITHM::int2str(word.uExistCount, szTemp);
					pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp) * sizeof(GAIA::TCH));
					pFile->Write(FILEBREAK, GAIA::ALGORITHM::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
				}
				else
					prt << "[" << index++ << "] \"" << word.strWord.front_ptr() << "\", Count = " << word.uExistCount << "\n";
				++it;
			}

			typedef GAIA::CONTAINER::Vector<WordByRefCount> __WordCountSortVectorType;
			__WordCountSortVectorType wordcountsortlist;
			it = plc_word->wordset.front_it();
			while(!it.empty())
			{
				PLC_Word::Word& word = *it;
				WordByRefCount temp;
				temp.pWord = &word.strWord;
				temp.uExistCount = word.uExistCount;
				wordcountsortlist.push_back(temp);
				++it;
			}
			wordcountsortlist.sort();

			index = 0;
			__WordCountSortVectorType::it itcountsort = wordcountsortlist.front_it();
			while(!itcountsort.empty())
			{
				WordByRefCount& word = *itcountsort;
				if(pFile != GNULL)
				{
					GAIA::TCH szTemp[32];
					GAIA::ALGORITHM::int2str(index++, szTemp);
					pFile->Write(_T("["), sizeof(GAIA::TCH));
					pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp) * sizeof(GAIA::TCH));
					pFile->Write(_T("] \""), sizeof(GAIA::TCH) * 3);
					pFile->Write(word.pWord->front_ptr(), word.pWord->size() * sizeof(__WordType::_datatype));
					pFile->Write(_T("\", Count = "), sizeof(_T("\", Count = ")) - sizeof(GAIA::TCH));
					GAIA::ALGORITHM::int2str(word.uExistCount, szTemp);
					pFile->Write(szTemp, GAIA::ALGORITHM::strlen(szTemp) * sizeof(GAIA::TCH));
					pFile->Write(FILEBREAK, GAIA::ALGORITHM::strlen(FILEBREAK) * sizeof(FILEBREAK[0]));
				}
				else
					prt << "[" << index++ << "] \"" << word.pWord->front_ptr() << "\", Count = " << word.uExistCount << "\n";
				++itcountsort;
			}

			return GAIA::True;
		}
	private:
		class WordByRefCount
		{
		public:
			const WordByRefCount& operator = (const WordByRefCount& src)
			{
				pWord = src.pWord;
				uExistCount = src.uExistCount;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE(uExistCount, uExistCount, WordByRefCount);
		public:
			__WordType* pWord;
			GAIA::U32 uExistCount;
		};
	};
};

#endif