#ifndef		__GAIA_ALLOCATOR_ESG_INDP_H__
#define		__GAIA_ALLOCATOR_ESG_INDP_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID* AllocatorESG::memory_alloc(const GAIA::UM& uSize)
		{
			GAIA::UM uSectionIndex = this->GetSectionIndex(uSize + HEAP_BUFFER_HEADERSIZE);
			if(uSectionIndex == GINVALID)
			{
				GAIA::GVOID* pTemp = new GAIA::U8[uSize + HEAP_BUFFER_HEADERSIZE];
				*(GAIA::UM*)pTemp = uSize;
				*(GAIA::U16*)((GAIA::U8*)pTemp + sizeof(GAIA::UM)) = (GAIA::U16)GINVALID;
				return (GAIA::U8*)pTemp + sizeof(GAIA::UM) + sizeof(GAIA::U16);
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
					for(GAIA::UM x = 0; x < uSectionPatchCount; ++x)
					{
						GAIA::U8* pTemp = (GAIA::U8*)newobref.buf + uSectionPatchSize * x;
						*(GAIA::UM*)pTemp = uSectionPatchSize;
						*(GAIA::U16*)(pTemp + sizeof(GAIA::UM)) = uOriginBufferIndex;
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
			*(GAIA::UM*)pRet = uSize;
			return (GAIA::U8*)pRet + sizeof(GAIA::UM) + sizeof(GAIA::U16);
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID AllocatorESG::memory_release(GAIA::GVOID* p)
		{
			GAIA::U8* pOriginP = (GAIA::U8*)p - sizeof(GAIA::UM) - sizeof(GAIA::U16);
			GAIA::U16 uOBIndex = *(GAIA::U16*)(pOriginP + sizeof(GAIA::UM));
			if(uOBIndex == (GAIA::U16)GINVALID)
			{
				delete[] pOriginP;
				return;
			}
			GAIA::UM uSectionIndex = this->GetSectionIndex(*(GAIA::UM*)pOriginP + HEAP_BUFFER_HEADERSIZE);
		#ifdef GAIA_ALLOCATOR_ESG_MULTITHREAD
			m_lr.Enter();
		#endif
			{
				Section& hs = m_seclist[uSectionIndex];
				OriginBuffer& ob = hs.oblist[uOBIndex];
				this->push(pOriginP, ob.freestack, ob.uFreeStackSize, ob.uFreeStackCapacity);
				if(ob.uFreeStackSize == this->GetSectionPatchCount(uSectionIndex))
				{
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
			return *(GAIA::UM*)((GAIA::U8*)p - sizeof(GAIA::UM) - sizeof(GAIA::U16));
		}
	};
};

#endif