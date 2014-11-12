#ifndef		__VENUS_INTERFACE_H__
#define		__VENUS_INTERFACE_H__

#include 	"../GAIA/gaia.h"

namespace VENUS
{
	class Render : virtual public GAIA::FWORK::Instance
	{
	public:
		GAIA_ENUM_BEGIN(RESOURCE_TYPE)
			RESOURCE_TYPE_INDEXBUFFER,
			RESOURCE_TYPE_VERTEXBUFFER,
			RESOURCE_TYPE_VERTEXDECLARATION,
			RESOURCE_TYPE_SHADER,
			RESOURCE_TYPE_TEXTURE,
			RESOURCE_TYPE_TARGET,
			RESOURCE_TYPE_DEPTHER,
		GAIA_ENUM_END(RESOURCE_TYPE)

		GAIA_ENUM_BEGIN(RENDER_STATE)
			RENDER_STATE_ALPHABLEND,
			RENDER_STATE_ALPHAFUNC,
			RENDER_STATE_ALPHAREF,
			RENDER_STATE_ZTEST,
			RENDER_STATE_ZFUNC,
			RENDER_STATE_ZWRITE,
			RENDER_STATE_ALPHATEST,
			RENDER_STATE_CULL,
		GAIA_ENUM_END(RENDER_STATE)

		GAIA_ENUM_BEGIN(SAMPLER_STATE)
			SAMPLER_STATE_MINFILTER,
			SAMPLER_STATE_MAXFILTER,
			SAMPLER_STATE_MIPFILTER,
			SAMPLER_STATE_BORDERCOLOR,
			SAMPLER_STATE_BORDER,
		GAIA_ENUM_END(SAMPLER_STATE)

		GAIA_ENUM_BEGIN(QUALITY_STATE)
			QUALITY_STATE_ANTIALIAS,
			QUALITY_STATE_FONTANTIALIAS,
		GAIA_ENUM_END(QUALITY_STATE)

		GAIA_ENUM_BEGIN(FORMAT)
			FORMAT_INDEX16,
			FORMAT_INDEX32,
			FORMAT_R8G8B8,
			FORMAT_X8R8G8B8,
			FORMAT_A8R8G8B8,
			FORMAT_DXT1,
			FORMAT_DXT3,
			FORMAT_DXT5,
			FORMAT_DEPTHF16,
			FORMAT_DEPTHF24,
			FORMAT_DEPTHF32,
		GAIA_ENUM_END(FORMAT)

		GAIA_ENUM_BEGIN(ELEMENT_TYPE)
			ELEMENT_TYPE_SLINE,
			ELEMENT_TYPE_SLINESTRIP,
			ELEMENT_TYPE_STRIANGLELIST,
			ELEMENT_TYPE_STRIANGLEFAN,
			ELEMENT_TYPE_STRIANGLESTRIP,
			ELEMENT_TYPE_SRECT,
			ELEMENT_TYPE_SPOLYGON,
			ELEMENT_TYPE_TRIANGLELIST,
			ELEMENT_TYPE_TRIANGLEFAN,
			ELEMENT_TYPE_TRIANGLESTRIP,
		GAIA_ENUM_END(ELEMENT_TYPE)

		GAIA_ENUM_BEGIN(SHADER_TYPE)
			SHADER_TYPE_VERTEXSHADER,
			SHADER_TYPE_PIXELSHADER,
		GAIA_ENUM_END(SHADER_TYPE)

		GAIA_ENUM_BEGIN(TEXTURE_TYPE)
			TEXTURE_TYPE_1D,
			TEXTURE_TYPE_2D,
			TEXTURE_TYPE_3D,
			TEXTURE_TYPE_CUBE,
		GAIA_ENUM_END(TEXTURE_TYPE)

		class Desc : public GAIA::FWORK::InstanceDesc
		{
		public:
			GAIA::UI::Canvas* pCanvas;
		};

		class Context : virtual public GAIA::RefObject
		{
		public:
		};

		class Resource : virtual public GAIA::RefObject
		{
		public:
			class Desc : virtual public GAIA::Base
			{
			public:
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const = 0;
		};

		class IndexBuffer : virtual public Resource
		{
		public:
			class Desc : virtual Resource::Desc
			{
			public:
				VENUS::Render::FORMAT fmt;
				GAIA::SIZE sCount;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_INDEXBUFFER;}
		};

		class VertexBuffer : virtual public Resource
		{
		public:
			class Desc : virtual Resource::Desc
			{
			public:
				GAIA::SIZE sElementSize; // In bytes.
				GAIA::SIZE sElementCount;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_VERTEXBUFFER;}
		};

		class VertexDeclaration : virtual public Resource
		{
		public:
			class Desc : virtual Resource::Desc
			{
			public:
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_VERTEXDECLARATION;}
		};

		class Shader : virtual public Resource
		{
		public:
			class Desc : virtual Resource::Desc
			{
			public:
				VENUS::Render::SHADER_TYPE type;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_SHADER;}
		};

