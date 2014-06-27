#ifndef		__GAIA_ALLOCATOR_CRT_H__
#define		__GAIA_ALLOCATOR_CRT_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
		class AllocatorCRT : public Allocator
		{
		public:
			GINL AllocatorCRT(){this->init();}
			GINL ~AllocatorCRT(){}
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::GVOID* memory_alloc(const GAIA::UM& uSize);
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::GVOID memory_release(GAIA::GVOID* p);
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::UM memory_size(GAIA::GVOID* p);
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::UM capacity();
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::UM size();
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::UM use_size();
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::UM piece_size();
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::U64 alloc_times();
		private:
			GINL GAIA::GVOID init()
			{
				m_capacity = 0;
				m_usesize = 0;
				m_piecesize = 0;
				m_alloctimes = 0;
			}
		private:
			GAIA::SYNC::Atomic m_capacity;
			GAIA::SYNC::Atomic m_usesize;
			GAIA::SYNC::Atomic m_piecesize;
			GAIA::SYNC::Atomic m_alloctimes;
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_allocator_crt_indp.h"
#endif

#endif
