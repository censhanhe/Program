#ifndef		__VENUS_RENDER_H__
#define		__VENUS_RENDER_H__

#include  "../GAIA/gaia.h"

namespace VENUS
{
	class Render : public virtual GAIA::FWORK::Instance
	{
	public:
		GAIA_ENUM_BEGIN(RESOURCE_TYPE)
			RESOURCE_TYPE_INDEXBUFFER,
			RESOURCE_TYPE_VERTEXBUFFER,
			RESOURCE_TYPE_SHADER,
			RESOURCE_TYPE_PROGRAM,
			RESOURCE_TYPE_TEXTURE,
			RESOURCE_TYPE_TARGET,
			RESOURCE_TYPE_DEPTHER,
		GAIA_ENUM_END(RESOURCE_TYPE)

		GAIA_ENUM_BEGIN(RENDER_STATE)
			RENDER_STATE_BLEND,
			RENDER_STATE_BLENDSRC,
			RENDER_STATE_BLENDDST,
			RENDER_STATE_BLENDMETHOD,
			RENDER_STATE_ZTEST,
			RENDER_STATE_ZFUNC,
			RENDER_STATE_ZWRITE,
			RENDER_STATE_CULL,
		GAIA_ENUM_END(RENDER_STATE)

		GAIA_ENUM_BEGIN(SAMPLER_STATE)
			SAMPLER_STATE_UNWRAPMODEU,
			SAMPLER_STATE_UNWRAPMODEV,
			SAMPLER_STATE_MINFILTER,
			SAMPLER_STATE_MAXFILTER,
		GAIA_ENUM_END(SAMPLER_STATE)

		GAIA_ENUM_BEGIN(BLEND)
			BLEND_ZERO,
			BLEND_ONE,
			BLEND_SRCALPHA,
			BLEND_DSTALPHA,
			BLEND_SRCALPHAINV,
			BLEND_DSTALPHAINV,
		GAIA_ENUM_END(BLEND)

		GAIA_ENUM_BEGIN(BLEND_METHOD)
			BLEND_METHOD_ADD,
			BLEND_METHOD_SUB,
			BLEND_METHOD_SUBINV,
		GAIA_ENUM_END(BLEND_METHOD)

		GAIA_ENUM_BEGIN(UNWRAPMODE)
			UNWRAPMODE_REPEAT,
			UNWRAPMODE_CLAMP,
			UNWRAPMODE_MIRRIOR,
		GAIA_ENUM_END(UNWRAPMODE)

		GAIA_ENUM_BEGIN(FILTER)
			FILTER_NEAREST,
			FILTER_LINEAR,
		GAIA_ENUM_END(FILTER)

		GAIA_ENUM_BEGIN(QUALITY_STATE)
			QUALITY_STATE_ANTIALIAS,
			QUALITY_STATE_FONTANTIALIAS,
		GAIA_ENUM_END(QUALITY_STATE)

		GAIA_ENUM_BEGIN(FORMAT)
			FORMAT_AUTO,
			FORMAT_INDEX16,
			FORMAT_R8G8B8,
			FORMAT_X8R8G8B8,
			FORMAT_A8R8G8B8,
			FORMAT_DXT1,
			FORMAT_DXT3,
			FORMAT_DXT5,
			FORMAT_DEPTH16,
			FORMAT_DEPTH24,
			FORMAT_DEPTH32,
		GAIA_ENUM_END(FORMAT)

		GAIA_ENUM_BEGIN(ELEMENT_TYPE)
			ELEMENT_TYPE_LINE,
			ELEMENT_TYPE_TRIANGLELIST,
			ELEMENT_TYPE_TRIANGLEFAN,
			ELEMENT_TYPE_TRIANGLESTRIP,
		GAIA_ENUM_END(ELEMENT_TYPE)

		GAIA_ENUM_BEGIN(SHADER_TYPE)
			SHADER_TYPE_VERTEXSHADER,
			SHADER_TYPE_PIXELSHADER,
		GAIA_ENUM_END(SHADER_TYPE)

