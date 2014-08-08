#ifndef		__GAIA_RENDER_TEXTURE_H__
#define		__GAIA_RENDER_TEXTURE_H__

namespace GAIA
{
	namespace RENDER
	{
		class Texture : public virtual GAIA::RENDER::Resource
		{
		public:
			class TextureDesc : public GAIA::Base
			{
			public:
			};
		public:
			const TextureDesc& GetDesc() const{return m_desc;}
		private:
			TextureDesc m_desc;
		};
	};
};

#endif
