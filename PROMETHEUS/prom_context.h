#ifndef		__PROM_CONTEXT_H__
#define		__PROM_CONTEXT_H__

namespace PROM
{
	class PipelineContext : public DirectionalFreeLink<PipelineContext>
	{
	public:
		GINL PipelineContext(){}
		GINL ~PipelineContext(){}
		virtual const GAIA::TCH* GetName() const = 0;
	};
};

#endif