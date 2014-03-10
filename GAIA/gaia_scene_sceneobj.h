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



			GINL const GAIA::BL SetParent(SceneObj* pParent);
			GINL const SceneObj* GetParent() const;

			GINL const GAIA::BL AddComponent(GAIA::COMPONENT::Component* pComp);
			GINL const GAIA::BL RemoveComponent(GAIA::COMPONENT::Component* pComp);
		};
	};
};

#endif