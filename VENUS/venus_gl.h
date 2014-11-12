#ifndef		__VENUS_GL_H__
#define		__VENUS_GL_H__

#include "venus_interface.h"

namespace VENUS
{
	class RenderGL : virtual public VENUS::Render
	{
	public:
		class Desc : public VENUS::Render::Desc
		{
		public:
			virtual GAIA::GVOID reset();
			virtual GAIA::BL check() const;
		};

		class Context : virtual public VENUS::Render::Context
		{
		public:
		};

		class IndexBuffer : virtual public VENUS::Render::IndexBuffer
		{
		public:
			virtual GAIA::GVOID* Lock(VENUS::Render::LOCK_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize);
			virtual GAIA::BL Unlock();
			virtual GAIA::BL IsLocked() const;
		};

		class VertexBuffer : virtual public VENUS::Render::VertexBuffer
		{

		public:
			virtual GAIA::GVOID* Lock(VENUS::Render::LOCK_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize);
			virtual GAIA::BL Unlock();
			virtual GAIA::BL IsLocked() const;
		};

		class VertexDeclaration : virtual public VENUS::Render::VertexDeclaration
		{
		public:
		};

		class Shader : virtual public VENUS::Render::Shader
		{
		public:
			virtual GAIA::BL Compile(const GAIA::GVOID* p);
		};

		class Texture : virtual public VENUS::Render::Texture
		{
		public:
			virtual GAIA::GVOID* Lock(VENUS::Render::LOCK_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, GAIA::SIZE sMipIndex, GAIA::SIZE sFaceIndex);
			virtual GAIA::BL Unlock();
			virtual GAIA::BL IsLocked() const;
		};

		class Target : virtual public VENUS::Render::Target
		{
		public:
			virtual GAIA::GVOID* Lock(VENUS::Render::LOCK_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize);
			virtual GAIA::BL Unlock();
			virtual GAIA::BL IsLocked() const;
		};

		class Depther : virtual public VENUS::Render::Depther
		{
		public:
			virtual GAIA::GVOID* Lock(VENUS::Render::LOCK_METHOD lm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize);
			virtual GAIA::BL Unlock();
			virtual GAIA::BL IsLocked() const;
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
		virtual GAIA::BL Present();

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
		virtual VENUS::Render::Texture* CreateTexture(const VENUS::Render::Texture::Desc& desc);
		virtual VENUS::Render::Target* CreateTarget(const VENUS::Render::Target::Desc& desc);
		virtual VENUS::Render::Depther* CreateDepther(const VENUS::Render::Depther::Desc& desc);

		virtual GAIA::BL SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB);
		virtual GAIA::BL SetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, VENUS::Render::VertexBuffer* pVB);
		virtual GAIA::BL SetVertexDeclaration(VENUS::Render::Context& ctx, VENUS::Render::VertexDeclaration* pVDecl);
		virtual GAIA::BL SetShader(VENUS::Render::Context& ctx, VENUS::Render::Shader* pShader);
		virtual GAIA::BL SetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex, VENUS::Render::Texture* pTex);
		virtual GAIA::BL SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget);
		virtual GAIA::BL SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther);

		virtual VENUS::Render::IndexBuffer* GetIndexBuffer(VENUS::Render::Context& ctx);
		virtual VENUS::Render::VertexBuffer* GetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex);
		virtual VENUS::Render::VertexDeclaration* GetVertexDeclaration(VENUS::Render::Context& ctx);
		virtual VENUS::Render::Shader* GetShader(VENUS::Render::Context& ctx);
		virtual VENUS::Render::Texture* GetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex);
		virtual VENUS::Render::Target* GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex);
		virtual VENUS::Render::Depther* GetDepther(VENUS::Render::Context& ctx);

		/* Draw function. */
		virtual GAIA::BL ClearTarget(GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& argb);
		virtual GAIA::BL ClearDepther(GAIA::REAL rDepth);
		virtual GAIA::BL SetVertexBufferBase(GAIA::SIZE sStreamIndex, GAIA::SIZE sBaseIndex);
		virtual GAIA::BL SetIndexBufferBase(GAIA::SIZE sBaseIndex);
		virtual GAIA::BL Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount);

	private:
		GAIA::GVOID init();

	private:
		GAIA::BL m_bCreated;
		GAIA::BL m_bBegin;
		VENUS::RenderGL::Desc m_desc;
	};
};

#endif

