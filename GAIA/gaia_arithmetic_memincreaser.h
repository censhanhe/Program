#ifndef		__GAIA_ARITHMETIC_MEMINCREASER_H__
#define		__GAIA_ARITHMETIC_MEMINCREASER_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _Type> class MemIncreaser
		{
		public:
			GINL virtual _Type Increase(_Type size) const = 0;
		};

		template <typename _Type> class TwiceMemIncreaser : public MemIncreaser<_Type>
		{
		public:
			GINL virtual _Type Increase(_Type size) const{return size * 2 + 1;}
		};
	};
}

#endif