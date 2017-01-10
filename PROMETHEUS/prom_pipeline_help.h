#ifndef		__PROM_PIPELINE_HELP_H__
#define		__PROM_PIPELINE_HELP_H__

namespace PROM
{
	class PL_Help : public Pipeline
	{
	public:
		GINL PL_Help(){}
		GINL ~PL_Help(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_Help");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::STREAM::StreamBase& stm, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);
			PLC_CommandParam* plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNIL)
				return GNIL;

			/* Initialize result pipeline context. */
			PLC_Empty* pRet = new PLC_Empty;
			for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
			{
				const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
				if(GAIA::ALGO::stremp(pszCmd))
					continue;
				if(GAIA::ALGO::strcmp(pszCmd, _T("help")) == 0)
				{
					if(plc_commandparam->cmdparam.param_size(x) != 0)
					{
						for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.param_size(x); ++y)
						{
						}
					}
					else
					{
						for(GAIA::SIZE y = 0; y < plc_commandparam->cmdparam.cmd_decl_size(); ++y)
						{
							const GAIA::TCH* pszDeclCmd = plc_commandparam->cmdparam.cmd_decl_cmd(y);
							if(pszDeclCmd == GNIL)
								continue;
							const GAIA::TCH* pszDeclDesc = plc_commandparam->cmdparam.cmd_decl_desc(y);
							GAIA::SIZE min_param_size = plc_commandparam->cmdparam.cmd_decl_min_param_size(y);
							GAIA::SIZE max_param_size = plc_commandparam->cmdparam.cmd_decl_max_param_size(y);
							DWARFS_MISC::CmdParam::CMD_TYPE cmdtype = plc_commandparam->cmdparam.cmd_decl_type(y);
							if(GAIA::ALGO::stremp(pszDeclDesc))
								pszDeclDesc = _T("NoInfo");
							stm << "\t" << "[" << y << "]" << pszDeclCmd << ", Info:" << pszDeclDesc << ", " <<
								"[" << min_param_size << ", " << max_param_size << "] " <<
								DWARFS_MISC::CMD_TYPE_NAME[cmdtype] << "\n";
						}
					}
					break;
				}
			}

			if(plc_commandparam != GNIL)
				plc_commandparam->Release();
			return pRet;
		}
	};
};

#endif