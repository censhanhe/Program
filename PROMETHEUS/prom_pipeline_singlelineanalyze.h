#ifndef		__PROM_PIPELINE_SINGLELINEANALYZE_H__
#define		__PROM_PIPELINE_SINGLELINEANALYZE_H__

namespace PROM
{
	class PL_SingleLineAnalyze : public Pipeline
	{
	public:
		GINL PL_SingleLineAnalyze(){}
		GINL ~PL_SingleLineAnalyze(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_SingleLineAnalyze");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			return GNIL;
		}
	};
};

#endif