#ifndef		__GAIA_ALLOCATOR_ESG_INDP_H__
#define		__GAIA_ALLOCATOR_ESG_INDP_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID* AllocatorESG::memory_alloc(const GAIA::UM& uSize)
		{
			m_piecesize.Increase();
			m_alloctimes.Increase();

			GAIA::UM uSectionIndex = this->GetSectionIndex(uSize + HEAP_BUFFER_HEADERSIZE);
			if(uSectionIndex == GINVALID)
			{
				m_capacity.Add(uSize + HEAP_BUFFER_HEADERSIZE);
				m_size.Add(uSize + HEAP_BUFFER_HEADERSIZE);
				m_usesize.Add(uSize);

				GAIA::GVOID* pTemp = new GAIA::U8[uSize + HEAP_BUFFER_HEADERSIZE];
				*GSCAST(GAIA::UM*)(pTemp) = uSize;
				*GRCAST(GAIA::U16*)(GSCAST(GAIA::U8*)(pTemp) + sizeof(GAIA::UM)) = (GAIA::U16)GINVALID;
				return GSCAST(GAIA::U8*)(pTemp) + sizeof(GAIA::UM) + sizeof(GAIA::U16);
			}
			else
			{
				m_size.Add(m_secsizelist[uSectionIndex]);
				m_usesize.Add(uSize);
			}
			GAIA::GVOID* pRet;
		#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
			m_lr.Enter();
		#endif
			{
				Section& hs = m_seclist[uSectionIndex];
				if(hs.uMinFreeIndex == GINVALID)
				{
					hs.uMinFreeSize = (GAIA::UM)GINVALID;
					for(GAIA::UM x = 0; x < hs.uObListSize; ++x)
					{
						OriginBuffer& ob = hs.oblist[x];
						if(ob.buf != GNULL && ob.uFreeStackSize != 0 && ob.uFreeStackSize < hs.uMinFreeSize)
						{
							hs.uMinFreeSize = (GAIA::UM)ob.uFreeStackSize;
							hs.uMinFreeIndex = x;
						}
					}
				}
				if(hs.uMinFreeIndex == GINVALID)
				{
					GAIA::U16 uOriginBufferIndex;
					if(hs.uFreeStackSize == 0)
					{
						OriginBuffer newob;
						newob.buf = GNULL;
						newob.freestack = GNULL;
						newob.uFreeStackSize = 0;
						newob.uFreeStackCapacity = 0;
						uOriginBufferIndex = (GAIA::U16)hs.uObListSize;
						this->push(newob, hs.oblist, hs.uObListSize, hs.uObListCapacity);
					}
					else
					{
						uOriginBufferIndex = (GAIA::U16)hs.freestack[hs.uFreeStackSize - 1];
						--hs.uFreeStackSize;
					}
					OriginBuffer& newobref = hs.oblist[uOriginBufferIndex];
					GAIA::UM uSectionPatchCount = this->GetSectionPatchCount(uSectionIndex);
					GAIA::UM uSectionPatchSize = m_secsizelist[uSectionIndex];
					newobref.buf = new GAIA::U8[uSectionPatchSize * uSectionPatchCount];
					m_capacity.Add(uSectionPatchSize * uSectionPatchCount);
					for(GAIA::UM x = 0; x < uSectionPatchCount; ++x)
					{
						GAIA::U8* pTemp = (GAIA::U8*)newobref.buf + uSectionPatchSize * x;
						*GRCAST(GAIA::UM*)(pTemp) = uSectionPatchSize;
						*GRCAST(GAIA::U16*)(pTemp + sizeof(GAIA::UM)) = uOriginBufferIndex;
						this->push(pTemp, newobref.freestack, newobref.uFreeStackSize, newobref.uFreeStackCapacity);
					}
					pRet = newobref.freestack[newobref.uFreeStackSize - 1];
					--newobref.uFreeStackSize;
					hs.uMinFreeIndex = uOriginBufferIndex;
					hs.uMinFreeSize = uSectionPatchCount - 1;
				}
				else
				{
					OriginBuffer& ob = hs.oblist[hs.uMinFreeIndex];
					pRet = ob.freestack[ob.uFreeStackSize - 1];
					--ob.uFreeStackSize;
					--hs.uMinFreeSize;
					if(hs.uMinFreeSize == 0)
					{
						hs.uMinFreeIndex = (GAIA::UM)GINVALID;
						hs.uMinFreeSize = (GAIA::UM)GINVALID;
					}
				}
			}
		#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
			m_lr.Leave();
		#endif
			*GSCAST(GAIA::UM*)(pRet) = uSize;
			return GSCAST(GAIA::U8*)(pRet) + sizeof(GAIA::UM) + sizeof(GAIA::U16);
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID AllocatorESG::memory_release(GAIA::GVOID* p)
		{
			GAIA::U8* pOriginP = GSCAST(GAIA::U8*)(p) - sizeof(GAIA::UM) - sizeof(GAIA::U16);
			GAIA::U16 uOBIndex = *GRCAST(GAIA::U16*)(pOriginP + sizeof(GAIA::UM));
			if(uOBIndex == (GAIA::U16)GINVALID)
			{
				m_capacity.Add(-(GAIA::N64)this->memory_size(p) - (GAIA::N64)HEAP_BUFFER_HEADERSIZE);
				m_size.Add(-(GAIA::N64)this->memory_size(p) - (GAIA::N64)HEAP_BUFFER_HEADERSIZE);
				m_usesize.Add(-(GAIA::N64)this->memory_size(p));
				m_piecesize.Decrease();
				delete[] pOriginP;
				return;
			}
			GAIA::UM uSectionIndex = this->GetSectionIndex(*GRCAST(GAIA::UM*)(pOriginP) + HEAP_BUFFER_HEADERSIZE);
			GAIA_AST(uSectionIndex != GINVALID);
			m_size.Add(-(GAIA::N64)m_secsizelist[uSectionIndex]);
			m_usesize.Add(-(GAIA::N64)this->memory_size(p));
			m_piecesize.Decrease();
		#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
			m_lr.Enter();
		#endif
			{
				Section& hs = m_seclist[uSectionIndex];
				OriginBuffer& ob = hs.oblist[uOBIndex];
				this->push(pOriginP, ob.freestack, ob.uFreeStackSize, ob.uFreeStackCapacity);
				if(ob.uFreeStackSize == this->GetSectionPatchCount(uSectionIndex))
				{
					m_capacity.Add(-((GAIA::N64)m_secsizelist[uSectionIndex] * (GAIA::N64)ob.uFreeStackSize));
					if(uOBIndex == hs.uMinFreeIndex)
					{
						hs.uMinFreeIndex = (GAIA::UM)GINVALID;
						hs.uMinFreeSize = (GAIA::UM)GINVALID;
					}
					delete[] ob.freestack;
					ob.freestack = GNULL;
					ob.uFreeStackSize = 0;
					ob.uFreeStackCapacity = 0;
					delete[] ob.buf;
					ob.buf = GNULL;
					this->push(uOBIndex, hs.freestack, hs.uFreeStackSize, hs.uFreeStackCapacity);
				}
			}
		#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
			m_lr.Leave();
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorESG::memory_size(GAIA::GVOID* p)
		{
			return *GRCAST(GAIA::UM*)(GSCAST(GAIA::U8*)(p) - sizeof(GAIA::UM) - sizeof(GAIA::U16));
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorESG::capacity()
		{
			return m_capacity;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorESG::size()
		{
			return m_size;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorESG::use_size()
		{
			return m_usesize;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UM AllocatorESG::piece_size()
		{
			return m_piecesize;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::U64 AllocatorESG::alloc_times()
		{
			return m_alloctimes;
		}
	};
};

#endif
