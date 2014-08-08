#ifndef		__GAIA_SCENE_CAMERA_H__
#define		__GAIA_SCENE_CAMERA_H__

namespace GAIA
{
	namespace SCENE
	{
		class Camera : public virtual SceneObj
		{
		public:
			GINL Camera();
			GINL ~Camera();
			GINL GAIA::GVOID SetRenderTarget(GAIA::U32 uIndex, GAIA::RENDER::Target* pRenderTarget);
			GINL GAIA::RENDER::Target* GetRenderTarget(GAIA::U32 uIndex) const;
		};
	};
};

#endif
