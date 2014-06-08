#ifndef		__GAIA_ALLOCATOR_H__
#define		__GAIA_ALLOCATOR_H__

namespace GAIA
{
	namespace ALLOCATOR
	{
		class Allocator : public RefObject
		{
		public:
			virtual GAIA::GVOID* memory_alloc(const GAIA::UM& size) = 0;
			virtual GAIA::GVOID memory_release(GAIA::GVOID* p) = 0;
			virtual GAIA::UM memory_size(GAIA::GVOID* p) = 0;
		};
	};
};

#endif
