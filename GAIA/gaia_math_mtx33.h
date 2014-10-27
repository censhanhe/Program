#ifndef		__GAIA_MATH_MTX33_H__
#define		__GAIA_MATH_MTX33_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class MTX33 : public GAIA::Base
		{
		public:
			_DataType m[3][3];
		};
	};
};

#endif