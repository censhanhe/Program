#include "../venus.h"
#include "gaia_global_impl.h"

class ScreenVertex
{
public:
	GAIA::MATH::VEC2<GAIA::F32> pos;
	GAIA::MATH::ARGB<GAIA::F32> cr;
	GAIA::MATH::VEC2<GAIA::F32> tc;
};

class Vertex
{
public:
};

static const GAIA::CH VERTEXSHADERSTRING[] = 
"\
attribute vec2 a_pos;\
attribute vec4 a_cr;\
attribute vec2 a_tc;\
varying vec4 v_cr;\
varying vec2 v_tc;\
void main()\
{\
	gl_Position = vec4(a_pos.x, a_pos.y, 0.5, 1.0);\
	v_cr = a_cr;\
	v_tc = a_tc;\
}\
";

static const GAIA::CH PIXELSHADERSTRING[] = 
"\
varying vec4 v_cr;\
varying vec2 v_tc;\
uniform float u_time;\
uniform sampler2D u_tex;\
void main()\
{\
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * v_cr * abs(sin(u_time)) * texture2D(u_tex, v_tc);\
}\
";

class Resource
{
public:
	Resource(){this->init();}
	~Resource(){this->Destroy();}
	GAIA::BL Create(VENUS::Render& r, VENUS::Render::Context& ctx)
	{
		{
			VENUS::Render::VertexBuffer::Desc descVB;
			descVB.reset();
			descVB.sElementCount = 3;
			descVB.sElementSize = sizeof(GAIA::MATH::VEC2<GAIA::F32>);
			pScreenTriangleVB = r.CreateVertexBuffer(descVB);
			ScreenVertex v[3];
			v[0].pos = GAIA::MATH::VEC2<GAIA::F32>(-0.5F, -0.5F);
			v[1].pos = GAIA::MATH::VEC2<GAIA::F32>(+0.5F, -0.5F);
			v[2].pos = GAIA::MATH::VEC2<GAIA::F32>(0.0F, 0.5F);
			v[0].cr = GAIA::MATH::ARGB<GAIA::F32>(1.0F, 1.0F, 0.0F, 0.0F);
			v[1].cr = GAIA::MATH::ARGB<GAIA::F32>(1.0F, 0.0F, 1.0F, 0.0F);
			v[2].cr = GAIA::MATH::ARGB<GAIA::F32>(1.0F, 0.0F, 0.0F, 1.0F);
			v[0].tc = GAIA::MATH::VEC2<GAIA::F32>(-1.0F, -1.0F);
			v[1].tc = GAIA::MATH::VEC2<GAIA::F32>(-1.0F, 2.0F);
			v[2].tc = GAIA::MATH::VEC2<GAIA::F32>(2.0F, 2.0F);
			pScreenTriangleVB->Commit(VENUS::Render::COMMIT_METHOD_WRITE, 0, sizeof(v), v);

			VENUS::Render::IndexBuffer::Desc descIB;
			descIB.reset();
			descIB.fmt = VENUS::Render::FORMAT_INDEX16;
			descIB.sCount = 3;
			pScreenTriangleIB = r.CreateIndexBuffer(descIB);
			GAIA::U16 i[3] = {0, 1, 2};
			pScreenTriangleIB->Commit(VENUS::Render::COMMIT_METHOD_WRITE, 0, sizeof(i), i);

			VENUS::Render::Shader::Desc descVShader;
			descVShader.reset();
			descVShader.type = VENUS::Render::SHADER_TYPE_VERTEXSHADER;
			pScreenVShader = r.CreateShader(descVShader);
			pScreenVShader->Commit(VERTEXSHADERSTRING);

			VENUS::Render::Shader::Desc descPShader;
			descPShader.reset();
			descPShader.type = VENUS::Render::SHADER_TYPE_PIXELSHADER;
			pScreenPShader = r.CreateShader(descPShader);
			pScreenPShader->Commit(PIXELSHADERSTRING);

			VENUS::Render::Program::Desc descProgram;
			descProgram.reset();
			descProgram.pVS = pScreenVShader;
			descProgram.pPS = pScreenPShader;
			pScreenProgram = r.CreateProgram(descProgram);

			VENUS::Render::Texture::Desc descTex;
			descTex.reset();
			descTex.type = VENUS::Render::TEXTURE_TYPE_2D;
			descTex.fmt = VENUS::Render::FORMAT_A8R8G8B8;
			descTex.sSizeX = 128;
			descTex.sSizeY = 128;
			pTex = r.CreateTexture(descTex);
			{
				GAIA::MATH::ARGB<GAIA::U8>* pTexData = new GAIA::MATH::ARGB<GAIA::U8>[descTex.sSizeX * descTex.sSizeY];
				for(GAIA::SIZE y = 0; y < descTex.sSizeY; ++y)
				{
					for(GAIA::SIZE x = 0; x < descTex.sSizeX; ++x)
					{
						pTexData[y * descTex.sSizeX + x].a = 255;
						pTexData[y * descTex.sSizeX + x].r = GAIA::MATH::xrandom() % 255;
						pTexData[y * descTex.sSizeX + x].g = GAIA::MATH::xrandom() % 255;
						pTexData[y * descTex.sSizeX + x].b = 255;
					}
				}
				pTex->Commit(VENUS::Render::COMMIT_METHOD_WRITE, 0, descTex.sSizeX * descTex.sSizeY * 4, 0, 0, pTexData);
				GAIA_DELETE_SAFE(pTexData);
			}
			r.SetSamplerState(ctx, VENUS::Render::SAMPLER_STATE_MINFILTER, VENUS::Render::FILTER_NEAREST);
			r.SetSamplerState(ctx, VENUS::Render::SAMPLER_STATE_MAXFILTER, VENUS::Render::FILTER_NEAREST);
			r.SetSamplerState(ctx, VENUS::Render::SAMPLER_STATE_UNWRAPMODEU, VENUS::Render::UNWRAPMODE_CLAMP);
			r.SetSamplerState(ctx, VENUS::Render::SAMPLER_STATE_UNWRAPMODEV, VENUS::Render::UNWRAPMODE_CLAMP);
		}
		return GAIA::True;
	}
	GAIA::BL Destroy()
	{
		GAIA_RELEASE_SAFE(pScreenTriangleVB);
		GAIA_RELEASE_SAFE(pScreenTriangleIB);
		GAIA_RELEASE_SAFE(pScreenVShader);
		GAIA_RELEASE_SAFE(pScreenPShader);
		GAIA_RELEASE_SAFE(pScreenProgram);
		GAIA_RELEASE_SAFE(pTex);
		return GAIA::True;
	}
public:
	VENUS::Render::VertexBuffer* pScreenTriangleVB;
	VENUS::Render::IndexBuffer* pScreenTriangleIB;
	VENUS::Render::Shader* pScreenVShader;
	VENUS::Render::Shader* pScreenPShader;
	VENUS::Render::Program* pScreenProgram;
	VENUS::Render::Texture* pTex;
private:
	GAIA::GVOID init()
	{
		pScreenTriangleVB = GNIL;
		pScreenTriangleIB = GNIL;
		pScreenVShader = GNIL;
		pScreenPShader = GNIL;
		pScreenProgram = GNIL;
		pTex = GNIL;
	}
};

