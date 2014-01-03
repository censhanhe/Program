#ifndef		__GAIA_ARITHMETIC_SIZE_INCREASER_H__
#define		__GAIA_ARITHMETIC_SIZE_INCREASER_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _SizeType> class TwiceSizeIncreaser
		{
		public:
			GINL _SizeType Increase(_SizeType size) const{return size * 2 + 1;}
		};
	};
}

#endif