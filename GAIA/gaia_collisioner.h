#ifndef		__GAIA_COLLISIONER_H__
#define		__GAIA_COLLISIONER_H__

namespace GAIA
{
	namespace COLLISIONER
	{
		class Collisioner : public virtual GAIA::FWORK::Instance
		{
		public:
			GINL Collisioner(){}
			GINL ~Collisioner(){}

			/* Bounder management. */
			virtual GAIA::BL InsertBounder(GAIA::COLLISIONER::Bounder* pBounders, const GAIA::SIZE& sCount) = 0;
			virtual GAIA::BL RemoveBounder(GAIA::COLLISIONER::Bounder* pBounders, const GAIA::SIZE& sCount) = 0;
			virtual GAIA::BL RemoveBounderAll() = 0;

			/* Point trace interface. */
			virtual GAIA::BL PointTrace() = 0;

			/* Ray trace interface. */
			virtual GAIA::BL RayTraceNearest() = 0;
			virtual GAIA::BL RayTrace() = 0;
			virtual GAIA::BL RayTraceExist() = 0;

			/* Sphere trace interface. */
			virtual GAIA::BL SphereTraceNearest() = 0;
			virtual GAIA::BL SphereTrace() = 0;
			virtual GAIA::BL SphereTraceExist() = 0;

			/* Plane trace interface. */
			virtual GAIA::BL PlaneTrace() = 0;
			virtual GAIA::BL PlaneTraceExist() = 0;

			/* Convex trace interface. */
			virtual GAIA::BL ConvexTrace() = 0;
			virtual GAIA::BL ConvexTraceExist() = 0;

		private:
		};
	};
};

#endif