#include	"venus.h"
#include	"venus_render_gl.h"

#include	<gl/gl.h>

namespace VENUS
{
	RenderGL::Context::Context()
	{
		this->init();
	}
	RenderGL::Context::~Context()
	{
		GAIA_RELEASE_SAFE(pIB);
		for(GAIA::SIZE x = 0; x < sizeofarray(pVB); ++x)
			GAIA_RELEASE_SAFE(pVB[x]);
		GAIA_RELEASE_SAFE(pVDecl);
		GAIA_RELEASE_SAFE(pVS);
		GAIA_RELEASE_SAFE(pPS);
		for(GAIA::SIZE x = 0; x < sizeofarray(pTex); ++x)
			GAIA_RELEASE_SAFE(pTex[x]);
		for(GAIA::SIZE x = 0; x < sizeofarray(pTarget); ++x)
			GAIA_RELEASE_SAFE(pTarget[x]);
		GAIA_RELEASE_SAFE(pDepther);
		this->init();
	}
	GAIA::GVOID RenderGL::Context::init()
	{
		eletype = VENUS::Render::ELEMENT_TYPE_TRIANGLELIST;
		pIB = GNIL;
		GAIA::ALGO::nil(pVB, sizeofarray(pVB));
		pVDecl = GNIL;
		pVS = GNIL;
		pPS = GNIL;
		GAIA::ALGO::nil(pTex, sizeofarray(pTex));
		GAIA::ALGO::nil(pTarget, sizeofarray(pTarget));
		pDepther = GNIL;
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
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::Create(const VENUS::Render::Desc& desc)
	{
		if(this->IsCreated())
			return GAIA::False;
		if(!desc.check())
			return GAIA::False;

	#if GAIA_OS == GAIA_OS_WINDOWS
		HWND hWnd = GSCAST(HWND)(desc.pCanvas->GetHandle());
		m_hDC = ::GetDC(hWnd);

		PIXELFORMATDESCRIPTOR pfd;
		GAIA::ALGO::xmemset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cRedBits = pfd.cRedShift = pfd.cGreenBits = pfd.cGreenShift = pfd.cBlueBits = pfd.cBlueShift = 0;
		pfd.cAlphaBits = pfd.cAlphaShift = 0;
		pfd.cAccumBits = 0;
		pfd.cAccumRedBits = pfd.cAccumGreenBits = pfd.cAccumBlueBits = pfd.cAccumAlphaBits = 0;
		pfd.cDepthBits = 32;
		pfd.cStencilBits = 0;
		pfd.cAuxBuffers= 0;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.bReserved = 0;
		pfd.dwLayerMask = pfd.dwVisibleMask = pfd.dwDamageMask = 0;

		GAIA::N32 nIndex = ::ChoosePixelFormat(m_hDC, &pfd);
		if(nIndex == 0)
		{
			::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;

			m_desc.pCanvas->Release();
			m_desc.pCanvas = GNIL;
			m_desc.reset();

			return GAIA::False;
		}

		if(!::SetPixelFormat(m_hDC, nIndex, &pfd))
		{
			::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;

			m_desc.pCanvas->Release();
			m_desc.pCanvas = GNIL;
			m_desc.reset();

			return GAIA::False;
		}

		m_hGLRC = ::wglCreateContext(m_hDC);
		if(m_hGLRC == GNIL)
		{
			::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;

			m_desc.pCanvas->Release();
			m_desc.pCanvas = GNIL;
			m_desc.reset();

			return GAIA::False;
		}

		if(!::wglMakeCurrent(m_hDC, m_hGLRC))
		{
			::wglDeleteContext(m_hGLRC);
			m_hGLRC = GNIL;

			::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;

			m_desc.pCanvas->Release();
			m_desc.pCanvas = GNIL;
			m_desc.reset();

			return GAIA::False;
		}
	#endif

		m_desc = desc;
		m_desc.pCanvas->Reference();

		m_bCreated = GAIA::True;
		return GAIA::True;
	}
	GAIA::BL RenderGL::Destroy()
	{
		if(!this->IsCreated())
			return GAIA::False;

	#if GAIA_OS == GAIA_OS_WINDOWS
		if(m_hGLRC != GNIL)
		{
			::wglDeleteContext(m_hGLRC);
			m_hGLRC = GNIL;
		}

		if(m_hDC != GNIL)
		{
			HWND hWnd = GSCAST(HWND)(m_desc.pCanvas->GetHandle());
			if(hWnd != GNIL)	// Because windows window can be destroy by user, so the handle could be GNIL. 
								// Search ::PostQuitMessage in gaia will find out the reason.
				::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;
		}
	#endif

		m_desc.pCanvas->Release();
		m_desc.pCanvas = GNIL;

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
		GPCHR_TRUE_RET(this->IsBegin(ctx), GAIA::False);
	#if GAIA_OS == GAIA_OS_WINDOWS
		if(m_hDC == GNIL)
			return GAIA::False;
	#endif
		if(bWaitComplete)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::SwapBuffers(m_hDC);
		#else
			::glFinish();
		#endif
		}
		else
			::glFlush();

		return GAIA::True;
	}
	GAIA::BL RenderGL::SetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, const GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::RENDER_STATE_ALPHABLEND:
			{
				if((GAIA::BL)v)
					::glEnable(GL_BLEND);
				else
					::glDisable(GL_BLEND);
			}
			break;
		case VENUS::Render::RENDER_STATE_ALPHATEST:
			{
				if((GAIA::BL)v)
					::glEnable(GL_ALPHA_TEST);
				else
					::glDisable(GL_ALPHA_TEST);
			}
			break;
		case VENUS::Render::RENDER_STATE_ALPHAFUNC:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ALPHAREF:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZTEST:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZFUNC:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZWRITE:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_CULL:
			{
			}
			break;
		default:
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, const GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::SAMPLER_STATE_MINFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MAXFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MIPFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_BORDERCOLOR:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_BORDER:
			{
			}
			break;
		default:
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, const GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::QUALITY_STATE_ANTIALIAS:
			{
			}
			break;
		case VENUS::Render::QUALITY_STATE_FONTANTIALIAS:
			{
			}
			break;
		default:
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::RENDER_STATE_ALPHABLEND:
			{
				if(::glIsEnabled(GL_BLEND))
					v = GAIA::True;
				else
					v = GAIA::False;
			}
			break;
		case VENUS::Render::RENDER_STATE_ALPHATEST:
			{
				if(::glIsEnabled(GL_ALPHA_TEST))
					v = GAIA::True;
				else
					v = GAIA::False;
			}
			break;
		case VENUS::Render::RENDER_STATE_ALPHAFUNC:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ALPHAREF:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZTEST:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZFUNC:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZWRITE:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_CULL:
			{
			}
			break;
		default:
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::SAMPLER_STATE_MINFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MAXFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MIPFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_BORDERCOLOR:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_BORDER:
			{
			}
			break;
		default:
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::QUALITY_STATE_ANTIALIAS:
			{
			}
			break;
		case VENUS::Render::QUALITY_STATE_FONTANTIALIAS:
			{
			}
			break;
		default:
			return GAIA::False;
		}
		return GAIA::True;
	}
	VENUS::Render::IndexBuffer* RenderGL::CreateIndexBuffer(const VENUS::Render::IndexBuffer::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		return GNIL;
	}
	VENUS::Render::VertexBuffer* RenderGL::CreateVertexBuffer(const VENUS::Render::VertexBuffer::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		return GNIL;
	}
	VENUS::Render::VertexDeclaration* RenderGL::CreateVertexDeclaration(const VENUS::Render::VertexDeclaration::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		return GNIL;
	}
	VENUS::Render::Shader* RenderGL::CreateShader(const VENUS::Render::Shader::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		return GNIL;
	}
	VENUS::Render::Texture* RenderGL::CreateTexture(const VENUS::Render::Texture::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		return GNIL;
	}
	VENUS::Render::Target* RenderGL::CreateTarget(const VENUS::Render::Target::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		return GNIL;
	}
	VENUS::Render::Depther* RenderGL::CreateDepther(const VENUS::Render::Depther::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		return GNIL;
	}
	GAIA::BL RenderGL::SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, VENUS::Render::VertexBuffer* pVB)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexDeclaration(VENUS::Render::Context& ctx, VENUS::Render::VertexDeclaration* pVDecl)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetShader(VENUS::Render::Context& ctx, VENUS::Render::Shader* pShader)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex, VENUS::Render::Texture* pTex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	VENUS::Render::IndexBuffer* RenderGL::GetIndexBuffer(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::VertexBuffer* RenderGL::GetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::VertexDeclaration* RenderGL::GetVertexDeclaration(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::Shader* RenderGL::GetShader(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::Texture* RenderGL::GetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::Target* RenderGL::GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::Depther* RenderGL::GetDepther(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	GAIA::BL RenderGL::ClearTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& cr)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		::glClearColor(cr.r, cr.g, cr.b, cr.a);
		::glClear(GL_COLOR_BUFFER_BIT);
		return GAIA::True;
	}
	GAIA::BL RenderGL::ClearDepther(VENUS::Render::Context& ctx, GAIA::REAL rDepth)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		::glClearDepth(rDepth);
		::glClear(GL_DEPTH_BUFFER_BIT);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexBufferBase(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, GAIA::SIZE sBaseIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetIndexBufferBase(VENUS::Render::Context& ctx, GAIA::SIZE sBaseIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		GLenum mode;
		switch(pContext->eletype)
		{
		case VENUS::Render::ELEMENT_TYPE_SLINE:
			mode = GL_LINES;
			break;
		case VENUS::Render::ELEMENT_TYPE_SLINESTRIP:
			mode = GL_LINE_STRIP;
			break;
		case VENUS::Render::ELEMENT_TYPE_STRIANGLELIST:
			mode = GL_TRIANGLES;
			break;
		case VENUS::Render::ELEMENT_TYPE_STRIANGLEFAN:
			mode = GL_TRIANGLE_FAN;
			break;
		case VENUS::Render::ELEMENT_TYPE_STRIANGLESTRIP:
			mode = GL_TRIANGLE_STRIP;
			break;
		case VENUS::Render::ELEMENT_TYPE_SRECT:
			mode = GL_QUADS;
			break;
		case VENUS::Render::ELEMENT_TYPE_SPOLYGON:
			mode = GL_POLYGON;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLELIST:
			mode = GL_TRIANGLES;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLEFAN:
			mode = GL_TRIANGLE_FAN;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLESTRIP:
			mode = GL_TRIANGLE_STRIP;
			break;
		default:
			return GAIA::False;
		}
		::glDrawElements(mode, sElementCount, GL_UNSIGNED_SHORT, GNIL);
		return GAIA::True;
	}
	GAIA::GVOID RenderGL::init()
	{
		m_bCreated = GAIA::False;
		m_bBegin = GAIA::False;
	#if GAIA_OS == GAIA_OS_WINDOWS
		m_hDC = GNIL;
		m_hGLRC = GNIL;
	#endif
	}
};