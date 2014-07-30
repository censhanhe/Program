#ifndef		__PROM_CONTEXT_FILECODELINEPREPARE_H__
#define		__PROM_CONTEXT_FILECODELINEPREPARE_H__

namespace PROM
{
	class PLC_FileCodeLinePrepare : public PipelineContext
	{
	public:
		GINL PLC_FileCodeLinePrepare(){}
		GINL ~PLC_FileCodeLinePrepare(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_FileCodeLinePrepare");}
	public:
		PLC_FileCodeLine::__FileCodelinesList file_codelines_list;
	};
};

#endif