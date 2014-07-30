#ifndef		__PROM_PIPELINE_SYMBOLSTAT_H__
#define		__PROM_PIPELINE_SYMBOLSTAT_H__

namespace PROM
{
	class PL_SymbolStat : public Pipeline
	{
	public:
		GINL PL_SymbolStat(){}
		GINL ~PL_SymbolStat(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_SymbolStat");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			return GNULL;
		}
	};
};

#endif