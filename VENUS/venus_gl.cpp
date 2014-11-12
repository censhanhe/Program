#include	"venus.h"
#include	"venus_gl.h"

namespace VENUS
{
	GAIA::GVOID RenderGL::Desc::reset()
	{
	}
	GAIA::BL RenderGL::Desc::check() const
	{
		return GAIA::True;
	}
	GAIA::FWORK::ClsID RenderGL::GetClassID() const
	{
		return VENUS::CLSID_VENUS_RENDERGL;
	}
	RenderGL::RenderGL()
	{
		this->init();
	}
	RenderGL::~RenderGL()
	{
	}
	GAIA::BL RenderGL::Create(const VENUS::Render::Desc& desc)
	{
		if(this->IsCreated())
			return GAIA::False;
		m_bCreated = GAIA::True;
		return GAIA::True;
	}
	GAIA::BL RenderGL::Destroy()
	{
		if(!this->IsCreated())
			return GAIA::False;
		m_bCreated = GAIA::False;
		return GAIA::True;
	}
	GAIA::BL RenderGL::IsCreated() const
	{
		return m_bCreated;
	}
	const VENUS::Render::Desc& RenderGL::GetDesc() const
	{
		return m_desc;
	}
	VENUS::Render::Context* RenderGL::CreateContext()
	{
		VENUS::RenderGL::Context* pContext = new VENUS::RenderGL::Context;
		return pContext;
	}
	GAIA::BL RenderGL::Begin(VENUS::Render::Context& ctx)
	{
		if(this->IsBegin(ctx))
			return GAIA::False;
		m_bBegin = GAIA::True;
		return GAIA::True;
	}
	GAIA::BL RenderGL::End(VENUS::Render::Context& ctx)
	{
		if(!this->IsBegin(ctx))
			return GAIA::False;
		m_bBegin = GAIA::False;
		return GAIA::True;
	}
	GAIA::BL RenderGL::IsBegin(VENUS::Render::Context& ctx) const
	{
		return m_bBegin;
	}
	GAIA::BL RenderGL::Flush(VENUS::Render::Context& ctx, GAIA::BL bWaitComplete)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::Present()
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, const GAIA::CTN::Vari& v)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, const GAIA::CTN::Vari& v)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, const GAIA::CTN::Vari& v)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, GAIA::CTN::Vari& v)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, GAIA::CTN::Vari& v)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, GAIA::CTN::Vari& v)
	{
		return GAIA::True;
	}
	VENUS::Render::IndexBuffer* RenderGL::CreateIndexBuffer(const VENUS::Render::IndexBuffer::Desc& desc)
	{
		return GNIL;
	}
	VENUS::Render::VertexBuffer* RenderGL::CreateVertexBuffer(const VENUS::Render::VertexBuffer::Desc& desc)
	{
		return GNIL;
	}
	VENUS::Render::VertexDeclaration* RenderGL::CreateVertexDeclaration(const VENUS::Render::VertexDeclaration::Desc& desc)
	{
		return GNIL;
	}
	VENUS::Render::Shader* RenderGL::CreateShader(const VENUS::Render::Shader::Desc& desc)
	{
		return GNIL;
	}
	VENUS::Render::Texture* RenderGL::CreateTexture(const VENUS::Render::Texture::Desc& desc)
	{
		return GNIL;
	}
	VENUS::Render::Target* RenderGL::CreateTarget(const VENUS::Render::Target::Desc& desc)
	{
		return GNIL;
	}
	VENUS::Render::Depther* RenderGL::CreateDepther(const VENUS::Render::Depther::Desc& desc)
	{
		return GNIL;
	}
	GAIA::BL RenderGL::SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, VENUS::Render::VertexBuffer* pVB)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexDeclaration(VENUS::Render::Context& ctx, VENUS::Render::VertexDeclaration* pVDecl)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetShader(VENUS::Render::Context& ctx, VENUS::Render::Shader* pShader)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex, VENUS::Render::Texture* pTex)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther)
	{
		return GAIA::True;
	}
	VENUS::Render::IndexBuffer* RenderGL::GetIndexBuffer(VENUS::Render::Context& ctx)
	{
		return GNIL;
	}
	VENUS::Render::VertexBuffer* RenderGL::GetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex)
	{
		return GNIL;
	}
	VENUS::Render::VertexDeclaration* RenderGL::GetVertexDeclaration(VENUS::Render::Context& ctx)
	{
		return GNIL;
	}
	VENUS::Render::Shader* RenderGL::GetShader(VENUS::Render::Context& ctx)
	{
		return GNIL;
	}
	VENUS::Render::Texture* RenderGL::GetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex)
	{
		return GNIL;
	}
	VENUS::Render::Target* RenderGL::GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex)
	{
		return GNIL;
	}
	VENUS::Render::Depther* RenderGL::GetDepther(VENUS::Render::Context& ctx)
	{
		return GNIL;
	}
	GAIA::BL RenderGL::ClearTarget(GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& argb)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::ClearDepther(GAIA::REAL rDepth)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexBufferBase(GAIA::SIZE sStreamIndex, GAIA::SIZE sBaseIndex)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetIndexBufferBase(GAIA::SIZE sBaseIndex)
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount)
	{
		return GAIA::True;
	}
	GAIA::GVOID RenderGL::init()
	{
		m_bCreated = GAIA::False;
		m_bBegin = GAIA::False;
	}
};