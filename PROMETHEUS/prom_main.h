#ifndef		__PROM_MAIN_H__
#define		__PROM_MAIN_H__

namespace PROM
{
	class Prom : public GAIA::Entity
	{
	public:
		GINL Prom(){}
		GINL ~Prom(){}
		GINL GAIA::BL Command(const GAIA::TCH* psz, GAIA::STREAM::StreamBase& prt)
		{
			GAIA_AST(psz != GNIL);
			if(psz == GNIL)
				return GAIA::False;
			if(*psz == 0)
				return GAIA::False;

			PipelineDispatch* pPLD = new PipelineDispatch;
			PLC_SourceCommand* pPLC = new PLC_SourceCommand; pPLC->pszCmd = psz;
			Pipeline* pPL = this->ConstructPipeline();
			{
				pPLD->Run(GNIL, 0, &pPL, 1, (PipelineContext**)&pPLC, 1, prt, m_errors);
				this->StreamError(prt);
				this->ClearError();
			}
			this->DestructPipeline(pPL); pPL = GNIL;
			pPLC->Release(); pPLC = GNIL;
			pPLD->Release(); pPLD = GNIL;

			return GAIA::True;
		}
	private:
		GINL Pipeline* ConstructPipeline()
		{
			Pipeline* pl_cmdanalyze = new PL_CommandAnalyze;
			{
				PL_Help* pl_help = new PL_Help;
				pl_cmdanalyze->BindNext(pl_help);
				pl_help->Release();

				PL_FileCollect* pl_filecollect = new PL_FileCollect;
				pl_cmdanalyze->BindNext(pl_filecollect);
				{
					PL_LineCollect* pl_linecollect = new PL_LineCollect;
					pl_filecollect->BindNext(pl_linecollect);
					{
						PL_LineBreakCorrect* pl_linebreakcorrect = new PL_LineBreakCorrect;
						pl_linecollect->BindNext(pl_linebreakcorrect);
						pl_linebreakcorrect->Release();

						PL_Format* pl_format = new PL_Format;
						pl_linecollect->BindNext(pl_format);
						pl_format->Release();

						PL_WordStat* pl_wordstat = new PL_WordStat;
						pl_linecollect->BindNext(pl_wordstat);
						pl_wordstat->Release();

						PL_LineStat* pl_linestat = new PL_LineStat;
						pl_linecollect->BindNext(pl_linestat);
						pl_linestat->Release();

						PL_LinePrepare* pl_lineprepare = new PL_LinePrepare;
						pl_linecollect->BindNext(pl_lineprepare);
						pl_lineprepare->Release();
						{
							PL_FileStructureAnalyze* pl_filestructureanalyze = new PL_FileStructureAnalyze;
							pl_lineprepare->BindNext(pl_filestructureanalyze);
							pl_filestructureanalyze->Release();

							PL_ObjAnalyzeBase* pl_objanalyzebase = new PL_ObjAnalyzeBase;
							pl_lineprepare->BindNext(pl_objanalyzebase);
							pl_objanalyzebase->Release();
							{
								PL_ObjAnalyzeUnwrapMacro* pl_objanalyzeunwrapmacro = new PL_ObjAnalyzeUnwrapMacro;
								pl_objanalyzebase->BindNext(pl_objanalyzeunwrapmacro);
								pl_objanalyzeunwrapmacro->Release();
							}
						}

						PL_Save* pl_save = new PL_Save;
						pl_linecollect->BindNext(pl_save);
						pl_save->Release();
					}
					pl_linecollect->Release();
				}
				pl_filecollect->Release();
			}
			return pl_cmdanalyze;
		}
		GINL GAIA::GVOID DestructPipeline(Pipeline* pPL)
		{
			pPL->UnbindPrevAll();
			pPL->UnbindNextAll();
			pPL->Release();
		}
		GINL GAIA::GVOID StreamError(GAIA::STREAM::StreamBase& prt)
		{
			GAIA::STREAM::StreamFormat prtfmt;
			GAIA::STREAM::StreamFormat prtfmt_old;
			prtfmt.reset();
			prtfmt_old.reset();
			prt >> prtfmt_old;
			prt << prtfmt;

			for(GAIA::SIZE x = 0; x < m_errors.size(); ++x)
			{
				ERROR_SYSTEM::ErrorBase* pError = m_errors[x];
				if(pError == GNIL)
					continue;
				prt << "Prometheus:";
				prt << "P" << GSCAST(GAIA::N32)(pError->getstage());
				prt << "L" << GSCAST(GAIA::N32)(pError->getlevel());
				prt << "N" << GSCAST(GAIA::N32)(pError->getid());
				if(!GAIA::ALGO::stremp(pError->getdesc()))
				{
					prt << ", ";
					prt << pError->getdesc();
				}
				if(!GAIA::ALGO::stremp(pError->getfilename()))
				{
					prt << ", ";
					prt << pError->getfilename();
					if(pError->getfileline() != GINVALID)
						prt << "(" << pError->getfileline() << ")";
				}
				if(!GAIA::ALGO::stremp(pError->getsample()))
				{
					prt << ", ";
					prt << pError->getsample();
				}
				prt << ". \n";
			}
			prt << prtfmt_old;
		}
		GINL GAIA::GVOID ClearError()
		{
			for(GAIA::SIZE x = 0; x < m_errors.size(); ++x)
			{
				ERROR_SYSTEM::ErrorBase* pError = m_errors[x];
				if(pError == GNIL)
					continue;
				delete pError;
			}
			m_errors.clear();
		}
	private:
		__ErrorListType m_errors;
	};
};

#endif