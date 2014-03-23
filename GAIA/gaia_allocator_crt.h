#ifndef		__GAIA_ALLOCATOR_CRT_H__
#define		__GAIA_ALLOCATOR_CRT_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
		class AllocatorCRT : public Allocator
		{
		public:
			GINL AllocatorCRT(){}
			GINL ~AllocatorCRT(){}
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::GVOID* memory_alloc(const GAIA::UM& uSize);
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::GVOID memory_release(GAIA::GVOID* p);
			GAIA_DEBUG_CODEPURE_MEMFUNC virtual GAIA::UM memory_size(GAIA::GVOID* p);
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_allocator_crt_indp.h"
#endif

#endif
