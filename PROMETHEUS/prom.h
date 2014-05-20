#ifndef 	__PROMETHEUS_H__
#define 	__PROMETHEUS_H__

#include "../GAIA/gaia.h"
#include "../DWARFS/MISC/cmdparam.h"
#include "../DWARFS/MISC/textlines.h"

namespace PROM
{
	class Prom : public GAIA::Base
	{
	private:
		class PipelineContext : public GAIA::RefObject
		{
		public:
			GINL PipelineContext();
			GINL ~PipelineContext();
			virtual const GAIA::GCH* GetName() const = 0;
			GINL GAIA::BL BindNext(PipelineContext* pPL);
			GINL GAIA::BL UnbindNext(PipelineContext* pPL);
		  	GINL GAIA::SIZE GetNextSize() const;
			GINL PipelineContext* GetNext(const GAIA::SIZE& index) const;	
			GINL GAIA::BL BindPrev(PipelineContext* pPL);
			GINL GAIA::BL UnbindPrev(PipelineContext* pPL);
		  	GINL GAIA::SIZE GetPrevSize() const;
			GINL PipelineContext* GetPrev(const GAIA::SIZE& index) const;	
		};
		class PPCCommand : public PipelineContext
		{
		public:
			GINL PPCCommand();
			GINL ~PPCCommand();
			virtual const GAIA::GCH* GetName() const{return "Prom:PPCCommand";}
		};
		class PPCFile : public PipelineContext
		{
		public:
			GINL PPCFile();
			GINL ~PPCFile();
			virtual const GAIA::GCH* GetName() const{return "Prom:PPCFile";}
		};
		class PPCCodeLines : public PipelineContext
		{
		public:
			GINL PPCCodeLines();
			GINL ~PPCCodeLines();
			virtual const GAIA::GCH* GetName() const{return "Prom:PPCCodeLines";}
		};
		class Pipeline : public GAIA::Base
		{
		public:
			GINL Pipeline();
			GINL ~Pipeline();
			virtual const GAIA::GCH* GetName() const = 0;
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size) = 0;
			GINL GAIA::BL LinkParent(Pipeline* pPL);
			GINL GAIA::BL UnlinkParent(Pipeline* pPL);
			GINL GAIA::SIZE GetParentSize() const;
			GINL Pipeline* GetParent(const GAIA::SIZE& index) const;
			GINL GAIA::SIZE GetChildSize() const;
			GINL Pipeline* GetChild(const GAIA::SIZE& index) const;
		};
		class PLCommandAnalyze : public Pipeline
		{
		public:
			GINL PLCommandAnalyze();
			GINL ~PLCommandAnalyze();
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCommandAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size);
		};
		class PLFileCollect : public Pipeline
		{
		public:
			GINL PLFileCollect();
			GINL ~PLFileCollect();
			virtual const GAIA::GCH* GetName() const{return "Prom:PLFileCollect";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size);
		};
		class PLLineStatistics : public Pipeline
		{
		public:
			GINL PLLineStatistics();
			GINL ~PLLineStatistics();
			virtual const GAIA::GCH* GetName() const{return "Prom:PLLineStatistics";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size);
		};
		class PLSymbolStatistics : public Pipeline
		{
		public:
			GINL PLSymbolStatistics();
			GINL ~PLSymbolStatistics();
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSymbolStatistics";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size);
		};
		class PLSingleLineAnalyze : public Pipeline
		{
		public:
			GINL PLSingleLineAnalyze();
			GINL ~PLSingleLineAnalyze();
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSingleLineAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size);
		};
	public:
		GINL Prom()
		{
		}
		GINL ~Prom()
		{
		}
		GINL GAIA::BL command(const GAIA::GCH* psz)
		{
			GAIA_AST(psz != GNULL);
			if(psz == GNULL)
				return GAIA::False;
			if(*psz == 0)
				return GAIA::False;

			return GAIA::True;
		}
	private:
	};
};

#endif
