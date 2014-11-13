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
		class Context : public virtual VENUS::Render::Context
		{
		public:
			Context();
			~Context();
		public:
			GAIA::GVOID init();
		public:
			VENUS::Render::ELEMENT_TYPE eletype;
			VENUS::Render::IndexBuffer* pIB;
			VENUS::Render::VertexBuffer* pVB[4];
			VENUS::Render::VertexDeclaration* pVDecl;
			VENUS::Render::Shader* pVS;
			VENUS::Render::Shader* pPS;
			VENUS::Render::Texture* pTex[4];
			VENUS::Render::Target* pTarget[4];
			VENUS::Render::Depther* pDepther;
		};

		class IndexBuffer : public virtual VENUS::Render::IndexBuffer
		{
		public:
			IndexBuffer();
			~IndexBuffer();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(const VENUS::Render::IndexBuffer::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		private:
			GAIA::U32 m_uIB;
		};

		class VertexBuffer : public virtual VENUS::Render::VertexBuffer
		{
		public:
			VertexBuffer();
			~VertexBuffer();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(const VENUS::Render::VertexBuffer::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		private:
			GAIA::U32 m_uVB;
		};

		class VertexDeclaration : public virtual VENUS::Render::VertexDeclaration
		{
		public:
			VertexDeclaration();
			~VertexDeclaration();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
		public:
			GAIA::BL Create(const VENUS::Render::VertexDeclaration::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		private:
		};

		class Program;
		class Shader : public virtual VENUS::Render::Shader
		{
			friend class Program;
		public:
			Shader();
			~Shader();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual GAIA::BL Commit(const GAIA::CH* p);
		public:
			GAIA::BL Create(const VENUS::Render::Shader::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		private:
			GAIA::U32 m_uShader;
		};

		class Program : public virtual VENUS::Render::Program
		{
		public:
			Program();
			~Program();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
		public:
			GAIA::BL Create(const VENUS::Render::Program::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		private:
			GAIA::U32 m_uProgram;
		};

		class Texture : public virtual VENUS::Render::Texture
		{
		public:
			Texture();
			~Texture();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, GAIA::SIZE sMipIndex, GAIA::SIZE sFaceIndex, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(const VENUS::Render::Texture::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		private:
		};

		class Target : public virtual VENUS::Render::Target
		{
		public:
			Target();
			~Target();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(const VENUS::Render::Target::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		private:
		};

		class Depther : public virtual VENUS::Render::Depther
		{
		public:
			Depther();
			~Depther();
			virtual GAIA::BL SaveToFile(GAIA::FSYS::FileBase* pFile) const;
			virtual GAIA::BL Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p);
		public:
			GAIA::BL Create(const VENUS::Render::Depther::Desc& desc);
			GAIA::BL Destroy();
			GAIA::BL IsCreated() const;
		private:
		};

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
		virtual VENUS::Render::VertexDeclaration* CreateVertexDeclaration(const VENUS::Render::VertexDeclaration::Desc& desc);
		virtual VENUS::Render::Shader* CreateShader(const VENUS::Render::Shader::Desc& desc);
		virtual VENUS::Render::Program* CreateProgram(const VENUS::Render::Program::Desc& desc);
		virtual VENUS::Render::Texture* CreateTexture(const VENUS::Render::Texture::Desc& desc);
		virtual VENUS::Render::Target* CreateTarget(const VENUS::Render::Target::Desc& desc);
		virtual VENUS::Render::Depther* CreateDepther(const VENUS::Render::Depther::Desc& desc);

		virtual GAIA::BL SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB);
		virtual GAIA::BL SetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, VENUS::Render::VertexBuffer* pVB);
		virtual GAIA::BL SetVertexDeclaration(VENUS::Render::Context& ctx, VENUS::Render::VertexDeclaration* pVDecl);
		virtual GAIA::BL SetProgram(VENUS::Render::Context& ctx, VENUS::Render::Program* pProgram);
		virtual GAIA::BL SetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex, VENUS::Render::Texture* pTex);
		virtual GAIA::BL SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget);
		virtual GAIA::BL SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther);

		virtual VENUS::Render::IndexBuffer* GetIndexBuffer(VENUS::Render::Context& ctx);
		virtual VENUS::Render::VertexBuffer* GetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex);
		virtual VENUS::Render::VertexDeclaration* GetVertexDeclaration(VENUS::Render::Context& ctx);
		virtual VENUS::Render::Program* GetProgram(VENUS::Render::Context& ctx);
		virtual VENUS::Render::Texture* GetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex);
		virtual VENUS::Render::Target* GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex);
		virtual VENUS::Render::Depther* GetDepther(VENUS::Render::Context& ctx);

		/* Draw function. */
		virtual GAIA::BL ClearTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& cr);
		virtual GAIA::BL ClearDepther(VENUS::Render::Context& ctx, GAIA::REAL rDepth);
		virtual GAIA::BL SetVertexBufferBase(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, GAIA::SIZE sBaseIndex);
		virtual GAIA::BL SetIndexBufferBase(VENUS::Render::Context& ctx, GAIA::SIZE sBaseIndex);
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
	};
};

#endif

