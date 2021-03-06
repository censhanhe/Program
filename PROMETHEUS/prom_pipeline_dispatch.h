#ifndef		__PROM_PIPELINE_DISPATCH_H__
#define		__PROM_PIPELINE_DISPATCH_H__

namespace PROM
{
	class PipelineDispatch : public GAIA::RefObject
	{
	public:
		GINL PipelineDispatch(){this->init();}
		GINL ~PipelineDispatch(){}
		GINL GAIA::GVOID Run(
			Pipeline** ppPrevPL, const GAIA::SIZE& prevpl_size,
			Pipeline** ppNextPL, const GAIA::SIZE& nextpl_size,
			PipelineContext** ppPLC, const GAIA::SIZE& plc_size,
			GAIA::STREAM::StreamBase& stm, __ErrorListType& errs)
		{
			/* Internal type. */
			typedef GAIA::CTN::Vector<Pipeline*> __PipelineList;
			typedef GAIA::CTN::Vector<PipelineContext*> __PipelineContextList;

			/* Check parameter. */
			GPCHR_NULL(ppNextPL);
			GPCHR_ZERO(nextpl_size);
			GPCHR_NULL(ppPLC);
			GPCHR_ZERO(plc_size);

			if(ppPrevPL == GNIL)
			{
				GAIA_AST(prevpl_size == 0);
				if(prevpl_size != 0)
					return;
			}
			else
			{
				GAIA_AST(prevpl_size != 0);
				if(prevpl_size == 0)
					return;
			}
			for(GAIA::SIZE x = 0; x < prevpl_size; ++x)
			{
				GAIA_AST(ppPrevPL[x] != GNIL);
				if(ppPrevPL[x] == GNIL)
					return;
			}
			for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
			{
				GAIA_AST(ppNextPL[x] != GNIL);
				if(ppNextPL[x] == GNIL)
					return;
			}

			/* Dispatch current layer. */
			__PipelineContextList plc_list;
			__PipelineContextList new_plc_list;
			plc_list.reserve(prevpl_size);
			new_plc_list.reserve(prevpl_size);
			for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
			{
				Pipeline* pTempPL = ppNextPL[x];
				GAIA::SIZE uPracPrevSize = 0;
				for(GAIA::SIZE y = 0; y < pTempPL->GetPrevSize(); ++y)
				{
					Pipeline* pTempPrevPL = dynamic_cast<Pipeline*>(pTempPL->GetPrev(y));
					if(pTempPrevPL == GNIL)
						continue;
					pTempPrevPL->Release();
					++uPracPrevSize;
				}
				if(uPracPrevSize == 0)
				{
					stm << "\n\tPipeline Stage : " << pTempPL->GetName() << "\n";
					GAIA::U64 uStartTick = GAIA::TIME::tick_time();
					PipelineContext* pNewPLC = pTempPL->Execute(ppPLC, plc_size, stm, errs);
					GAIA::U64 uEndTick = GAIA::TIME::tick_time();
					stm << "\t\tTimeLost : " << GSCAST(GAIA::F64)(uEndTick - uStartTick) / 1000.0 / 1000.0 << "\n";
					if(pNewPLC == GNIL)
						PROM_RAISE_FATALERROR(101);
					else
					{
						this->ExecuteOutput(pNewPLC, pTempPL, stm, errs);
						this->ExecuteExportTempResult(ppPLC, plc_size, pNewPLC, pTempPL, stm, errs);
						for(GAIA::SIZE y = 0; y < plc_size; y++)
						{
							if(ppPLC[y] == GNIL)
								continue;
							ppPLC[y]->BindNext(pNewPLC);
						}
					}
					new_plc_list.push_back(pNewPLC);
				}
				else
				{
					plc_list.clear();
					GAIA::BL bExecuteAble = GAIA::True;
					for(GAIA::SIZE y = 0; y < pTempPL->GetPrevSize(); ++y)
					{
						Pipeline* pTempPrevPL = dynamic_cast<Pipeline*>(pTempPL->GetPrev(y));
						if(pTempPrevPL == GNIL)
							continue;
						GAIA::BL bFindedMatchedPLC = GAIA::False;
						for(GAIA::SIZE z = 0; z < prevpl_size; ++z)
						{
							if(ppPrevPL[z] == pTempPrevPL)
							{
								plc_list.push_back(ppPLC[z]);
								bFindedMatchedPLC = GAIA::True;
								break;
							}
						}
						pTempPrevPL->Release();
						if(!bFindedMatchedPLC)
						{
							PROM_RAISE_FATALERROR(103);
							bExecuteAble = GAIA::False;
							break;
						}
					}
					stm << "\n\tPipeline Stage : " << pTempPL->GetName() << "\n";
					GAIA::U64 uStartTick = GAIA::TIME::tick_time();
					PipelineContext* pNewPLC = pTempPL->Execute(plc_list.front_ptr(), plc_list.size(), stm, errs);
					GAIA::U64 uEndTick = GAIA::TIME::tick_time();
					stm << "\t\tTimeLost : " << GSCAST(GAIA::F64)(uEndTick - uStartTick) / 1000.0 / 1000.0 << "\n";
					if(pNewPLC == GNIL)
						PROM_RAISE_FATALERROR(101);
					else
					{
						this->ExecuteOutput(pNewPLC, pTempPL, stm, errs);
						this->ExecuteExportTempResult(plc_list.front_ptr(), plc_list.size(), pNewPLC, pTempPL, stm, errs);
						for(GAIA::SIZE y = 0; y < plc_size; y++)
						{
							if(ppPLC[y] == GNIL)
								continue;
							ppPLC[y]->BindNext(pNewPLC);
						}
					}
					new_plc_list.push_back(pNewPLC);
				}
			}

			/* Dispatch next layer. */
			__PipelineList pl_list;
			for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
			{
				for(GAIA::SIZE y = 0; y < ppNextPL[x]->GetNextSize(); ++y)
				{
					Pipeline* pTempNext = dynamic_cast<Pipeline*>(ppNextPL[x]->GetNext(y));
					if(pTempNext == GNIL)
						continue;
					pl_list.push_back(pTempNext);
				}
			}
			if(pl_list.size() != 0)
			{
				this->Run(ppNextPL, nextpl_size,
					pl_list.front_ptr(), pl_list.size(),
					new_plc_list.front_ptr(), new_plc_list.size(),
					stm, errs);
			}
			for(GAIA::SIZE x = 0; x < pl_list.size(); ++x)
				pl_list[x]->Release();

			/* Release new pipeline context. */
			for(GAIA::SIZE x = 0; x < new_plc_list.size(); ++x)
			{
				if(new_plc_list[x] != GNIL)
				{
					new_plc_list[x]->UnbindPrevAll();
					new_plc_list[x]->UnbindNextAll();
					new_plc_list[x]->Release();
				}
			}
		}
	private:
		GINL GAIA::GVOID init()
		{
			m_plc_commandparam = GNIL;
		}
		GINL GAIA::GVOID ExecuteOutput(PipelineContext* pPLC, Pipeline* pPL, GAIA::STREAM::StreamBase& stm, __ErrorListType& errs)
		{
			GAIA_AST(!GAIA::ALGO::stremp(pPLC->GetName()));
			if(!GAIA::ALGO::stremp(pPLC->GetName()))
			{
				if(GAIA::ALGO::strcmp(pPLC->GetName(), _T("Prom:PLC_CommandParam")) == 0)
					m_plc_commandparam = static_cast<PLC_CommandParam*>(pPLC);
			}
			if(m_plc_commandparam != GNIL)
			{
				for(GAIA::SIZE y = 0; y < m_plc_commandparam->cmdparam.cmd_size(); ++y)
				{
					const GAIA::TCH* pszCmd = m_plc_commandparam->cmdparam.cmd(y);
					if(GAIA::ALGO::stremp(pszCmd))
						continue;
					if(GAIA::ALGO::strcmp(pszCmd, _T("-o")) == 0)
					{
						if(m_plc_commandparam->cmdparam.param_size(y) == 2)
						{
							const GAIA::TCH* pszParam0 = m_plc_commandparam->cmdparam.param(y, 0);
							const GAIA::TCH* pszParam1 = m_plc_commandparam->cmdparam.param(y, 1);
							GAIA_AST(!GAIA::ALGO::stremp(pszParam0));
							GAIA_AST(!GAIA::ALGO::stremp(pszParam1));
							if(!GAIA::ALGO::stremp(pszParam0) && !GAIA::ALGO::stremp(pszParam1))
							{
								if(GAIA::ALGO::strcmp(pszParam0, pPL->GetName()) == 0)
								{
									GAIA::FSYS::File ofile;
									if(ofile.Open(pszParam1, GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS | GAIA::FSYS::File::OPEN_TYPE_WRITE))
									{
										if(pPL->Output(pPLC, &ofile, stm))
											stm << "\t\tOutput " << pPL->GetName() << " successfully!\n";
										else
											PROM_RAISE_FATALERROR(104);
									}
									else
										PROM_RAISE_FATALERROR(503);
								}
							}
						}
						else if(m_plc_commandparam->cmdparam.param_size(y) == 1)
						{
							const GAIA::TCH* pszParam0 = m_plc_commandparam->cmdparam.param(y, 0);
							GAIA_AST(!GAIA::ALGO::stremp(pszParam0));
							if(!GAIA::ALGO::stremp(pszParam0))
							{
								if(GAIA::ALGO::strcmp(pszParam0, pPL->GetName()) == 0)
								{
									if(pPL->Output(pPLC, GNIL, stm))
										stm << "\t\tOutput " << pPL->GetName() << " successfully!\n";
									else
										PROM_RAISE_FATALERROR(104);
								}
							}
						}
						else
							GAIA_AST(GAIA::ALWAYSFALSE);
					}
				}
			}
		}
		GINL GAIA::GVOID ExecuteExportTempResult(PipelineContext** ppPLC, const GAIA::SIZE& plc_size, PipelineContext* pNewPLC, Pipeline* pPL, GAIA::STREAM::StreamBase& stm, __ErrorListType& errs)
		{
			GPCHR_NULL(ppPLC);
			GPCHR_ZERO(plc_size);
			GPCHR_NULL(pNewPLC);
			GPCHR_NULL(pPL);

			PLC_CommandParam* plc_commandparam = GNIL;
			PLC_File* plc_file = GNIL;
			PLC_FileCodeLinePrepare* plc_codelineprepare = GNIL;
			plc_commandparam = static_cast<PLC_CommandParam*>(pPL->GetPLCByName(ppPLC, plc_size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNIL)
				goto FUNCTION_END;
			plc_file = static_cast<PLC_File*>(pPL->GetPLCByName(ppPLC, plc_size, _T("Prom:PLC_File")));
			if(plc_file == GNIL)
				goto FUNCTION_END;
			plc_codelineprepare = static_cast<PLC_FileCodeLinePrepare*>(pPL->GetPLCByName(ppPLC, plc_size, _T("Prom:PLC_FileCodeLinePrepare")));
			if(plc_codelineprepare == GNIL)
			{
				if(GAIA::ALGO::strcmp(pNewPLC->GetName(), _T("Prom:PLC_FileCodeLinePrepare")) == 0)
					plc_codelineprepare = GSCAST(PLC_FileCodeLinePrepare*)(pNewPLC);
			}
			if(plc_codelineprepare == GNIL)
				goto FUNCTION_END;

			/* Execute. */
			const GAIA::TCH* pszExportPath = GNIL;
			GAIA::BL bMatch = GAIA::False;
			for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
			{
				const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
				if(GAIA::ALGO::stremp(pszCmd))
					continue;
				if(GAIA::ALGO::strcmp(pszCmd, _T("-export")) == 0)
				{
					const GAIA::TCH* pszPLName = plc_commandparam->cmdparam.param(x, 0);
					if(GAIA::ALGO::stremp(pszPLName))
						continue;
					if(GAIA::ALGO::strcmp(pszPLName, pPL->GetName()) != 0)
						continue;
					pszExportPath = plc_commandparam->cmdparam.param(x, 1);
					if(pszExportPath == GNIL)
						continue;
					bMatch = GAIA::True;
					break;
				}
			}
			if(bMatch)
			{
				GAIA::TCH szPath[GAIA::FSYS::MAXPL];
				GAIA::ALGO::strcpy(szPath, pszExportPath);
				GAIA::TCH* pszEnd = GAIA::ALGO::strend(szPath);
				if(pszEnd != GNIL && *(pszEnd - 1) != '\\' && *(pszEnd - 1) != '/')
				{
					*pszEnd = '/';
					*(pszEnd + 1) = '\0';
				}
				GAIA::FSYS::Directory dir;
				if(dir.Exist(szPath) || dir.Create(szPath, GAIA::True))
				{
					for(GAIA::SIZE x = 0; x < plc_codelineprepare->file_codelines_list.size(); ++x)
					{
						DWARFS_MISC::TextLine& l = plc_codelineprepare->file_codelines_list[x].lines;
						__FileName fname = plc_file->filelist[x].name;
						GAIA_AST(!fname.empty());
						if(fname.empty())
							continue;
						fname.replace(_T("\\..\\"), _T("\\prev\\"));
						fname.replace(_T("..\\"), _T("prev\\"));
						fname.replace(_T("\\.."), _T("\\prev"));
						fname.replace(_T("/../"), _T("/prev/"));
						fname.replace(_T("../"), _T("prev/"));
						fname.replace(_T("/.."), _T("/prev"));
						fname.replace(_T(":\\"), _T("_disk\\"));
						fname.replace(_T(":/"), _T("_disk/"));

						GAIA::TCH szFinal[GAIA::FSYS::MAXPL];
						GAIA::ALGO::strcpy(szFinal, szPath);
						GAIA::ALGO::strcat(szFinal, fname.front_ptr());

						GAIA::TCH szFinalPath[GAIA::FSYS::MAXPL];
						GAIA::ALGO::strcpy(szFinalPath, szFinal);
						GAIA::ALGO::strpath(szFinalPath);

						if(!dir.Exist(szFinalPath) && !dir.Create(szFinalPath, GAIA::True))
						{
							PROM_RAISE_FILEERROR(506, szFinalPath);
							break;
						}

						GAIA::FSYS::File file;
						if(!file.Open(szFinal, GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS | GAIA::FSYS::File::OPEN_TYPE_WRITE))
						{
							PROM_RAISE_FILEERROR(503, szFinal);
							break;
						}
						DWARFS_MISC::TextFile textfile;
						textfile.charset_type(GAIA::CHARSET_TYPE_UTF16LE);
						DWARFS_MISC::TextFile::__StringType& strTextFile = textfile.get_string();
						for(GAIA::SIZE x = 0; x < l.size(); ++x)
						{
							strTextFile += l.get_line(x);
							strTextFile += FILEBREAK;
						}
						if(!textfile.save(file))
						{
							PROM_RAISE_FILEERROR(503, szFinal);
							break;
						}
					}
				}
				else
					PROM_RAISE_FILEERROR(506, szPath);
			}

		FUNCTION_END:
			if(plc_commandparam != GNIL)
				plc_commandparam->Release();
			if(plc_file != GNIL)
				plc_file->Release();
			if(plc_codelineprepare != GNIL && plc_codelineprepare != pNewPLC)
				plc_codelineprepare->Release();
		}
	private:
		PLC_CommandParam* m_plc_commandparam;
	};
};

#endif