		GAIA_ENUM_BEGIN(TEXTURE_TYPE)
			TEXTURE_TYPE_2D,
			TEXTURE_TYPE_CUBE,
		GAIA_ENUM_END(TEXTURE_TYPE)

	public:
		class Desc : public virtual GAIA::FWORK::InstanceDesc
		{
		public:
			virtual GAIA::GVOID reset()
			{
				pCanvas = GNIL;
			}
			virtual GAIA::BL check() const
			{
				if(pCanvas == GNIL)
					return GAIA::False;
				if(pCanvas->GetHandle() == GNIL)
					return GAIA::False;
				return GAIA::True;
			}
			GAIA::UI::Canvas* pCanvas;
		};

		class Context : public virtual GAIA::RefObject
		{
		public:
		};

		class Resource : public virtual GAIA::RefObject
		{
		public:
			class Desc : public virtual GAIA::Base
			{
			public:
				virtual GAIA::GVOID reset()
				{
					pFile = GNIL;
				}
				virtual GAIA::BL check() const
				{
					return GAIA::True;
				}
				GAIA::FSYS::FileBase* pFile;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const = 0;
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const = 0;
		};

		class IndexBuffer : public virtual Resource
		{
		public:
			class Desc : public virtual Resource::Desc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					VENUS::Render::Resource::Desc::reset();
					fmt = VENUS::Render::FORMAT_INDEX16;
					sCount = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!VENUS::Render::Resource::Desc::check())
						return GAIA::False;
					if(pFile != GNIL)
						return GAIA::True;
					if(fmt != VENUS::Render::FORMAT_INDEX16)
						return GAIA::False;
					if(sCount <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				VENUS::Render::FORMAT fmt;
				GAIA::SIZE sCount;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_INDEXBUFFER;}
			virtual const VENUS::Render::IndexBuffer::Desc& GetDesc() const = 0;
			virtual GAIA::BL Commit(GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p) = 0;
		};

		class VertexBuffer : public virtual Resource
		{
		public:
			class Desc : public virtual Resource::Desc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					VENUS::Render::Resource::Desc::reset();
					sVertexSize = 0;
					sVertexCount = 0;
					bDynamic = GAIA::False;
				}
				virtual GAIA::BL check() const
				{
					if(!VENUS::Render::Resource::Desc::check())
						return GAIA::False;
					if(pFile != GNIL)
						return GAIA::True;
					if(sVertexSize <= 0)
						return GAIA::False;
					if(sVertexCount <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				GAIA::SIZE sVertexSize; // In bytes.
				GAIA::SIZE sVertexCount;
				GAIA::U8 bDynamic : 1;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_VERTEXBUFFER;}
			virtual const VENUS::Render::VertexBuffer::Desc& GetDesc() const = 0;
			virtual GAIA::BL Commit(GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p) = 0;
		};