static GAIA::BL FrameLoop(VENUS::Render::Context& ctx, VENUS::Render& r, Resource& res)
{
	// Clear.
	GAIA::MATH::ARGB<GAIA::REAL> crClear;
	crClear.fromu32(0xFF8080FF);
	crClear.torealmode();
	r.ClearTarget(ctx, 0, crClear);

	// Draw screen triangle.
	r.SetTexture(ctx, "u_tex", res.pTex);
	r.SetVertexBuffer(ctx, "a_pos", res.pScreenTriangleVB, sizeof(ScreenVertex), 0);
	r.SetVertexBuffer(ctx, "a_cr", res.pScreenTriangleVB, sizeof(ScreenVertex), sizeof(GAIA::MATH::VEC2<GAIA::F32>));
	r.SetVertexBuffer(ctx, "a_tc", res.pScreenTriangleVB, sizeof(ScreenVertex), sizeof(GAIA::MATH::VEC2<GAIA::F32>) + sizeof(GAIA::MATH::ARGB<GAIA::F32>));
	r.SetIndexBuffer(ctx, res.pScreenTriangleIB);
	r.SetProgram(ctx, res.pScreenProgram);
	GAIA::F32 fTime = (GAIA::F32)GAIA::TIME::tick_time() / 1000.0F / 1000.0F;
	r.SetConstant(ctx, "u_time", &fTime, 1, 1, 1);
	r.SetElementType(ctx, VENUS::Render::ELEMENT_TYPE_TRIANGLELIST);
	r.Draw(ctx, 1);

	// Flush.
	r.Flush(ctx, GAIA::True);

	return GAIA::True;
}

int main()
{
	GAIA::FWORK::Factory fac;

	// New canvas instance.
	GAIA::UI::Canvas* pCanvas = GDCAST(GAIA::UI::Canvas*)(fac.CreateInstance(GAIA::FWORK::CLSID_UI_CANVAS, GNIL));
	if(pCanvas == GNIL)
		return -1;

	// Create canvas.
	GAIA::UI::Canvas::Desc descCanvas;
	descCanvas.reset();
	descCanvas.pszCaptionText = _T("Hello Venus!");
	pCanvas->Create(descCanvas);
	pCanvas->Show(GAIA::True);

	//
	VENUS::Initialize(fac);
	{
		// Alloc render instance.
		VENUS::Render* pRender = GDCAST(VENUS::Render*)(fac.CreateInstance(VENUS::CLSID_VENUS_RENDERGL, GNIL));
		if(pRender == GNIL)
		{
			VENUS::Release(fac);
			pCanvas->Release();
			return -1;
		}

		// Create render.
		VENUS::Render::Desc descRender;
		descRender.reset();
		descRender.pCanvas = pCanvas;
		pRender->Create(descRender);

		// Create context.
		VENUS::Render::Context* pContext = pRender->CreateContext();

		// Create resource.
		Resource res;
		res.Create(*pRender, *pContext);

		// 
		for(;;)
		{
			GAIA::BL bExistMsg;
			if(!GAIA::UI::UpdateMessage(GAIA::False, bExistMsg))
				break;
			if(!bExistMsg)
				FrameLoop(*pContext, *pRender, res);
		}

		// Release resource.
		res.Destroy();

		// Release context.
		pContext->Release();

		// Destroy render.
		pRender->Destroy();

		// Release render instance.
		pRender->Release();
	}
	VENUS::Release(fac);

	// Release canvas instance.
	pCanvas->Release();
	
	return 0;
}