#ifndef		__PROM_CONTEXT_SOURCECOMMAND_H__
#define		__PROM_CONTEXT_SOURCECOMMAND_H__

namespace PROM
{
	class PLC_SourceCommand : public PipelineContext
	{
	public:
		GINL PLC_SourceCommand(){pszCmd = GNIL;}
		GINL ~PLC_SourceCommand(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_SourceCommand");}
		const GAIA::TCH* pszCmd;
	};
};

#endif