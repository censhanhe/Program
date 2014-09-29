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
			GINL virtual GAIA::GVOID* memory_alloc(const GAIA::UM& uSize);
			GINL virtual GAIA::GVOID memory_release(GAIA::GVOID* p);
			GINL virtual GAIA::UM memory_size(GAIA::GVOID* p);
			GINL virtual GAIA::UM capacity();
			GINL virtual GAIA::UM size();
			GINL virtual GAIA::UM use_size();
			GINL virtual GAIA::UM piece_size();
			GINL virtual GAIA::U64 alloc_times();
		private:
			class OriginBuffer
			{
			public:
				GAIA::U8* buf;
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
				m_seclist = GNIL;
				m_uSecListSize = 0;
				m_secsizelist = GNIL;
				m_uSecSizeListSize = 0;
				m_capacity = 0;
				m_size = 0;
				m_usesize = 0;
				m_piecesize = 0;
				m_alloctimes = 0;
			}
			GINL GAIA::UM GetSectionPatchSize(GAIA::UM uIndex) const{return 32 + 32 * uIndex * uIndex;}
			GINL GAIA::UM GetSectionPatchCount(GAIA::UM uIndex) const{if(uIndex == 0) uIndex = 1; return 40000 / (uIndex * uIndex);}
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
						temp.oblist = GNIL;
						temp.uObListSize = 0;
						temp.uObListCapacity = 0;
						temp.freestack = GNIL;
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
					if(m_seclist != GNIL)
					{
						for(GAIA::UM x = 0; x < HEAP_SECTION_COUNT; ++x)
						{
							Section& sec = m_seclist[x];
							if(sec.oblist != GNIL)
							{
								for(GAIA::UM y = 0; y < sec.uObListSize; ++y)
								{
									OriginBuffer& ob = sec.oblist[y];
									if(ob.freestack != GNIL)
										delete[] ob.freestack;
									if(ob.buf != GNIL)
										delete[] ob.buf;
								}
								delete[] sec.oblist;
							}
							if(sec.freestack != NULL)
								delete[] sec.freestack;
						}
						delete[] m_seclist;
						m_seclist = GNIL;
						m_uSecListSize = 0;
					}
					if(m_secsizelist != GNIL)
					{
						delete[] m_secsizelist;
						m_secsizelist = GNIL;
						m_uSecSizeListSize = 0;
					}
				}
			#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
				m_lr.Leave();
			#endif
			}
			template<typename _DataType> GAIA::GVOID push(const _DataType& t, _DataType*& p, GAIA::UM& uSize, GAIA::UM& uCapacity)
			{
				if(uSize == uCapacity)
				{
					GAIA::UM uNewCapacity = uCapacity * 2 + 1;
					_DataType* pNew = new _DataType[uNewCapacity];
					if(p != GNIL)
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
			GAIA::SYNC::Atomic m_capacity;
			GAIA::SYNC::Atomic m_size;
			GAIA::SYNC::Atomic m_usesize;
			GAIA::SYNC::Atomic m_piecesize;
			GAIA::SYNC::Atomic m_alloctimes;
			GAIA::SYNC::Lock m_lr;
		};
	};
};

#include "gaia_allocator_esg_indp.h"

#endif
