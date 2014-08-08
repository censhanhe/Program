#ifndef		__GAIA_RENDER_RENDER2D_H__
#define		__GAIA_RENDER_RENDER2D_H__

namespace GAIA
{
	namespace RENDER
	{
		class Render2D : public virtual GAIA::RENDER::Render
		{
		public:
			class Render2DDesc : public GAIA::RENDER::Render::RenderDesc
			{
			public:
			};
		public:
			virtual GAIA::RENDER::FontFamily* CreateFontFamily(const GAIA::RENDER::FontFamily::FontFamilyDesc& desc);
			virtual GAIA::RENDER::Font* CreateFont(GAIA::RENDER::FontFamily& ff, const GAIA::RENDER::Font::FontDesc& desc);
			virtual GAIA::GVOID DrawFont(GAIA::RENDER::Font* pFont, const GAIA::TCH* pszText, const GAIA::MATH::AABR<GAIA::REAL>& rect, const GAIA::MATH::ARGB<GAIA::REAL>& cr);

			
		private:
		};
	};
};

#endif