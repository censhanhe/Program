#ifndef		__GAIA_RENDER_VERTEXBUFFER_H__
#define		__GAIA_RENDER_VERTEXBUFFER_H__

namespace GAIA
{
	namespace RENDER
	{
		class VertexBuffer : public virtual GAIA::RENDER::Resource
		{
		public:
			class VertexBufferDesc : public GAIA::Base
			{
			public:
			};
		public:
			const VertexBufferDesc& GetDesc() const{return m_desc;}
		private:
			VertexBufferDesc m_desc;
		};
	};
};

#endif
