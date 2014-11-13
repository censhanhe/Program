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
			RESOURCE_TYPE_VERTEXDECLARATION,
			RESOURCE_TYPE_SHADER,
			RESOURCE_TYPE_PROGRAM,
			RESOURCE_TYPE_TEXTURE,
			RESOURCE_TYPE_TARGET,
			RESOURCE_TYPE_DEPTHER,
		GAIA_ENUM_END(RESOURCE_TYPE)

		GAIA_ENUM_BEGIN(RENDER_STATE)
			RENDER_STATE_ALPHABLEND,
			RENDER_STATE_ZTEST,
			RENDER_STATE_ZFUNC,
			RENDER_STATE_ZWRITE,
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
			ELEMENT_TYPE_SLINE,
			ELEMENT_TYPE_SLINESTRIP,
			ELEMENT_TYPE_STRIANGLELIST,
			ELEMENT_TYPE_STRIANGLEFAN,
			ELEMENT_TYPE_STRIANGLESTRIP,
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

		GAIA_ENUM_BEGIN(COMMIT_METHOD)
			COMMIT_METHOD_READ,
			COMMIT_METHOD_WRITE,
			COMMIT_METHOD_READWRITE,
		GAIA_ENUM_END(COMMIT_METHOD)

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
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p) = 0;
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
					sElementSize = 0;
					sElementCount = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!VENUS::Render::Resource::Desc::check())
						return GAIA::False;
					if(pFile != GNIL)
						return GAIA::True;
					if(sElementSize <= 0)
						return GAIA::False;
					if(sElementCount <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				GAIA::SIZE sElementSize; // In bytes.
				GAIA::SIZE sElementCount;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_VERTEXBUFFER;}
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p) = 0;
		};

		class VertexDeclaration : public virtual Resource
		{
		public:
			class Desc : public virtual Resource::Desc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					VENUS::Render::Resource::Desc::reset();
				}
				virtual GAIA::BL check() const
				{
					if(!VENUS::Render::Resource::Desc::check())
						return GAIA::False;
					if(pFile != GNIL)
						return GAIA::True;
					return GAIA::True;
				}
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_VERTEXDECLARATION;}
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
				}
				VENUS::Render::Shader* pVS;
				VENUS::Render::Shader* pPS;
			};
		public:
			virtual VENUS::Render::RESOURCE_TYPE GetResourceType() const{return VENUS::Render::RESOURCE_TYPE_PROGRAM;}
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
					case VENUS::Render::TEXTURE_TYPE_1D:
						{
							if(sSizeX <= 0)
								return GAIA::False;
							if(sSizeY != 0)
								return GAIA::False;
							if(sSizeZ != 0)
								return GAIA::False;
						}
						break;
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
					case VENUS::Render::TEXTURE_TYPE_3D:
						{
							if(sSizeX <= 0)
								return GAIA::False;
							if(sSizeY <= 0)
								return GAIA::False;
							if(sSizeZ <= 0)
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
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, GAIA::SIZE sMipIndex, GAIA::SIZE sFaceIndex, const GAIA::GVOID* p) = 0;
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
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p) = 0;
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
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p) = 0;
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
		virtual VENUS::Render::VertexDeclaration* CreateVertexDeclaration(const VENUS::Render::VertexDeclaration::Desc& desc) = 0;
		virtual VENUS::Render::Shader* CreateShader(const VENUS::Render::Shader::Desc& desc) = 0;
		virtual VENUS::Render::Program* CreateProgram(const VENUS::Render::Program::Desc& desc) = 0;
		virtual VENUS::Render::Texture* CreateTexture(const VENUS::Render::Texture::Desc& desc) = 0;
		virtual VENUS::Render::Target* CreateTarget(const VENUS::Render::Target::Desc& desc) = 0;
		virtual VENUS::Render::Depther* CreateDepther(const VENUS::Render::Depther::Desc& desc) = 0;

		virtual GAIA::BL SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB) = 0;
		virtual GAIA::BL SetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, VENUS::Render::VertexBuffer* pVB) = 0;
		virtual GAIA::BL SetVertexDeclaration(VENUS::Render::Context& ctx, VENUS::Render::VertexDeclaration* pVDecl) = 0;
		virtual GAIA::BL SetProgram(VENUS::Render::Context& ctx, VENUS::Render::Program* pProgram) = 0;
		virtual GAIA::BL SetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex, VENUS::Render::Texture* pTex) = 0;
		virtual GAIA::BL SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget) = 0;
		virtual GAIA::BL SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther) = 0;

		virtual VENUS::Render::IndexBuffer* GetIndexBuffer(VENUS::Render::Context& ctx) = 0;
		virtual VENUS::Render::VertexBuffer* GetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex) = 0;
		virtual VENUS::Render::VertexDeclaration* GetVertexDeclaration(VENUS::Render::Context& ctx) = 0;
		virtual VENUS::Render::Program* GetProgram(VENUS::Render::Context& ctx) = 0;
		virtual VENUS::Render::Texture* GetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex) = 0;
		virtual VENUS::Render::Target* GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex) = 0;
		virtual VENUS::Render::Depther* GetDepther(VENUS::Render::Context& ctx) = 0;

		/* Draw function. */
		virtual GAIA::BL ClearTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& cr) = 0;
		virtual GAIA::BL ClearDepther(VENUS::Render::Context& ctx, GAIA::REAL rDepth) = 0;
		virtual GAIA::BL SetVertexBufferBase(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, GAIA::SIZE sBaseIndex) = 0;
		virtual GAIA::BL SetIndexBufferBase(VENUS::Render::Context& ctx, GAIA::SIZE sBaseIndex) = 0;
		virtual GAIA::BL Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount) = 0;
	};
};

#endif