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
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::STREAM::StreamBase& stm, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);
			PLC_Empty* pRet = GNIL;
			PLC_CommandParam* plc_commandparam = GNIL;
			PLC_File* plc_file = GNIL;
			PLC_FileCodeLine* plc_codeline = GNIL;
			plc_commandparam = static_cast<PLC_CommandParam*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_CommandParam")));
			if(plc_commandparam == GNIL)
				goto FUNCTION_END;
			plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
			if(plc_file == GNIL)
				goto FUNCTION_END;
			plc_codeline = static_cast<PLC_FileCodeLine*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_FileCodeLine")));
			if(plc_codeline == GNIL)
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
					GAIA::FSYS::File file;
					if(file.Open(plc_file->filelist[x].name,
						GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS | GAIA::FSYS::File::OPEN_TYPE_WRITE))
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
					stm << "\t\tThere are " << save_success_count << " files save successfully.\n";
				else
					stm << "\t\tThere are " << save_success_count << " files save successfully, and " << save_failed_count << " files save failed!.\n";
			}

			/* Release. */
		FUNCTION_END:
			if(plc_commandparam != GNIL)
				plc_commandparam->Release();
			if(plc_file != GNIL)
				plc_file->Release();
			if(plc_codeline != GNIL)
				plc_codeline->Release();

			return pRet;
		}
	};
};

#endif