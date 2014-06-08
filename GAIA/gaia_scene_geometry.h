#ifndef		__GAIA_SCENE_GEOMETRY_H__
#define		__GAIA_SCENE_GEOMETRY_H__

namespace GAIA
{
	namespace SCENE
	{
		class GeoLinkToDesc
		{
		public:
		};

		class Geometry
		{
		public:
			GINL Geometry();
			GINL ~Geometry();

			GINL GAIA::GVOID SetLinkToDesc(const GeoLinkToDesc* pDesc);
			GINL const GeoLinkToDesc* GetLinkToDesc() const;

			GINL GAIA::GVOID SetMatrixWorld(const GAIA::MATH::MTX44& mtx);
			GINL const GAIA::MATH::MTX44& GetMatrixWorld() const;
			GINL GAIA::GVOID SetMatrixLocal(const GAIA::MATH::MTX44& mtx);
			GINL const GAIA::MATH::MTX44& GetMatrixLocal() const;
			GINL GAIA::GVOID SetAABBWorld(const GAIA::MATH::AABB& aabb);
			GINL const GAIA::MATH::MTX44& GetAABBWorld() const;
			GINL GAIA::GVOID SetAABBLocal(const GAIA::MATH::AABB& aabb);
			GINL const GAIA::MATH::AABB& GetAABBLocal() const;
		};
	};
};

#endif
