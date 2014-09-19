#ifndef		__PROM_PIPELINE_COMMANDANALYZE_H__
#define		__PROM_PIPELINE_COMMANDANALYZE_H__

namespace PROM
{
	class PL_CommandAnalyze : public Pipeline
	{
	public:
		GINL PL_CommandAnalyze(){}
		GINL ~PL_CommandAnalyze(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_CommandAnalyze");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);
			PLC_SourceCommand* plc_sourcecommand = static_cast<PLC_SourceCommand*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_SourceCommand")));
			if(plc_sourcecommand == GNIL)
				return GNIL;

			/* Initialize result pipeline context. */
			PLC_CommandParam* pRet = new PLC_CommandParam;
			pRet->cmdparam.begin_decl();
			{
				pRet->cmdparam.cmd_decl(_T("help"), _T("show help information"), 0, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);

				pRet->cmdparam.cmd_decl(_T("-i"), _T("input files"), 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-I"), _T("input directory"), 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-E"), _T("input directory files extension name filter"), 1, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-s"), _T("save changes to source files"), 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-o"), _T("output the stage result"), 1, 2, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-h"), _T("set header file path"), 0, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-predefine"), _T("set predefine macros"), 0, GINVALID, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-export"), _T("export the temp result to destination path"), 2, 2, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);

				pRet->cmdparam.cmd_decl(_T("-linebreak"), _T("change lines break flag, use \"\\r\" \"\\n\" or \"\\r\\n\""), 1, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-fmt"), _T("format the codes"), 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);

				pRet->cmdparam.cmd_decl(_T("-linestat"), _T("statistics the lines"), 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-wordstat"), _T("statistics the words, use -o to output the result"), 0, 1, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
				pRet->cmdparam.cmd_decl(_T("-symbolstat"), _T("statistics the symbols, use -o to output the result"), 0, 0, DWARFS_MISC::CmdParam::CMD_TYPE_INVALID);
			}
			pRet->cmdparam.end_decl();

			/* Execute. */
			if(!pRet->cmdparam.build(plc_sourcecommand->pszCmd, prt))
			{
				PROM_RAISE_FATALERROR(102);
				pRet->Release();
				plc_sourcecommand->Release();
				return GNIL;
			}

			/* Release. */
			plc_sourcecommand->Release();

			return pRet;
		}
		virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt)
		{
			/* Parameter check up. */
			GAIA_AST(pPLC != GNIL);
			if(pPLC == GNIL)
				return GAIA::False;

			GAIA_AST(!GAIA::ALGO::stremp(pPLC->GetName()));
			if(GAIA::ALGO::stremp(pPLC->GetName()))
				return GAIA::False;

			PLC_CommandParam* plc_sourcecommand = static_cast<PLC_CommandParam*>(pPLC);
			if(plc_sourcecommand == GNIL)
				return GAIA::False;
			if(GAIA::ALGO::strcmp(pPLC->GetName(), _T("Prom:PLC_CommandParam")) != 0)
				return GAIA::False;

			for(GAIA::SIZE x = 0; x < plc_sourcecommand->cmdparam.cmd_size(); ++x)
			{
				const GAIA::TCH* pszCmd = plc_sourcecommand->cmdparam.cmd(x);
				if(GAIA::ALGO::stremp(pszCmd))
					continue;
				prt << "\t\t" << pszCmd << " ";
				for(GAIA::SIZE y = 0; y < plc_sourcecommand->cmdparam.param_size(x); ++y)
				{
					const GAIA::TCH* pszParam = plc_sourcecommand->cmdparam.param(x, y);
					if(GAIA::ALGO::stremp(pszParam))
						continue;
					prt << pszParam << " ";
				}
				prt << "\n";
			}

			return GAIA::True;
		}
	};
};

#endif