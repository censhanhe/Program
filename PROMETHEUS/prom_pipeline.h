#ifndef		__PROM_PIPELINE_H__
#define		__PROM_PIPELINE_H__

namespace PROM
{
	class Pipeline : public DirectionalFreeLink<Pipeline>
	{
	public:
		GINL Pipeline(){}
		GINL ~Pipeline(){}
		GINL PipelineContext* GetPLCByName(PipelineContext** ppPLC, const GAIA::SIZE& size, const GAIA::TCH* pszName) const
		{
			GPCHR_NULL_RET(ppPLC, GNULL);
			GPCHR_ZERO_RET(size, GNULL);
			for(GAIA::SIZE x = 0; x < size; ++x)
			{
				if(ppPLC[x] == GNULL)
					continue;
				const GAIA::TCH* pszTempName = ppPLC[x]->GetName();
				if(GAIA::ALGORITHM::strcmp(pszTempName, pszName) == 0)
				{
					ppPLC[x]->Reference();
					return ppPLC[x];
				}
				for(GAIA::SIZE y = 0; y < ppPLC[x]->GetPrevSize(); ++y)
				{
					PipelineContext* pPrevPLC = static_cast<PipelineContext*>(ppPLC[x]->GetPrev(y));
					if(pPrevPLC == GNULL)
						continue;
					PipelineContext* pPrevResult = this->GetPLCByName(&pPrevPLC, 1, pszName);
					pPrevPLC->Release();
					if(pPrevResult != GNULL)
						return pPrevResult;
				}
			}
			return GNULL;
		}
		virtual const GAIA::TCH* GetName() const = 0;
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::PRINT::PrintBase& prt, __ErrorListType& errs) = 0;
		virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FILESYSTEM::FileBase* pFile, GAIA::PRINT::PrintBase& prt){return GAIA::False;}
	};
};

#endif