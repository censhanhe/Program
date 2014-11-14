#ifndef		__VENUS_RENDER_GL_H__
#define		__VENUS_RENDER_GL_H__

#include "venus_render.h"

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <windows.h>
#endif

namespace VENUS
{
	class RenderGL : public virtual VENUS::Render
	{
	public:
		class IndexBuffer;
		class VertexBuffer;
		class Shader;
		class Program;
		class Texture;
		class Target;
		class Depther;

	public:
		class Context : public virtual VENUS::Render::Context
		{
		public:
			class VertexBufferRec : public GAIA::Base
			{
			public:
				GAIA_CLASS_OPERATOR_COMPARE(sNameIndex, sNameIndex, VertexBufferRec);
			public:
				VENUS::RenderGL::VertexBuffer* pVB;
				GAIA::SIZE sNameIndex;
				GAIA::SIZE sOffset;
				GAIA::SIZE sStride;
			};
		public:
			Context();
			~Context();
		public:
			GAIA::GVOID init();
		public:
			VENUS::Render::ELEMENT_TYPE eletype;
			VENUS::RenderGL::IndexBuffer* pIB;
			GAIA::CTN::Set<VertexBufferRec> vbset;
			VENUS::RenderGL::Program* pProgram;
			VENUS::RenderGL::Texture* pTex[4];
			VENUS::RenderGL::Target* pTarget[4];
			VENUS::RenderGL::Depther* pDepther;
		};

		class IndexBuffer : public virtual VENUS::Render::IndexBuffer
		{
		public:
			IndexBuffer();
			~IndexBuffer();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual const VENUS::Render::IndexBuffer::Desc& GetDesc() const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(VENUS::RenderGL& r, const VENUS::Render::IndexBuffer::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		public:
			VENUS::Render::IndexBuffer::Desc m_desc;
			GAIA::U32 m_uIB;
		};

		class VertexBuffer : public virtual VENUS::Render::VertexBuffer
		{
		public:
			VertexBuffer();
			~VertexBuffer();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual const VENUS::Render::VertexBuffer::Desc& GetDesc() const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(VENUS::RenderGL& r, const VENUS::Render::VertexBuffer::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		public:
			VENUS::Render::VertexBuffer::Desc m_desc;
			GAIA::U32 m_uVB;
		};

		class Shader : public virtual VENUS::Render::Shader
		{
		public:
			Shader();
			~Shader();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual const VENUS::Render::Shader::Desc& GetDesc() const;
			virtual GAIA::BL Commit(const GAIA::CH* p);
		public:
			GAIA::BL Create(VENUS::RenderGL& r, const VENUS::Render::Shader::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		public:
			VENUS::Render::Shader::Desc m_desc;
			GAIA::U32 m_uShader;
		};

		class Program : public virtual VENUS::Render::Program
		{
		public:
			class Constant : public GAIA::Base
			{
			public:
				GAIA_CLASS_OPERATOR_COMPARE(sNameIndex, sNameIndex, Constant);
			public:
				GAIA::SIZE sNameIndex;
				GAIA::TYPEID type;
				GAIA::U16 uCount;
				GAIA::U8 uDimenX;
				GAIA::U8 uDimenY;
				GAIA::N8 nLocation;
			};
		public:
			Program();
			~Program();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual const VENUS::Render::Program::Desc& GetDesc() const;
		public:
			GAIA::BL Create(VENUS::RenderGL& r, const VENUS::Render::Program::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		public:
			GAIA::CTN::Vector<Constant> attrlist;
			GAIA::CTN::Vector<Constant> uniformlist;
		public:
			VENUS::Render::Program::Desc m_desc;
			GAIA::U32 m_uProgram;
		};

		class Texture : public virtual VENUS::Render::Texture
		{
		public:
			Texture();
			~Texture();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual const VENUS::Render::Texture::Desc& GetDesc() const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, GAIA::SIZE sMipIndex, GAIA::SIZE sFaceIndex, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(VENUS::RenderGL& r, const VENUS::Render::Texture::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		public:
			VENUS::Render::Texture::Desc m_desc;
		};

		class Target : public virtual VENUS::Render::Target
		{
		public:
			Target();
			~Target();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual const VENUS::Render::Target::Desc& GetDesc() const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(VENUS::RenderGL& r, const VENUS::Render::Target::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		public:
			VENUS::Render::Target::Desc m_desc;
		};

		class Depther : public virtual VENUS::Render::Depther
		{
		public:
			Depther();
			~Depther();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual const VENUS::Render::Depther::Desc& GetDesc() const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(VENUS::RenderGL& r, const VENUS::Render::Depther::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		public:
			VENUS::Render::Depther::Desc m_desc;
		};

	private:
		friend class Program;

	public:
		RenderGL();
		~RenderGL();

