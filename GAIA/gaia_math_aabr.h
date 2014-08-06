#ifndef		__GAIA_MATH_AABR_H__
#define		__GAIA_MATH_AABR_H__

namespace GAIA
{
	namespace MATH
	{
		template<typename _DataType> class AABR : public GAIA::Entity
		{
		public:
			GINL GAIA::GVOID identity(){pmin = (_DataType)+1; pmax = (_DataType)-1;}
			GINL GAIA::BL isidentity() const{}
		public:
			VEC2<_DataType> pmin;
			VEC2<_DataType> pmax;
		};
	};
};

#endif