#ifndef		__PROM_CONTEXT_EMPTY_H__
#define		__PROM_CONTEXT_EMPTY_H__

namespace PROM
{
	class PLC_Empty : public PipelineContext
	{
	public:
		GINL PLC_Empty(){}
		GINL ~PLC_Empty(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_Empty");}
	};
};

#endif