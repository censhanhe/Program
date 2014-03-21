#ifndef		__GAIA_ALLOCATOR_ESG_H__
#define		__GAIA_ALLOCATOR_ESG_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
		#define GAIA_ALLOCATOR_ESG_MULTITHREAD
		class AllocatorESG : public Allocator
		{
		public:
			GINL AllocatorESG(){this->init(); this->InitHeap();}
			GINL ~AllocatorESG(){this->ReleaseHeap();}
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::GVOID* alloc_proc(const GAIA::UM& uSize);
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::GVOID release_proc(GAIA::GVOID* p);
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::UM size_proc(GAIA::GVOID* p);
		private:
			class OriginBuffer
			{
			public:
				GAIA::GVOID* buf;
				GAIA::U8** freestack;
				GAIA::UM uFreeStackSize;
				GAIA::UM uFreeStackCapacity;
			};
			class Section
			{
			public:
				OriginBuffer* oblist;
				GAIA::UM uObListSize;
				GAIA::UM uObListCapacity;
				GAIA::U16* freestack;
				GAIA::UM uFreeStackSize;
				GAIA::UM uFreeStackCapacity;
				GAIA::UM uMinFreeIndex;
				GAIA::UM uMinFreeSize;
			};
		private:
			GINL GAIA::GVOID init()
			{
				m_seclist = GNULL;
				m_uSecListSize = 0;
				m_secsizelist = GNULL;
				m_uSecSizeListSize = 0;
			}
			GINL GAIA::UM GetSectionPatchSize(GAIA::UM uIndex) const{return 32 + 32 * uIndex * uIndex;}
			GINL GAIA::UM GetSectionPatchCount(GAIA::UM uIndex) const{if(uIndex == 0) uIndex = 1; return 40000 / uIndex / uIndex;}
			GINL GAIA::UM GetSectionIndex(GAIA::UM uSize) const
			{
				GAIA::UM x;
				for(x = 0; x < HEAP_SECTION_COUNT; x += 10)
				{
					GAIA::UM uTemp = m_secsizelist[x];
					if(uTemp < uSize)
						continue;
					if(uTemp == uSize)
						return x;
					if(x > 0)
					{
						for(GAIA::UM y = 0; y < 10; y++)
						{
							if(m_secsizelist[x + y - 10] >= uSize)
								return x + y - 10;
						}
					}
					return x;
				}
				x -= 10;
				for(; x < HEAP_SECTION_COUNT; ++x)
				{
					if(m_secsizelist[x] >= uSize)
						return x;
				}
				return (GAIA::UM)GINVALID;
			}
			GINL GAIA::GVOID InitHeap()
			{
				GAIA_AST(HEAP_SECTION_COUNT == 100);
			#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
				m_lr.Enter();
			#endif
				{
					m_seclist = new Section[HEAP_SECTION_COUNT];
					m_secsizelist = new GAIA::UM[HEAP_SECTION_COUNT];
					for(GAIA::UM x = 0; x < HEAP_SECTION_COUNT; ++x)
					{
						Section temp;
						temp.oblist = GNULL;
						temp.uObListSize = 0;
						temp.uObListCapacity = 0;
						temp.freestack = GNULL;
						temp.uFreeStackSize = 0;
						temp.uFreeStackCapacity = 0;
						temp.uMinFreeIndex = (GAIA::UM)GINVALID;
						temp.uMinFreeSize = (GAIA::UM)GINVALID;
						m_seclist[x] = temp;
						m_secsizelist[x] = this->GetSectionPatchSize(x);
					}
				}
			#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
				m_lr.Leave();
			#endif
			}
			GINL GAIA::GVOID ReleaseHeap()
			{
			#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
				m_lr.Enter();
			#endif
				{
					if(m_seclist != GNULL)
					{
						for(GAIA::UM x = 0; x < HEAP_SECTION_COUNT; ++x)
						{
							Section& sec = m_seclist[x];
							if(sec.oblist != GNULL)
							{
								for(GAIA::UM y = 0; y < sec.uObListSize; ++y)
								{
									OriginBuffer& ob = sec.oblist[y];
									if(ob.freestack != GNULL)
										delete[] ob.freestack;
									if(ob.buf != GNULL)
										delete[] ob.buf;
								}
								delete[] sec.oblist;
							}
							if(sec.freestack != NULL)
								delete[] sec.freestack;
						}
						delete[] m_seclist;
						m_seclist = GNULL;
						m_uSecListSize = 0;
					}
					if(m_secsizelist != GNULL)
					{
						delete[] m_secsizelist;
						m_secsizelist = GNULL;
						m_uSecSizeListSize = 0;
					}
				}
			#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
				m_lr.Leave();
			#endif
			}
			template<typename _DataType> GINL GAIA::GVOID push(const _DataType& t, _DataType*& p, GAIA::UM& uSize, GAIA::UM& uCapacity)
			{
				if(uSize == uCapacity)
				{
					GAIA::UM uNewCapacity = uCapacity * 2 + 1;
					_DataType* pNew = new _DataType[uNewCapacity];
					if(p != GNULL)
					{
						for(GAIA::UM x = 0; x < uSize; ++x)
							pNew[x] = p[x];
						delete[] p;
					}
					p = pNew;
					uCapacity = uNewCapacity;
				}
				GAIA_AST(uSize < uCapacity);
				p[uSize++] = t;
			}
		private:
			static const GAIA::UM HEAP_SECTION_COUNT = 100;
			static const GAIA::UM HEAP_BUFFER_HEADERSIZE = sizeof(GAIA::UM) + sizeof(GAIA::U16); // First is the buffer's size, second is the origin buffer index.
		private:
			Section* m_seclist;
			GAIA::UM m_uSecListSize;
			GAIA::UM* m_secsizelist;
			GAIA::UM m_uSecSizeListSize;
			GAIA::SYNC::Lock m_lr;
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_allocator_esg_indp.h"
#endif

#endif