		class Shader : public virtual Resource
		{
		public:
			class Desc : public virtual Resource::Desc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					VENUS::Render::Resource::Desc::reset();
					type = VENUS::Render::SHADER_TYPE_INVALID;
				}
				virtual GAIA::BL check() const
				{
					if(!VENUS::Render::Resource::Desc::check())
						return GAIA::False;
					if(pFile != GNIL)
						return GAIA::True;
					if(type == VENUS::Render::SHADER_TYPE_INVALID || 
						type >= VENUS::Render::SHADER_TYPE_MAXENUMCOUNT)
						return GAIA::False;
					return GAIA::True;
				}
				VENUS::Render::SHADER_TYPE type;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_SHADER;}
			virtual const VENUS::Render::Shader::Desc& GetDesc() const = 0;
			virtual GAIA::BL Commit(const GAIA::CH* p) = 0;
		};

		class Program : public virtual Resource
		{
		public:
			class Desc : public virtual Resource::Desc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					pVS = GNIL;
					pPS = GNIL;
				}
				virtual GAIA::BL check() const
				{
					if(pVS == GNIL && pPS == GNIL)
						return GAIA::False;
					return GAIA::True;
				}
				VENUS::Render::Shader* pVS;
				VENUS::Render::Shader* pPS;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_PROGRAM;}
			virtual const VENUS::Render::Program::Desc& GetDesc() const = 0;
		};

		class Texture : public virtual Resource
		{
		public:
			class Desc : public virtual Resource::Desc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					VENUS::Render::Resource::Desc::reset();
					type = VENUS::Render::TEXTURE_TYPE_2D;
					fmt = VENUS::Render::FORMAT_A8R8G8B8;
					sSizeX = 0;
					sSizeY = 0;
					sSizeZ = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!VENUS::Render::Resource::Desc::check())
						return GAIA::False;
					if(pFile != GNIL)
						return GAIA::True;
					if(type == VENUS::Render::TEXTURE_TYPE_INVALID || 
						type >= VENUS::Render::TEXTURE_TYPE_MAXENUMCOUNT)
						return GAIA::False;
					switch(type)
					{
					case VENUS::Render::TEXTURE_TYPE_2D:
						{
							if(sSizeX <= 0)
								return GAIA::False;
							if(sSizeY <= 0)
								return GAIA::False;
							if(sSizeZ != 0)
								return GAIA::False;
						}
						break;
					default:
						GAIA_AST(GAIA::ALWAYSFALSE);
						break;
					}
					return GAIA::True;
				}
				VENUS::Render::TEXTURE_TYPE type;
				VENUS::Render::FORMAT fmt;
				GAIA::SIZE sSizeX;
				GAIA::SIZE sSizeY;
				GAIA::SIZE sSizeZ;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_TEXTURE;}
			virtual const VENUS::Render::Texture::Desc& GetDesc() const = 0;
			virtual GAIA::BL Commit(GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, GAIA::SIZE sMipIndex, GAIA::SIZE sFaceIndex, const GAIA::GVOID* p) = 0;
		};

		class Target : public virtual Resource
		{
		public:
			class Desc : public virtual Resource::Desc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					VENUS::Render::Resource::Desc::reset();
					fmt = VENUS::Render::FORMAT_A8R8G8B8;
					sSizeX = 0;
					sSizeY = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!VENUS::Render::Resource::Desc::check())
						return GAIA::False;
					if(pFile != GNIL)
						return GAIA::True;
					if(fmt != VENUS::Render::FORMAT_X8R8G8B8 && 
						fmt != VENUS::Render::FORMAT_A8R8G8B8)
						return GAIA::False;
					if(sSizeX <= 0)
						return GAIA::False;
					if(sSizeY <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				VENUS::Render::FORMAT fmt;
				GAIA::SIZE sSizeX;
				GAIA::SIZE sSizeY;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_TARGET;}
			virtual const VENUS::Render::Target::Desc& GetDesc() const = 0;
		};

		class Depther : public virtual Resource
		{
		public:
			class Desc : public virtual Resource::Desc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					VENUS::Render::Resource::Desc::reset();
					fmt = VENUS::Render::FORMAT_DEPTH24;
					sSizeX = 0;
					sSizeY = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!VENUS::Render::Resource::Desc::check())
						return GAIA::False;
					if(fmt != VENUS::Render::FORMAT_DEPTH16 && 
						fmt != VENUS::Render::FORMAT_DEPTH24 && 
						fmt != VENUS::Render::FORMAT_DEPTH32)
						return GAIA::False;
					if(sSizeX <= 0)
						return GAIA::False;
					if(sSizeY <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				VENUS::Render::FORMAT fmt;
				GAIA::SIZE sSizeX;
				GAIA::SIZE sSizeY;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_DEPTHER;}
			virtual const VENUS::Render::Depther::Desc& GetDesc() const = 0;
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

		/* State function. */
		virtual GAIA::BL SetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, const GAIA::CTN::Vari& v) = 0;
		virtual GAIA::BL SetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, const GAIA::CTN::Vari& v) = 0;
		virtual GAIA::BL SetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, const GAIA::CTN::Vari& v) = 0;

		virtual GAIA::BL GetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, GAIA::CTN::Vari& v) = 0;
		virtual GAIA::BL GetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, GAIA::CTN::Vari& v) = 0;
		virtual GAIA::BL GetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, GAIA::CTN::Vari& v) = 0;

		/* Resource function. */
		virtual VENUS::Render::IndexBuffer* CreateIndexBuffer(const VENUS::Render::IndexBuffer::Desc& desc) = 0;
		virtual VENUS::Render::VertexBuffer* CreateVertexBuffer(const VENUS::Render::VertexBuffer::Desc& desc) = 0;
		virtual VENUS::Render::Shader* CreateShader(const VENUS::Render::Shader::Desc& desc) = 0;
		virtual VENUS::Render::Program* CreateProgram(const VENUS::Render::Program::Desc& desc) = 0;
		virtual VENUS::Render::Texture* CreateTexture(const VENUS::Render::Texture::Desc& desc) = 0;
		virtual VENUS::Render::Target* CreateTarget(const VENUS::Render::Target::Desc& desc) = 0;
		virtual VENUS::Render::Depther* CreateDepther(const VENUS::Render::Depther::Desc& desc) = 0;

		virtual GAIA::BL SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB) = 0;
		virtual GAIA::BL SetVertexBuffer(VENUS::Render::Context& ctx, const GAIA::CH* pszName, VENUS::Render::VertexBuffer* pVB, GAIA::SIZE sStride, GAIA::SIZE sOffset) = 0;
		virtual GAIA::BL SetProgram(VENUS::Render::Context& ctx, VENUS::Render::Program* pProgram) = 0;
		virtual GAIA::BL SetTexture(VENUS::Render::Context& ctx, const GAIA::CH* pszName, VENUS::Render::Texture* pTex) = 0;
		virtual GAIA::BL SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget) = 0;
		virtual GAIA::BL SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther) = 0;

		virtual VENUS::Render::IndexBuffer* GetIndexBuffer(VENUS::Render::Context& ctx) = 0;
		virtual VENUS::Render::VertexBuffer* GetVertexBuffer(VENUS::Render::Context& ctx, const GAIA::CH* pszName, GAIA::SIZE& sStride, GAIA::SIZE& sOffset) = 0;
		virtual VENUS::Render::Program* GetProgram(VENUS::Render::Context& ctx) = 0;
		virtual VENUS::Render::Texture* GetTexture(VENUS::Render::Context& ctx, const GAIA::CH* pszName) = 0;
		virtual VENUS::Render::Target* GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex) = 0;
		virtual VENUS::Render::Depther* GetDepther(VENUS::Render::Context& ctx) = 0;

		/* Program constant management. */
		virtual GAIA::BL SetConstant(VENUS::Render::Context& ctx, const GAIA::CH* pszUniformName, const GAIA::F32* p, GAIA::U8 uDimenX, GAIA::U8 uDimenY, GAIA::SIZE sCount) = 0;
		virtual GAIA::BL GetConstant(VENUS::Render::Context& ctx, const GAIA::CH* pszUniformName, GAIA::F32* p, GAIA::U8 uDimenX, GAIA::U8 uDimenY, GAIA::SIZE sCount) = 0;

		/* Draw function. */
		virtual GAIA::BL SetViewport(const GAIA::MATH::AABR<GAIA::N32>& vp) = 0;
		virtual GAIA::BL GetViewport(GAIA::MATH::AABR<GAIA::N32>& vp) const = 0;
		virtual GAIA::BL SetScissor(const GAIA::MATH::AABR<GAIA::N32>& s) = 0;
		virtual GAIA::BL GetScissor(GAIA::MATH::AABR<GAIA::N32>& s) const = 0;
		virtual GAIA::BL SetElementType(VENUS::Render::Context& ctx, VENUS::Render::ELEMENT_TYPE eletype) = 0;
		virtual VENUS::Render::ELEMENT_TYPE GetElementType(VENUS::Render::Context& ctx) const = 0;
		virtual GAIA::BL ClearTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;
		virtual GAIA::BL ClearDepther(VENUS::Render::Context& ctx, GAIA::REAL rDepth) = 0;
		virtual GAIA::BL Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount) = 0;
	};
};

#endif