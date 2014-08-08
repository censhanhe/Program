#ifndef		__GAIA_RENDER_FONTFAMILY_H__
#define		__GAIA_RENDER_FONTFAMILY_H__

namespace GAIA
{
	namespace RENDER
	{
		class FontFamily : public virtual GAIA::RENDER::Resource
		{
		public:
			class FontFamilyDesc : public GAIA::Base
			{
			public:
			};
		public:
			const FontFamilyDesc& GetDesc() const{return m_desc;}
		private:
			FontFamilyDesc m_desc;
		};
	};
};

#endif