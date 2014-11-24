#include "../venus.h"
#include "gaia_global_impl.h"

class Vertex
{
public:
	GAIA::MATH::VEC3<GAIA::F32> pos;
	GAIA::MATH::VEC3<GAIA::F32> nor;
};

static const GAIA::CH VERTEXSHADERSTRING[] = 
"\
attribute vec3 a_pos;\
attribute vec3 a_nor;\
varying vec3 v_nor;\
uniform mat4 u_mtx;\
void main()\
{\
	gl_Position = u_mtx * vec4(a_pos.x, a_pos.y, a_pos.z, 1);\
	v_nor = (u_mtx * vec4(a_nor.x, a_nor.y, a_nor.z, 0)).xyz;\
}\
";

static const GAIA::CH PIXELSHADERSTRING[] = 
"\
varying vec3 v_nor;\
void main()\
{\
	gl_FragColor.xyz = v_nor;\
	gl_FragColor.w = 1;\
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
			// Create vertex buffer.
			VENUS::Render::VertexBuffer::Desc descVB;
			descVB.reset();
			descVB.sVertexCount = 3;
			descVB.sVertexSize = sizeof(GAIA::MATH::VEC2<GAIA::F32>);
			pTriangleVB = r.CreateVertexBuffer(descVB);
			Vertex v[6 * 4];

			GAIA::MATH::MTX44<GAIA::REAL> mtxR, mtx[6];
			mtx[0].identity();
			mtxR.rotatey(GAIA::MATH::PI * R(+0.5));
			mtx[1] = mtxR;
			mtxR.rotatey(GAIA::MATH::PI * R(-0.5));
			mtx[2] = mtxR;
			mtxR.rotatex(GAIA::MATH::PI * R(+0.5));
			mtx[3] = mtxR;
			mtxR.rotatex(GAIA::MATH::PI * R(-0.5));
			mtx[4] = mtxR;
			mtxR.rotatex(GAIA::MATH::PI);
			mtx[5] = mtxR;

			v[4 * 0 + 0].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, -1.0F, +1.0F) * mtx[0];
			v[4 * 0 + 1].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, -1.0F, +1.0F) * mtx[0];
			v[4 * 0 + 2].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, +1.0F, +1.0F) * mtx[0];
			v[4 * 0 + 3].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, +1.0F, +1.0F) * mtx[0];

			v[4 * 1 + 0].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, -1.0F, +1.0F) * mtx[1];
			v[4 * 1 + 1].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, -1.0F, +1.0F) * mtx[1];
			v[4 * 1 + 2].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, +1.0F, +1.0F) * mtx[1];
			v[4 * 1 + 3].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, +1.0F, +1.0F) * mtx[1];

			v[4 * 2 + 0].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, -1.0F, +1.0F) * mtx[2];
			v[4 * 2 + 1].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, -1.0F, +1.0F) * mtx[2];
			v[4 * 2 + 2].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, +1.0F, +1.0F) * mtx[2];
			v[4 * 2 + 3].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, +1.0F, +1.0F) * mtx[2];

			v[4 * 3 + 0].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, -1.0F, +1.0F) * mtx[3];
			v[4 * 3 + 1].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, -1.0F, +1.0F) * mtx[3];
			v[4 * 3 + 2].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, +1.0F, +1.0F) * mtx[3];
			v[4 * 3 + 3].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, +1.0F, +1.0F) * mtx[3];

			v[4 * 4 + 0].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, -1.0F, +1.0F) * mtx[4];
			v[4 * 4 + 1].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, -1.0F, +1.0F) * mtx[4];
			v[4 * 4 + 2].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, +1.0F, +1.0F) * mtx[4];
			v[4 * 4 + 3].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, +1.0F, +1.0F) * mtx[4];

			v[4 * 5 + 0].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, -1.0F, +1.0F) * mtx[5];
			v[4 * 5 + 1].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, -1.0F, +1.0F) * mtx[5];
			v[4 * 5 + 2].pos = GAIA::MATH::VEC3<GAIA::REAL>(+1.0F, +1.0F, +1.0F) * mtx[5];
			v[4 * 5 + 3].pos = GAIA::MATH::VEC3<GAIA::REAL>(-1.0F, +1.0F, +1.0F) * mtx[5];

			v[4 * 0 + 0].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[0];
			v[4 * 0 + 1].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[0];
			v[4 * 0 + 2].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[0];
			v[4 * 0 + 3].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[0];

			v[4 * 1 + 0].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[1];
			v[4 * 1 + 1].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[1];
			v[4 * 1 + 2].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[1];
			v[4 * 1 + 3].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[1];

			v[4 * 2 + 0].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[2];
			v[4 * 2 + 1].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[2];
			v[4 * 2 + 2].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[2];
			v[4 * 2 + 3].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[2];

			v[4 * 3 + 0].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[3];
			v[4 * 3 + 1].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[3];
			v[4 * 3 + 2].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[3];
			v[4 * 3 + 3].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[3];

			v[4 * 4 + 0].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[4];
			v[4 * 4 + 1].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[4];
			v[4 * 4 + 2].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[4];
			v[4 * 4 + 3].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[4];

			v[4 * 5 + 0].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[5];
			v[4 * 5 + 1].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[5];
			v[4 * 5 + 2].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[5];
			v[4 * 5 + 3].nor = GAIA::MATH::VEC3<GAIA::REAL>(+0.0F, +0.0F, +1.0F) * mtx[5];

			pTriangleVB->Commit(0, sizeof(v), v);

			// Create index buffer.
			VENUS::Render::IndexBuffer::Desc descIB;
			descIB.reset();
			descIB.fmt = VENUS::Render::FORMAT_INDEX16;
			descIB.sCount = 3;
			pTriangleIB = r.CreateIndexBuffer(descIB);
			GAIA::U16 i[6 * 2 * 3] = {0, 1, 2};
			for(GAIA::SIZE x = 0; x < 6; ++x)
			{
				i[x * 6 + 0] = 0 + x * 4;
				i[x * 6 + 1] = 1 + x * 4;
				i[x * 6 + 2] = 2 + x * 4;

				i[x * 6 + 3] = 0 + x * 4;
				i[x * 6 + 4] = 2 + x * 4;
				i[x * 6 + 5] = 3 + x * 4;
			}
			pTriangleIB->Commit(0, sizeof(i), i);

			// Create shader.
			VENUS::Render::Shader::Desc descVShader;
			descVShader.reset();
			descVShader.type = VENUS::Render::SHADER_TYPE_VERTEXSHADER;
			pVShader = r.CreateShader(descVShader);
			pVShader->Commit(VERTEXSHADERSTRING);

			VENUS::Render::Shader::Desc descPShader;
			descPShader.reset();
			descPShader.type = VENUS::Render::SHADER_TYPE_PIXELSHADER;
			pPShader = r.CreateShader(descPShader);
			pPShader->Commit(PIXELSHADERSTRING);

			VENUS::Render::Program::Desc descProgram;
			descProgram.reset();
			descProgram.pVS = pVShader;
			descProgram.pPS = pPShader;
			pProgram = r.CreateProgram(descProgram);
			GAIA_AST(pProgram != GNIL);

			// Create texture.
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
				pTex->Commit(0, descTex.sSizeX * descTex.sSizeY * 4, 0, 0, pTexData);
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
		GAIA_RELEASE_SAFE(pTriangleVB);
		GAIA_RELEASE_SAFE(pTriangleIB);
		GAIA_RELEASE_SAFE(pVShader);
		GAIA_RELEASE_SAFE(pPShader);
		GAIA_RELEASE_SAFE(pProgram);
		GAIA_RELEASE_SAFE(pTex);
		return GAIA::True;
	}