		class Texture : virtual public Resource
		{
		public:
			class Desc : virtual Resource::Desc
			{
			public:
				VENUS::Render::TEXTURE_TYPE type;
				VENUS::Render::FORMAT fmt;
				GAIA::SIZE sSizeX;
				GAIA::SIZE sSizeY;
				GAIA::SIZE sSizeZ;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_TEXTURE;}
		};

		class Target : virtual public Resource
		{
		public:
			class Desc : virtual Resource::Desc
			{
			public:
				VENUS::Render::FORMAT fmt;
				GAIA::SIZE sSizeX;
				GAIA::SIZE sSizeY;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_TARGET;}
		};

		class Depther : virtual public Resource
		{
		public:
			class Desc : virtual Resource::Desc
			{
			public:
				VENUS::Render::FORMAT fmt;
				GAIA::SIZE sSizeX;
				GAIA::SIZE sSizeY;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_DEPTHER;}
		};

	public:

		/* Base. */
		virtual GAIA::BL Create(const VENUS::Render::Desc& desc) = 0;
		virtual GAIA::BL Destroy() = 0;
		virtual GAIA::BL IsCreated() const = 0;
		virtual const VENUS::Render::Desc& GetDesc() const = 0;
		virtual VENUS::Render::Context* CreateContext() = 0;
		virtual GAIA::BL Begin(VENUS::Render::Context& ctx) = 0;
		virtual GAIA::BL End(VENUS::Render::Context& ctx) = 0;
		virtual GAIA::BL IsBegin(VENUS::Render::Context& ctx) const = 0;
		virtual GAIA::BL Flush(VENUS::Render::Context& ctx, GAIA::BL bWaitComplete) = 0;
		virtual GAIA::BL Present() = 0;

		/* State function. */
		virtual GAIA::BL SetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, const GAIA::CTN::Vari& v) = 0;
		virtual GAIA::BL SetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, const GAIA::CTN::Vari& v) = 0;
		virtual GAIA::BL SetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, const GAIA::CTN::Vari& v) = 0;

		virtual GAIA::BL GetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, GAIA::CTN::Vari& v) = 0;
		virtual GAIA::BL GetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, GAIA::CTN::Vari& v) = 0;
		virtual GAIA::BL GetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, GAIA::CTN::Vari& v) = 0;

		/* Resource function. */
		virtual GAIA::BL CreateIndexBuffer(const VENUS::Render::IndexBuffer::Desc& desc) = 0;
		virtual GAIA::BL CreateVertexBuffer(const VENUS::Render::VertexBuffer::Desc& desc) = 0;
		virtual GAIA::BL CreateVertexDeclaration(const VENUS::Render::VertexDeclaration::Desc& desc) = 0;
		virtual GAIA::BL CreateShader(const VENUS::Render::Shader::Desc& desc) = 0;
		virtual GAIA::BL CreateTexture(const VENUS::Render::Texture::Desc& desc) = 0;
		virtual GAIA::BL CreateTarget(const VENUS::Render::Target::Desc& desc) = 0;
		virtual GAIA::BL CreateDepther(const VENUS::Render::Depther::Desc& desc) = 0;

		virtual GAIA::BL SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB) = 0;
		virtual GAIA::BL SetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, VENUS::Render::VertexBuffer* pVB) = 0;
		virtual GAIA::BL SetVertexDeclaration(VENUS::Render::Context& ctx, VENUS::Render::VertexDeclaration* pVDecl) = 0;
		virtual GAIA::BL SetShader(VENUS::Render::Context& ctx, VENUS::Render::Shader* pShader) = 0;
		virtual GAIA::BL SetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex, VENUS::Render::Texture* pTex) = 0;
		virtual GAIA::BL SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget) = 0;
		virtual GAIA::BL SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther) = 0;

		virtual VENUS::Render::IndexBuffer* GetIndexBuffer(VENUS::Render::Context& ctx) = 0;
		virtual VENUS::Render::VertexBuffer* GetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex) = 0;
		virtual VENUS::Render::VertexDeclaration* GetVertexDeclaration(VENUS::Render::Context& ctx) = 0;
		virtual VENUS::Render::Shader* GetShader(VENUS::Render::Context& ctx) = 0;
		virtual VENUS::Render::Texture* GetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex) = 0;
		virtual VENUS::Render::Target* GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex) = 0;
		virtual VENUS::Render::Depther* GetDepther(VENUS::Render::Context& ctx) = 0;

		/* Draw function. */
		virtual GAIA::BL ClearTarget(GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& argb) = 0;
		virtual GAIA::BL ClearDepther(GAIA::REAL rDepth) = 0;
		virtual GAIA::BL SetVertexBufferBase(GAIA::SIZE sStreamIndex, GAIA::SIZE sBaseIndex);
		virtual GAIA::BL SetIndexBufferBase(GAIA::SIZE sBaseIndex);
		virtual GAIA::BL Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount) = 0;
	};
};

#endif