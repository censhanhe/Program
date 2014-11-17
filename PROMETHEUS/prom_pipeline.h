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
			GPCHR_NULL_RET(ppPLC, GNIL);
			GPCHR_ZERO_RET(size, GNIL);
			for(GAIA::SIZE x = 0; x < size; ++x)
			{
				if(ppPLC[x] == GNIL)
					continue;
				const GAIA::TCH* pszTempName = ppPLC[x]->GetName();
				if(GAIA::ALGO::strcmp(pszTempName, pszName) == 0)
				{
					ppPLC[x]->Reference();
					return ppPLC[x];
				}
				for(GAIA::SIZE y = 0; y < ppPLC[x]->GetPrevSize(); ++y)
				{
					PipelineContext* pPrevPLC = static_cast<PipelineContext*>(ppPLC[x]->GetPrev(y));
					if(pPrevPLC == GNIL)
						continue;
					PipelineContext* pPrevResult = this->GetPLCByName(&pPrevPLC, 1, pszName);
					pPrevPLC->Release();
					if(pPrevResult != GNIL)
						return pPrevResult;
				}
			}
			return GNIL;
		}
		virtual const GAIA::TCH* GetName() const = 0;
		virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size, GAIA::STREAM::StreamBase& stm, __ErrorListType& errs) = 0;
		virtual GAIA::BL Output(PipelineContext* pPLC, GAIA::FSYS::FileBase* pFile, GAIA::STREAM::StreamBase& stm){return GAIA::False;}
	};
};

#endif