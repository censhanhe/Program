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
		template<typename _DataType> class DirectionalFreeLink : public GAIA::RefObject
		{
		public:
			typedef DirectionalFreeLink<_DataType> __MyType;
		public:
			GINL GAIA::BL BindNext(__MyType* p)
			{
				GAIA_AST(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				GAIA_AST(p != this);
				if(p == this)
					return GAIA::False;
				if(this->prev_exist(p))
					return GAIA::False;
				if(this->next_exist(p))
					return GAIA::False;
				this->Reference();
				p->Reference();
				GAIA::BL bExist = GAIA::False;
				for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
				{
					if(m_nexts[x] == GNULL)
					{
						m_nexts[x] = p;
						bExist = GAIA::True;
						break;
					}
				}
				if(!bExist)
					m_nexts.push_back(p);
				bExist = GAIA::False;
				for(GAIA::SIZE x = 0; x < p->m_prevs.size(); ++x)
				{
					if(p->m_prevs[x] == GNULL)
					{
						p->m_prevs[x] = this;
						bExist = GAIA::True;
						break;
					}
				}
				if(!bExist)
					p->m_prevs.push_back(this);
				return GAIA::True;
			}
			GINL GAIA::BL UnbindNext(__MyType* p)
			{
				GAIA_AST(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				GAIA_AST(p != this);
				if(p == this)
					return GAIA::False;
				GAIA::BL bExist = GAIA::False;
				for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
				{
					if(m_nexts[x] == p)
					{
						m_nexts[x] = GNULL;
						bExist = GAIA::True;
						break;
					}
				}
				if(!bExist)
					return GAIA::False;
				bExist = GAIA::False;
				for(GAIA::SIZE x = 0; x < p->m_prevs.size(); ++x)
				{
					if(p->m_prevs[x] == this)
					{
						p->m_prevs[x] = GNULL;
						bExist = GAIA::True;
						break;
					}
				}
				if(!bExist)
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				this->Release();
				p->Release();
				return GAIA::True;
			}
			GINL GAIA::GVOID UnbindNextAll()
			{
				for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
				{
					__MyType* pPLC = m_nexts[x];
					if(pPLC == GNULL)
						continue;
					this->UnbindNext(pPLC);
				}
			}
			GINL GAIA::SIZE GetNextSize() const{return m_nexts.size();}
			GINL __MyType* GetNext(const GAIA::SIZE& index) const
			{
				if(index >= m_nexts.size())
					return GNULL;
				if(m_nexts[index] == GNULL)
					return GNULL;
				m_nexts[index]->Reference();
				return m_nexts[index];
			}
			GINL GAIA::BL BindPrev(__MyType* p){return p->BindNext(this);}
			GINL GAIA::BL UnbindPrev(__MyType* p){return p->UnbindNext(this);}
			GINL GAIA::GVOID UnbindPrevAll()
			{
				for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
				{
					__MyType* pPLC = m_prevs[x];
					if(pPLC == GNULL)
						continue;
					this->UnbindPrev(pPLC);
				}
			}
			GINL GAIA::SIZE GetPrevSize() const{return m_prevs.size();}
			GINL __MyType* GetPrev(const GAIA::SIZE& index) const
			{
				if(index >= m_prevs.size())
					return GNULL;
				if(m_prevs[index] == GNULL)
					return GNULL;
				m_prevs[index]->Reference();
				return m_prevs[index];
			}
		private:
			GINL GAIA::BL next_exist(__MyType* p) const
			{
				GAIA_AST(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				for(GAIA::SIZE x = 0; x < this->GetNextSize(); ++x)
				{
					__MyType* pNext = this->GetNext(x);
					if(pNext == GNULL)
						continue;
					if(pNext == p)
					{
						pNext->Release();
						return GAIA::True;
					}
					if(pNext->next_exist(p))
					{
						pNext->Release();
						return GAIA::True;
					}
					pNext->Release();
				}
				return GAIA::False;
			}
			GINL GAIA::BL prev_exist(__MyType* p) const
			{
				GAIA_AST(p != GNULL);
				if(p == GNULL)
					return GAIA::False;
				for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
				{
					__MyType* pPrev = this->GetPrev(x);
					if(pPrev == GNULL)
						continue;
					if(pPrev == p)
					{
						p->Release();
						return GAIA::True;
					}
					if(pPrev->prev_exist(p))
					{
						pPrev->Release();
						return GAIA::True;
					}
					pPrev->Release();
				}
				return GAIA::False;
			}
		protected:
			virtual GAIA::GVOID Destruct()
			{
				this->UnbindNextAll();
				this->UnbindPrevAll();
			}
		private:
			typedef GAIA::CONTAINER::Vector<__MyType*> __DoubleLinkList;
		private:
			__DoubleLinkList m_nexts;
			__DoubleLinkList m_prevs;
		};
		class PipelineContext : public DirectionalFreeLink<PipelineContext>
		{
		public:
			GINL PipelineContext(){}
			GINL ~PipelineContext(){}
			virtual const GAIA::GCH* GetName() const = 0;
		};
		class PLCSourceCommand : public PipelineContext
		{
		public:
			GINL PLCSourceCommand(){pCmd = GNULL;}
			GINL ~PLCSourceCommand(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCSourceCommand";}
			const GAIA::GCH* pCmd;
		};
		class PLCCommandParam : public PipelineContext
		{
		public:
			GINL PLCCommandParam(){}
			GINL ~PLCCommandParam(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCCommandParam";}
			DWARFS_MISC::CmdParam cmdparam;
		};
		class PLCFile : public PipelineContext
		{
		public:
			GINL PLCFile();
			GINL ~PLCFile();
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCFile";}
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
		class PLCFileCodeLines : public PipelineContext
		{
		public:
			GINL PLCFileCodeLines();
			GINL ~PLCFileCodeLines();
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCFileCodeLines";}
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
		class Pipeline : public DirectionalFreeLink<Pipeline>
		{
		public:
			GINL Pipeline(){}
			GINL ~Pipeline(){}
			virtual const GAIA::GCH* GetName() const = 0;
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size) = 0;
		};
		class PLCommandAnalyze : public Pipeline
		{
		public:
			GINL PLCommandAnalyze(){}
			GINL ~PLCommandAnalyze(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLCommandAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size)
			{
				return GNULL;
			}
		};
		class PLFileCollect : public Pipeline
		{
		public:
			GINL PLFileCollect(){}
			GINL ~PLFileCollect(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLFileCollect";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size)
			{
				return GNULL;
			}
		};
		class PLLineStatistics : public Pipeline
		{
		public:
			GINL PLLineStatistics(){}
			GINL ~PLLineStatistics(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLLineStatistics";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size)
			{
				return GNULL;
			}
		};
		class PLSymbolStatistics : public Pipeline
		{
		public:
			GINL PLSymbolStatistics(){}
			GINL ~PLSymbolStatistics(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSymbolStatistics";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size)
			{
				return GNULL;
			}
		};
		class PLSingleLineAnalyze : public Pipeline
		{
		public:
			GINL PLSingleLineAnalyze(){}
			GINL ~PLSingleLineAnalyze(){}
			virtual const GAIA::GCH* GetName() const{return "Prom:PLSingleLineAnalyze";}
			virtual PipelineContext* Execute(PipelineContext** ppPLC, const GAIA::SIZE& size)
			{
				return GNULL;
			}
		};
		class PipelineDispatch : public GAIA::RefObject
		{
		public:
			GINL GAIA::GVOID Run(
				Pipeline** ppPrevPL, const GAIA::SIZE& prevpl_size,
				Pipeline** ppNextPL, const GAIA::SIZE& nextpl_size,
				PipelineContext** ppPLC, const GAIA::SIZE& plc_size)
			{
				/* Internal type. */
				typedef GAIA::CONTAINER::Vector<Pipeline*> __PipelineList;
				typedef GAIA::CONTAINER::Vector<PipelineContext*> __PipelineContextList;

				/* Check parameter. */
				GAIA_AST(ppNextPL != GNULL);
				if(ppNextPL == GNULL)
					return;
				GAIA_AST(nextpl_size != 0);
				if(nextpl_size == 0)
					return;
				GAIA_AST(ppPLC != GNULL);
				if(ppPLC == GNULL)
					return;
				GAIA_AST(plc_size != 0);
				if(plc_size == 0)
					return;
				if(ppPrevPL == GNULL)
				{
					GAIA_AST(prevpl_size == 0);
					if(prevpl_size != 0)
						return;
				}
				else
				{
					GAIA_AST(prevpl_size != 0);
					if(prevpl_size == 0)
						return;
					GAIA_AST(prevpl_size == nextpl_size);
					if(prevpl_size != nextpl_size)
						return;
				}
				for(GAIA::SIZE x = 0; x < prevpl_size; ++x)
				{
					GAIA_AST(ppPrevPL[x] != GNULL);
					if(ppPrevPL[x] == GNULL)
						return;
				}
				for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
				{
					GAIA_AST(ppNextPL[x] != GNULL);
					if(ppNextPL[x] == GNULL)
						return;
				}
				for(GAIA::SIZE x = 0; x < plc_size; ++x)
				{
					GAIA_AST(ppPLC[x] != GNULL);
					if(ppPLC[x] == GNULL)
						return;
				}

				/* Dispatch current layer. */
				__PipelineContextList plc_list;
				__PipelineContextList new_plc_list;
				plc_list.reserve(prevpl_size);
				new_plc_list.reserve(prevpl_size);
				for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
				{
					Pipeline* pTempPL = ppNextPL[x];
					GAIA::SIZE uPracPrevSize = 0;
					for(GAIA::SIZE y = 0; y < pTempPL->GetPrevSize(); ++y)
					{
						Pipeline* pTempPrevPL = dynamic_cast<Pipeline*>(pTempPL->GetPrev(y));
						if(pTempPrevPL == GNULL)
							continue;
						pTempPrevPL->Release();
						++uPracPrevSize;
					}
					if(uPracPrevSize == 0)
					{
						PipelineContext* pNewPLC = pTempPL->Execute(ppPLC, plc_size);
						if(pNewPLC == GNULL)
						{
							// OUTPUT.
						}
						new_plc_list.push_back(pNewPLC);
					}
					else
					{
						plc_list.clear();
						GAIA::BL bExecuteAble = GAIA::True;
						for(GAIA::SIZE y = 0; y < pTempPL->GetPrevSize(); ++y)
						{
							Pipeline* pTempPrevPL = dynamic_cast<Pipeline*>(pTempPL->GetPrev(y));
							if(pTempPrevPL == GNULL)
								continue;
							GAIA::BL bFindedMatchedPLC = GAIA::False;
							for(GAIA::SIZE z = 0; z < prevpl_size; ++z)
							{
								if(ppPrevPL[z] == pTempPrevPL)
								{
									plc_list.push_back(ppPLC[z]);
									bFindedMatchedPLC = GAIA::True;
									break;
								}
							}
							pTempPrevPL->Release();
							if(!bFindedMatchedPLC)
							{
								// OUTPUT.
								bExecuteAble = GAIA::False;
								break;
							}
						}
						PipelineContext* pNewPLC = pTempPL->Execute(
							plc_list.front_ptr(), plc_list.size());
						if(pNewPLC == GNULL)
						{
							// OUTPUT.
						}
						new_plc_list.push_back(pNewPLC);
					}
				}

				/* Dispatch next layer. */
				__PipelineList pl_list;
				for(GAIA::SIZE x = 0; x < nextpl_size; ++x)
				{
					for(GAIA::SIZE y = 0; y < ppNextPL[x]->GetNextSize(); ++y)
					{
						Pipeline* pTempNext = dynamic_cast<Pipeline*>(ppNextPL[x]->GetNext(y));
						if(pTempNext == GNULL)
							continue;
						pl_list.push_back(pTempNext);
					}
				}
				this->Run(ppNextPL, nextpl_size, 
					pl_list.front_ptr(), pl_list.size(), 
					new_plc_list.front_ptr(), new_plc_list.size());
				for(GAIA::SIZE x = 0; x < pl_list.size(); ++x)
					pl_list[x]->Release();
			}
		protected:
			virtual GAIA::GVOID Destruct()
			{
			}
		};
	public:
		GINL Prom()
		{
		}
		GINL ~Prom()
		{
		}
		GINL GAIA::BL Command(const GAIA::GCH* psz)
		{
			GAIA_AST(psz != GNULL);
			if(psz == GNULL)
				return GAIA::False;
			if(*psz == 0)
				return GAIA::False;

			PipelineDispatch* pPLD = new PipelineDispatch;
			PLCSourceCommand* pPLC = new PLCSourceCommand; pPLC->pCmd = psz;
			Pipeline* pPL = this->ConstructPipeline();
			{
			}
			this->DestructPipeline(pPL); pPL = GNULL;
			pPLC->Release(); pPLC = GNULL;
			pPLD->Release(); pPLD = GNULL;

			return GAIA::True;
		}
	private:
		GINL Pipeline* ConstructPipeline()
		{
			Pipeline* pl_cmdanalyze = new PLCommandAnalyze;
			return pl_cmdanalyze;
		}
		GINL GAIA::GVOID DestructPipeline(Pipeline* pPL)
		{
			pPL->Release();
		}
	private:
	};
};

#endif
