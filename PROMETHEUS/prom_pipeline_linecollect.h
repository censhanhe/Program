#ifndef		__PROM_PIPELINE_LINECOLLECT_H__
#define		__PROM_PIPELINE_LINECOLLECT_H__

namespace PROM
{
	class PL_LineCollect : public Pipeline
	{
	public:
		GINL PL_LineCollect(){}
		GINL ~PL_LineCollect(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PL_LineCollect");}
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs)
		{
			/* Parameter check up. */
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);
			PLC_File* plc_file = static_cast<PLC_File*>(this->GetPLCByName(ppPLC, size, _T("Prom:PLC_File")));
			if(plc_file == GNIL)
				return GNIL;

			/* Initialize result pipeline context. */
			PLC_FileCodeLine* pRet = new PLC_FileCodeLine;

			/* Execute. */
			pRet->file_codelines_list.resize(plc_file->filelist.size());
			GAIA::SIZE uTotalLineCount = 0;
			for(PLC_File::__FileList::_sizetype x = 0; x < plc_file->filelist.size(); ++x)
			{
				GAIA::FILESYSTEM::File file;
				if(!file.Open(plc_file->filelist[x].name, GAIA::FILESYSTEM::File::OPEN_TYPE_READ))
				{
					PROM_RAISE_FILEERROR(502, plc_file->filelist[x].name);
					continue;
				}
				if(!pRet->file_codelines_list[x].lines.load(file))
				{
					PROM_RAISE_FILEERROR(511, plc_file->filelist[x].name);
					continue;
				}
				uTotalLineCount += pRet->file_codelines_list.size();
			}
			prt << "\t\tThere are " << uTotalLineCount << " lines collected!\n";

			/* Release. */
			plc_file->Release();

			return pRet;
		}
	};
};

#endif