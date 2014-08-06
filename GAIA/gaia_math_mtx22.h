#ifndef		__GAIA_MATH_MTX22_H__
#define		__GAIA_MATH_MTX22_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class MTX22 : public GAIA::Entity
		{
		public:
			GINL GAIA::GVOID identity(){}
			GINL GAIA::BL isidentity() const{}
			GINL GAIA::GVOID inverse(){}
			GINL GAIA::GVOID transpose(){}
		public:
			_DataType m[2][2];
		};
	};
};

#endif