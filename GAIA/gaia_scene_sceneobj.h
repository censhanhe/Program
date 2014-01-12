#ifndef		__GAIA_SCENE_SCENEOBJ_H__
#define		__GAIA_SCENE_SCENEOBJ_H__

namespace GAIA
{
	namespace SCENE
	{
		class SceneObj
		{
		public:
			GINL SceneObj(){}
			GINL ~SceneObj(){}

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