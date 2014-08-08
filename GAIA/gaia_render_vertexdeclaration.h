#ifndef		__GAIA_RENDER_VERTEXDECLARATION_H__
#define		__GAIA_RENDER_VERTEXDECLARATION_H__

namespace GAIA
{
	namespace RENDER
	{
		class VertexDeclaration : public virtual GAIA::RENDER::Resource
		{
		public:
			class VertexDeclarationDesc : public GAIA::Base
			{
			public:
			};
		public:
			const VertexDeclarationDesc& GetDesc() const{return m_desc;}
		private:
			VertexDeclarationDesc m_desc;
		};
	};
};

#endif