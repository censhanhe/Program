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
			/* Font. */
			virtual GAIA::RENDER::FontFamily* CreateFontFamily(
				const GAIA::RENDER::FontFamily::FontFamilyDesc& desc) = 0;
			virtual GAIA::RENDER::Font* CreateFont(
				GAIA::RENDER::FontFamily& ff,
				const GAIA::RENDER::Font::FontDesc& desc) = 0;
			virtual GAIA::GVOID DrawFont(
				GAIA::RENDER::Font* pFont,
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;

			/* Pen and brush. */
			virtual GAIA::GVOID DrawLine(
				const GAIA::MATH::VEC2<GAIA::REAL>& s,
				const GAIA::MATH::VEC2<GAIA::REAL>& e,
				const GAIA::MATH::ARGB<GAIA::REAL>& crs,
				const GAIA::MATH::ARGB<GAIA::REAL>& cre, const GAIA::REAL& rWidth) = 0;
			virtual GAIA::GVOID DrawRect(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::ARGB<GAIA::REAL> crs[4]) = 0;
			virtual GAIA::GVOID DrawTriangle(
				const GAIA::MATH::VEC2<GAIA::REAL> pos[3],
				const GAIA::MATH::AABR<GAIA::REAL> crs[3]) = 0;

			/* Texture. */
			virtual GAIA::RENDER::Texture* CreateTexture() = 0;
			virtual GAIA::GVOID DrawTexture(
				const GAIA::MATH::AABR<GAIA::REAL>& aabr, 
				GAIA::RENDER::Texture& tex, 
				const GAIA::MATH::MTX22<GAIA::REAL>& mtxTM) = 0;

		private:
		};
	};
};

#endif