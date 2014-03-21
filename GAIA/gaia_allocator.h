#ifndef		__GAIA_ALLOCATOR_H__
#define		__GAIA_ALLOCATOR_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
		class Allocator : public RefObject
		{
		public:
			virtual GAIA::GVOID* alloc_proc(const GAIA::UM& size) = 0;
			virtual GAIA::GVOID release_proc(GAIA::GVOID* p) = 0;
			virtual GAIA::UM size_proc(GAIA::GVOID* p) = 0;
		};
	};
};

#endif
