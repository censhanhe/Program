#include "../venus.h"
#include "gaia_global_impl.h"

class ScreenVertex
{
public:
	GAIA::MATH::VEC2<GAIA::F32> pos;
	GAIA::MATH::ARGB<GAIA::F32> cr;
};

class Vertex
{
public:
};

static const GAIA::CH VERTEXSHADERSTRING[] = 
"\
attribute vec2 a_pos;\
attribute vec4 a_cr;\
varying vec4 v_cr;\
void main()\
{\
	gl_Position = vec4(a_pos.x, a_pos.y, 0.5, 1.0);\
	v_cr = a_cr;\
}\
";

static const GAIA::CH PIXELSHADERSTRING[] = 
"\
varying vec4 v_cr;\
uniform float u_time;\
void main()\
{\
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * v_cr * abs(sin(u_time));\
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
		return GAIA::True;
	}
public:
	VENUS::Render::VertexBuffer* pScreenTriangleVB;
	VENUS::Render::IndexBuffer* pScreenTriangleIB;
	VENUS::Render::Shader* pScreenVShader;
	VENUS::Render::Shader* pScreenPShader;
	VENUS::Render::Program* pScreenProgram;
private:
	GAIA::GVOID init()
	{
		pScreenTriangleVB = GNIL;
		pScreenTriangleIB = GNIL;
		pScreenVShader = GNIL;
		pScreenPShader = GNIL;
		pScreenProgram = GNIL;
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
	r.SetVertexBuffer(ctx, "a_pos", res.pScreenTriangleVB, sizeof(ScreenVertex), 0);
	r.SetVertexBuffer(ctx, "a_cr", res.pScreenTriangleVB, sizeof(ScreenVertex), sizeof(GAIA::MATH::VEC2<GAIA::F32>));
	r.SetIndexBuffer(ctx, res.pScreenTriangleIB);
	r.SetProgram(ctx, res.pScreenProgram);
	GAIA::F32 fTime = (GAIA::F32)GAIA::TIME::tick_time() / 1000.0F / 1000.0F;
	r.SetConstant(ctx, *res.pScreenProgram, "u_time", &fTime, 1, 1, 1);
	r.GetConstant(ctx, *res.pScreenProgram, "u_time", &fTime, 1, 1, 1);
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