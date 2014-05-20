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
			GINL PipelineContext(){}
			GINL ~PipelineContext(){}
			virtual const GAIA::GCH* GetName() const = 0;
			GINL GAIA::BL BindNext(PipelineContext* pPLC)
			{
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;
				GAIA_AST(pPLC != this);
				if(pPLC == this)
					return GAIA::False;
				if(this->prev_exist(pPLC))
					return GAIA::False;
				pPLC->Reference();
				for(GAIA::SIZE x = 0; x < this->GetNextSize(); ++x)
				{
					if(this->GetNext(x) == GNULL)
					{
						m_nexts[x] = pPLC;
						return GAIA::True;
					}
				}
				m_nexts.push_back(pPLC);
				return GAIA::True;
			}
			GINL GAIA::BL UnbindNext(PipelineContext* pPLC)
			{
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;
				GAIA_AST(pPLC != this);
				if(pPLC == this)
					return GAIA::False;
				for(GAIA::SIZE x = 0; x < this->GetNextSize(); ++x)
				{
					if(this->GetNext(x) == pPLC)
					{
						pPLC->Release();
						m_nexts[x] = GNULL;
						return GAIA::True;
					}
				}
				return GAIA::False;
			}
			GINL GAIA::GVOID UnbindNextAll()
			{
				for(GAIA::SIZE x = 0; x < this->GetNextSize(); ++x)
				{
					PipelineContext* pPLC = this->GetNext(x);
					if(pPLC == GNULL)
						continue;
					this->UnbindNext(pPLC);
				}
			}
			GINL GAIA::SIZE GetNextSize() const{return m_nexts.size();}
			GINL PipelineContext* GetNext(const GAIA::SIZE& index) const{if(index >= m_nexts.size()) return GNULL; return m_nexts[index];}
			GINL GAIA::BL BindPrev(PipelineContext* pPLC)
			{
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;
				GAIA_AST(pPLC != this);
				if(pPLC == this)
					return GAIA::False;
				if(this->next_exist(pPLC))
					return GAIA::False;
				pPLC->Reference();
				for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
				{
					if(this->GetPrev(x) == GNULL)
					{
						m_prevs[x] = pPLC;
						return GAIA::True;
					}
				}
				m_prevs.push_back(pPLC);
				return GAIA::True;
			}
			GINL GAIA::BL UnbindPrev(PipelineContext* pPLC)
			{
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;
				GAIA_AST(pPLC != this);
				if(pPLC == this)
					return GAIA::False;
				for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
				{
					if(this->GetPrev(x) == pPLC)
					{
						pPLC->Release();
						m_prevs[x] = GNULL;
						return GAIA::True;
					}
				}
				return GAIA::True;
			}
			GINL GAIA::GVOID UnbindPrevAll()
			{
				for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
				{
					PipelineContext* pPLC = this->GetPrev(x);
					if(pPLC == GNULL)
						continue;
					this->UnbindPrev(pPLC);
				}
			}
			GINL GAIA::SIZE GetPrevSize() const{return m_prevs.size();}
			GINL PipelineContext* GetPrev(const GAIA::SIZE& index) const{if(index >= m_prevs.size()) return GNULL; return m_prevs[index];}
		private:
			GINL GAIA::BL next_exist(PipelineContext* pPLC) const
			{
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;
				for(GAIA::SIZE x = 0; x < this->GetNextSize(); ++x)
				{
					if(this->GetNext(x) == pPLC)
						return GAIA::True;
					if(this->GetNext(x)->next_exist(pPLC))
						return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::BL prev_exist(PipelineContext* pPLC) const
			{
				GAIA_AST(pPLC != GNULL);
				if(pPLC == GNULL)
					return GAIA::False;
				for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
				{
					if(this->GetPrev(x) == pPLC)
						return GAIA::True;
					if(this->GetPrev(x)->prev_exist(pPLC))
						return GAIA::True;
				}
				return GAIA::False;
			}
		private:
			typedef GAIA::CONTAINER::Vector<PipelineContext*> __PipelineContextList;
			__PipelineContextList m_nexts;
			__PipelineContextList m_prevs;
		};
		class PPCSourceCommand : public PipelineContext
		{
		public:
			GINL PPCSourceCommand(){pCmd = GNULL;}
			GINL ~PPCSourceCommand(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PPCSourceCommand";}
			GAIA::GCH* pCmd;
		};
		class PPCCommandParam : public PipelineContext
		{
		public:
			GINL PPCCommandParam(){}
			GINL ~PPCCommandParam(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PPCCommandParam";}
			DWARFS_MISC::CmdParam cmdparam;
		};
		class PPCFile : public PipelineContext
		{
		public:
			GINL PPCFile();
			GINL ~PPCFile();
			virtual const GAIA::GCH* GetName() const{return "Prom:PPCFile";}
		public:
			typedef GAIA::CONTAINER::AString __FileName;
			class File
			{
			public:
				__FileName name;
			};
			typedef GAIA::CONTAINER::Vector<File> __FileList;
			typedef GAIA::CONTAINER::Vector<GAIA::CONTAINER::Ref<File> > __FileOPTList;
		public:
			__FileList filelist;
			__FileOPTList fileoptlist;
		};
		class PPCFileCodeLines : public PipelineContext
		{
		public:
			GINL PPCFileCodeLines();
			GINL ~PPCFileCodeLines();
			virtual const GAIA::GCH* GetName() const{return "Prom:PPCFileCodeLines";}
		public:
			class FileCodeLines
			{
			public:
				GAIA::SIZE fileid;
				DWARFS_MISC::TextLines lines;
			};
			typedef GAIA::CONTAINER::Vector<FileCodeLines> __FileCodelinesList;
		public:
			__FileCodelinesList file_codelines_list;
		};
		class Pipeline : public GAIA::Base
		{
		public:
			GINL Pipeline(){}
			GINL ~Pipeline(){}
			virtual const GAIA::GCH* GetName() const = 0;
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size) = 0;
			GINL GAIA::BL LinkParent(Pipeline* pPL)
			{
				GAIA_AST(pPL != GNULL);
				if(pPL == GNULL)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::BL UnlinkParent(Pipeline* pPL)
			{
				GAIA_AST(pPL != GNULL);
				if(pPL == GNULL)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::SIZE GetParentSize() const{return m_parents.size();}
			GINL Pipeline* GetParent(const GAIA::SIZE& index) const{if(index >= m_parents.size()) return GNULL; return m_parents[index];}
			GINL GAIA::SIZE GetChildSize() const{return m_childs.size();}
			GINL Pipeline* GetChild(const GAIA::SIZE& index) const{if(index >= m_childs.size()) return GNULL; return m_childs[index];}
		private:
			typedef GAIA::CONTAINER::Vector<Pipeline*> __PipelineList;
		private:
			__PipelineList m_parents;
			__PipelineList m_childs;
		};
		class PLCommandAnalyze : public Pipeline
		{
		public:
			GINL PLCommandAnalyze(){}
			GINL ~PLCommandAnalyze(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCommandAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size){}
		};
		class PLFileCollect : public Pipeline
		{
		public:
			GINL PLFileCollect(){}
			GINL ~PLFileCollect(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLFileCollect";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size){}
		};
		class PLLineStatistics : public Pipeline
		{
		public:
			GINL PLLineStatistics(){}
			GINL ~PLLineStatistics(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLLineStatistics";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size){}
		};
		class PLSymbolStatistics : public Pipeline
		{
		public:
			GINL PLSymbolStatistics(){}
			GINL ~PLSymbolStatistics(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSymbolStatistics";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size){}
		};
		class PLSingleLineAnalyze : public Pipeline
		{
		public:
			GINL PLSingleLineAnalyze(){}
			GINL ~PLSingleLineAnalyze(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSingleLineAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size){}
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
