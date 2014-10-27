#ifndef		__GAIA_MATH_MTX32_H__
#define		__GAIA_MATH_MTX32_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class MTX32 : public GAIA::Base
		{
		public:
			_DataType m[3][2];
		};
	};
};

#endif