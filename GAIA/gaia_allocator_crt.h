#ifndef		__GAIA_ALLOCATOR_CRT_H__
#define		__GAIA_ALLOCATOR_CRT_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
		class AllocatorCRT : public GAIA::ALLOCATOR::Allocator
		{
		public:
			GINL AllocatorCRT(){this->init();}
			GINL ~AllocatorCRT(){}
			GINL virtual GAIA::GVOID* memory_alloc(const GAIA::UM& uSize);
			GINL virtual GAIA::GVOID memory_release(GAIA::GVOID* p);
			GINL virtual GAIA::UM memory_size(GAIA::GVOID* p);
			GINL virtual GAIA::UM capacity();
			GINL virtual GAIA::UM size();
			GINL virtual GAIA::UM use_size();
			GINL virtual GAIA::UM piece_size();
			GINL virtual GAIA::U64 alloc_times();
		private:
			GINL GAIA::GVOID init(){}
		private:
			GAIA::SYNC::Atomic m_capacity;
			GAIA::SYNC::Atomic m_usesize;
			GAIA::SYNC::Atomic m_piecesize;
			GAIA::SYNC::Atomic m_alloctimes;
		};
	};
};

#include "gaia_allocator_crt_indp.h"

#endif