		/* Overload. */
		virtual GAIA::FWORK::ClsID GetClassID() const;

		/* Base. */
		virtual GAIA::BL Create(const VENUS::Render::Desc& desc);
		virtual GAIA::BL Destroy();
		virtual GAIA::BL IsCreated() const;
		virtual const VENUS::Render::Desc& GetDesc() const;
		virtual VENUS::Render::Context* CreateContext();
		virtual GAIA::BL Begin(VENUS::Render::Context& ctx);
		virtual GAIA::BL End(VENUS::Render::Context& ctx);
		virtual GAIA::BL IsBegin(VENUS::Render::Context& ctx) const;
		virtual GAIA::BL Flush(VENUS::Render::Context& ctx, GAIA::BL bWaitComplete);

		/* State function. */
		virtual GAIA::BL SetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, const GAIA::CTN::Vari& v);
		virtual GAIA::BL SetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, const GAIA::CTN::Vari& v);
		virtual GAIA::BL SetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, const GAIA::CTN::Vari& v);

		virtual GAIA::BL GetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, GAIA::CTN::Vari& v);
		virtual GAIA::BL GetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, GAIA::CTN::Vari& v);
		virtual GAIA::BL GetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, GAIA::CTN::Vari& v);

		/* Resource function. */
		virtual VENUS::Render::IndexBuffer* CreateIndexBuffer(const VENUS::Render::IndexBuffer::Desc& desc);
		virtual VENUS::Render::VertexBuffer* CreateVertexBuffer(const VENUS::Render::VertexBuffer::Desc& desc);
		virtual VENUS::Render::Shader* CreateShader(const VENUS::Render::Shader::Desc& desc);
		virtual VENUS::Render::Program* CreateProgram(const VENUS::Render::Program::Desc& desc);
		virtual VENUS::Render::Texture* CreateTexture(const VENUS::Render::Texture::Desc& desc);
		virtual VENUS::Render::Target* CreateTarget(const VENUS::Render::Target::Desc& desc);
		virtual VENUS::Render::Depther* CreateDepther(const VENUS::Render::Depther::Desc& desc);

		virtual GAIA::BL SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB);
		virtual GAIA::BL SetVertexBuffer(VENUS::Render::Context& ctx, const GAIA::CH* pszAttrName, VENUS::Render::VertexBuffer* pVB, GAIA::SIZE sStride, GAIA::SIZE sOffset);
		virtual GAIA::BL SetProgram(VENUS::Render::Context& ctx, VENUS::Render::Program* pProgram);
		virtual GAIA::BL SetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex, VENUS::Render::Texture* pTex);
		virtual GAIA::BL SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget);
		virtual GAIA::BL SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther);

		virtual VENUS::Render::IndexBuffer* GetIndexBuffer(VENUS::Render::Context& ctx);
		virtual VENUS::Render::VertexBuffer* GetVertexBuffer(VENUS::Render::Context& ctx, const GAIA::CH* pszAttrName, GAIA::SIZE& sStride, GAIA::SIZE& sOffset);
		virtual VENUS::Render::Program* GetProgram(VENUS::Render::Context& ctx);
		virtual VENUS::Render::Texture* GetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex);
		virtual VENUS::Render::Target* GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex);
		virtual VENUS::Render::Depther* GetDepther(VENUS::Render::Context& ctx);

		/* Program constant management. */
		virtual GAIA::BL SetConstant(VENUS::Render::Context& ctx, VENUS::Render::Program& prog, const GAIA::CH* pszUniformName, const GAIA::F32* p, GAIA::U8 uDimenX, GAIA::U8 uDimenY, GAIA::SIZE sCount);
		virtual GAIA::BL GetConstant(VENUS::Render::Context& ctx, VENUS::Render::Program& prog, const GAIA::CH* pszUniformName, GAIA::F32* p, GAIA::U8 uDimenX, GAIA::U8 uDimenY, GAIA::SIZE sCount);

		/* Draw function. */
		virtual GAIA::BL SetElementType(VENUS::Render::Context& ctx, VENUS::Render::ELEMENT_TYPE eletype);
		virtual VENUS::Render::ELEMENT_TYPE GetElementType(VENUS::Render::Context& ctx) const;
		virtual GAIA::BL ClearTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& cr);
		virtual GAIA::BL ClearDepther(VENUS::Render::Context& ctx, GAIA::REAL rDepth);
		virtual GAIA::BL Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount);

	private:
		GAIA::GVOID init();

	private:
		GAIA::BL m_bCreated;
		GAIA::BL m_bBegin;
		VENUS::Render::Desc m_desc;
	#if GAIA_OS == GAIA_OS_WINDOWS
		HDC m_hDC;
		HGLRC m_hGLRC;
	#endif
		GAIA::CTN::StaticStringPool<GAIA::CH> m_strpool;
	};
};

#endif

