#ifndef		__GAIA_COLLISIONER_BOUNDER_H__
#define		__GAIA_COLLISIONER_BOUNDER_H__

namespace GAIA
{
	namespace COLLISIONER
	{
		class Bounder : public virtual GAIA::Base
		{
		public:
			GINL Bounder(){}
			GINL ~Bounder(){}
			virtual const GAIA::MATH::MTX44<GAIA::REAL>& GetLocalMatrix() const = 0;
			virtual const GAIA::MATH::AABB<GAIA::REAL>& GetLocalAABB() const = 0;
		};
	};
};

#endif