#ifndef		__PROM_PIPELINE_SAVE_H__
#define		__PROM_PIPELINE_SAVE_H__

namespace PROM
{
	class PL_Save : public Pipeline
	{
	public:
		GINL PL_Save(){}
		GINL ~PL_Save(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_Save");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNULL);
			GPCHR_ZERO_RET(size, GNULL);
			PLC_Empty* pRet = GNULL;
			PLC_CommandParam* plc_commandparam = GNULL;
			PLC_File* plc_file = GNULL;
			PLC_FileCodeLine* plc_codeline = GNULL;
			plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNULL)
				goto FUNCTION_END;
			plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
			if(plc_file == GNULL)
				goto FUNCTION_END;
			plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
			if(plc_codeline == GNULL)
				goto FUNCTION_END;

			/* Initialize result pipeline context. */
			pRet = new PLC_Empty;

			/* Execute. */
			GAIA::BL bSaveCmd = GAIA::False;
			for(GAIA::SIZE x = 0; x < plc_commandparam->cmdparam.cmd_size(); ++x)
			{
				const GAIA::TCH* pszCmd = plc_commandparam->cmdparam.cmd(x);
				if(GAIA::ALGO::stremp(pszCmd))
					continue;
				if(GAIA::ALGO::strcmp(pszCmd, _T("-s")) == 0)
				{
					bSaveCmd = GAIA::True;
					break;
				}
			}
			GAIA::SIZE save_success_count = 0;
			GAIA::SIZE save_failed_count = 0;
			if(bSaveCmd)
			{
				for(GAIA::SIZE x = 0; x < plc_file->filelist.size(); ++x)
				{
					if(!plc_file->filelist[x].bNeedSave)
						continue;
					GAIA::FILESYSTEM::File file;
					if(file.Open(plc_file->filelist[x].name,
						GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS | GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE))
					{
						if(plc_codeline->file_codelines_list[x].lines.save(file))
						{
							plc_file->filelist[x].bNeedSave = GAIA::False;
							++save_success_count;
						}
						else
							--save_failed_count;
					}
					else
						--save_failed_count;
				}
				if(save_failed_count == 0)
					prt << "\t\tThere are " << save_success_count << " files save successfully.\n";
				else
					prt << "\t\tThere are " << save_success_count << " files save successfully, and " << save_failed_count << " files save failed!.\n";
			}

			/* Release. */
		FUNCTION_END:
			if(plc_commandparam != GNULL)
				plc_commandparam->Release();
			if(plc_file != GNULL)
				plc_file->Release();
			if(plc_codeline != GNULL)
				plc_codeline->Release();

			return pRet;
		}
	};
};

#endif