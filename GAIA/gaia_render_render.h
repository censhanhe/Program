#ifndef		__GAIA_RENDER_RENDER_H__
#define		__GAIA_RENDER_RENDER_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render
		{
		public:
			ENUM_BEGIN(DRAW_PRIMITIVE_TYPE)
				DRAW_PRIMITIVE_TYPE_TRIANGLELIST,
				DRAW_PRIMITIVE_TYPE_TRIANGLESTRIP,
				DRAW_PRIMITIVE_TYPE_TRIANGLEFAN,
			ENUM_END

			ENUM_BEGIN(RENDER_STATE)
				RENDER_STATE_ENABLEZTEST,
				RENDER_STATE_ENABLEZWRITE,
				RENDER_STATE_ALPHABLEND,
				RENDER_STATE_ALPHATEST,
				RENDER_STATE_CULLMODE,
				RENDER_STATE_FILLMODE,
			ENUM_END

			ENUM_BEGIN(SAMPLE_STATE)
			ENUM_END

		public:
			GINL Render();
			GINL ~Render();

			virtual GAIA::BL Initialize();
			virtual GAIA::BL Release();
			virtual GAIA::BL IsInitialized() const;

			virtual GAIA::GVOID SetRenderState();
			virtual GAIA::GVOID GetRenderState();
			virtual GAIA::GVOID SetSampleState();
			virtual GAIA::GVOID GetSampleState();
			virtual GAIA::GVOID SetTexture();
			virtual GAIA::GVOID GetTexture();
			virtual GAIA::GVOID DrawTriangle();
			virtual GAIA::GVOID DrawIndexedTriangle();
			virtual GAIA::GVOID DrawLine();
			virtual GAIA::GVOID DrawText();
			virtual GAIA::GVOID Flush();
		};
	};
};

#endif