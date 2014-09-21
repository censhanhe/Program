#ifndef		__PROM_PIPELINE_OBJANALYZEBASE_H__
#define		__PROM_PIPELINE_OBJANALYZEBASE_H__

namespace PROM
{
	class PL_ObjAnalyzeBase : public Pipeline
	{
	public:
		GINL PL_ObjAnalyzeBase(){}
		GINL ~PL_ObjAnalyzeBase(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_ObjAnalyzeBase");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);

			PLC_ObjCtn* pRet = GNIL;
			PLC_CommandParam* plc_commandparam = GNIL;
			PLC_FileCodeLinePrepare* plc_codelineprepare = GNIL;
			plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNIL)
				goto FUNCTION_END;
			plc_codelineprepare = static_cast<PLC_FileCodeLinePrepare*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLinePrepare")));
			if(plc_codelineprepare == GNIL)
				goto FUNCTION_END;

			/* Initialize result pipeline context. */
			pRet = new PLC_ObjCtn;

			/* Execute. */

		FUNCTION_END:
			if(plc_commandparam != GNIL)
				plc_commandparam->Release();
			if(plc_codelineprepare != GNIL)
				plc_codelineprepare->Release();
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

			PLC_ObjCtn* plc_objctn = static_cast<PLC_ObjCtn*>(pPLC);
			if(plc_objctn == GNIL)
				return GAIA::False;
			if(GAIA::ALGO::strcmp(pPLC->GetName(), _T("Prom:PLC_ObjCtn")) != 0)
				return GAIA::False;

			return GAIA::True;
		}
	};
};

#endif