#include "../venus.h"
#include "gaia_global_impl.h"

class ScreenVertex
{
public:
	GAIA::MATH::VEC2<GAIA::F32> pos;
};

class Vertex
{
public:
};

static const GAIA::CH VERTEXSHADERSTRING[] = 
"\
attribute vec4 a_pos;\
void main()\
{\
	gl_Position = a_pos;\
}\
";

static const GAIA::CH PIXELSHADERSTRING[] = 
"\
void main()\
{\
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\
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
			v[0].pos = GAIA::MATH::VEC2<GAIA::F32>(100, 100);
			v[1].pos = GAIA::MATH::VEC2<GAIA::F32>(200, 100);
			v[2].pos = GAIA::MATH::VEC2<GAIA::F32>(150, 150);
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