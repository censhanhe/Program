#ifndef		__GAIA_SCENE_SCENE_H__
#define		__GAIA_SCENE_SCENE_H__

namespace GAIA
{
	namespace SCENE
	{
		class Scene : public virtual SceneObj
		{
		public:
			GAIA::GVOID AddSceneObj(SceneObj& sobj);
			GAIA::GVOID RemoveSceneObj(SceneObj& sobj);
		};
	};
};

#endif
