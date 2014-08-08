#ifndef		__GAIA_RENDER_INDEXBUFFER_H__
#define		__GAIA_RENDER_INDEXBUFFER_H__

namespace GAIA
{
	namespace RENDER
	{
		class IndexBuffer : public virtual GAIA::RENDER::Resource
		{
		public:
			class IndexBufferDesc : public GAIA::Base
			{
			public:
			};
		public:
			const IndexBufferDesc& GetDesc() const{return m_desc;}
		private:
			IndexBufferDesc m_desc;
		};
	};
};

#endif
