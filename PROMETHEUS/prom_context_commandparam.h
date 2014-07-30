#ifndef		__PROM_CONTEXT_COMMANDPARAM_H__
#define		__PROM_CONTEXT_COMMANDPARAM_H__

namespace PROM
{
	class PLC_CommandParam : public PipelineContext
	{
	public:
		GINL PLC_CommandParam(){this->init();}
		GINL ~PLC_CommandParam(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_CommandParam");}
		DWARFS_MISC::CmdParam cmdparam;
	private:
		GINL GAIA::GVOID init()
		{
		}
	};
};

#endif