public:
	VENUS::Render::VertexBuffer* pTriangleVB;
	VENUS::Render::IndexBuffer* pTriangleIB;
	VENUS::Render::Shader* pVShader;
	VENUS::Render::Shader* pPShader;
	VENUS::Render::Program* pProgram;
	VENUS::Render::Texture* pTex;
private:
	GAIA::GVOID init()
	{
		pTriangleVB = GNIL;
		pTriangleIB = GNIL;
		pVShader = GNIL;
		pPShader = GNIL;
		pProgram = GNIL;
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
	r.ClearDepther(ctx, R(1.0));

	r.SetRenderState(ctx, VENUS::Render::RENDER_STATE_ZTEST, GAIA::True);

	// Draw box.
	r.SetTexture(ctx, "u_tex", res.pTex);
	r.SetVertexBuffer(ctx, "a_pos", res.pTriangleVB, sizeof(Vertex), 0);
	r.SetVertexBuffer(ctx, "a_nor", res.pTriangleVB, sizeof(Vertex), sizeof(GAIA::MATH::VEC3<GAIA::F32>));
	r.SetIndexBuffer(ctx, res.pTriangleIB);
	r.SetProgram(ctx, res.pProgram);
	r.SetElementType(ctx, VENUS::Render::ELEMENT_TYPE_TRIANGLELIST);
	GAIA::MATH::MTX44<GAIA::REAL> mtxRotate, mtxView, mtxProj, mtxCombin;
	GAIA::REAL rAspect = (GAIA::REAL)r.GetDesc().pCanvas->Size().y / (GAIA::REAL)r.GetDesc().pCanvas->Size().x;
	static GAIA::REAL s_rRotate = 0.0F;
	s_rRotate += R(0.001);
	mtxRotate.rotatex(s_rRotate);
	mtxView.look(
		GAIA::MATH::VEC3<GAIA::REAL>(R(0.0), R(0.0), R(-10.0)), 
		GAIA::MATH::VEC3<GAIA::REAL>(R(0.0), R(0.0), R(1.0)), 
		GAIA::MATH::VEC3<GAIA::REAL>(R(0.0), R(1.0), R(0.0)));
	mtxProj.perspectivefov(GAIA::MATH::PI * R(0.5), 1.0F / rAspect, R(0.001), R(1000.0));
	mtxCombin = mtxRotate * mtxView * mtxProj;
	r.SetConstant(ctx, "u_mtx", mtxCombin.front_ptr(), 4, 4, 1);
	r.Draw(ctx, 12);

	// Flush.
	r.Flush(ctx, GAIA::True);

	// Calculate frame count.
	static GAIA::U32 s_nFrameCount = 0;
	++s_nFrameCount;
	if(s_nFrameCount % 100 == 0)
	{
		GAIA::TCH szTemp[32];
		GAIA::ALGO::value_cast(s_nFrameCount, szTemp, sizeofarray(szTemp));
		r.GetDesc().pCanvas->SetCaptionText(szTemp);
	}

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