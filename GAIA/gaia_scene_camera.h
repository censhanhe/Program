#ifndef		__GAIA_SCENE_CAMERA_H__
#define		__GAIA_SCENE_CAMERA_H__

namespace GAIA
{
	namespace SCENE
	{
		class Camera : public SceneObj
		{
		public:
			GINL Camera();
			GINL ~Camera();
			GINL GAIA::GVOID SetRenderTarget(GAIA::U32 uIndex, GAIA::RENDER::RenderTarget* pRenderTarget);
			GINL GAIA::RENDER::RenderTarget* GetRenderTarget(GAIA::U32 uIndex) const;
		};
	};
};

#endif
