#ifndef		__GAIA_RENDER_FONT_H__
#define		__GAIA_RENDER_FONT_H__

namespace GAIA
{
	namespace RENDER
	{
		class Font : public virtual GAIA::RENDER::Resource
		{
		public:
			class FontDesc : public GAIA::Base
			{
			public:
			};
		public:
			const FontDesc& GetDesc() const{return m_desc;}
		private:
			FontDesc m_desc;
		};
	};
};

#endif