#ifndef		__GAIA_RENDER_GL1_H__
#define		__GAIA_RENDER_GL1_H__

#if defined(GAIA_PLATFORM_OPENGL1)
#	include <gl/gl.h>
#endif

#if GAIA_REAL == GAIA_REAL_F32
#	define GL_REAL GL_FLOAT
#elif GAIA_REAL == GAIA_REAL_F64
#	define GAIA_REAL GL_DOUBLE
#endif

namespace GAIA
{
	namespace RENDER
	{
		class Render3DGL1 : public virtual GAIA::RENDER::Render3D
		{
		public:
			typedef Render3DGL1 __MyType;

		public:
			class GLI : public GAIA::Base
			{
			#define GLPROCINST(name) gl##name##Proc name
			#define GLPROCINIT(name) name = GNIL
			#define GLPROCMAP(name) name = gl##name
			#define GLPROCCHECK(name) if(name == GNIL) return GAIA::False;
			public:
				GINL GLI(){this->reset();}
				GINL GAIA::BL Initialize()
				{
					if(m_bInitialized)
						return GAIA::False;
				#if GAIA_PLATFORM_OPENGL1
					GLPROCMAP(GetError);
					GLPROCMAP(GetBooleanv);
					GLPROCMAP(GetIntegerv);
					GLPROCMAP(GetFloatv);
					GLPROCMAP(GetDoublev);
					GLPROCMAP(Flush);
					GLPROCMAP(Enable);
					GLPROCMAP(Disable);
					GLPROCMAP(Hint);
					GLPROCMAP(BlendFunc);
					GLPROCMAP(ShadeModel);
					GLPROCMAP(DepthFunc);
					GLPROCMAP(ClearColor);
					GLPROCMAP(Clear);
					GLPROCMAP(LoadIdentity);
					GLPROCMAP(Ortho);
					GLPROCMAP(PointSize);
					GLPROCMAP(LineWidth);
					GLPROCMAP(EnableClientState);
					GLPROCMAP(DisableClientState);
					GLPROCMAP(VertexPointer);
					GLPROCMAP(NormalPointer);
					GLPROCMAP(ColorPointer);
					GLPROCMAP(TexCoordPointer);
					GLPROCMAP(DrawElements);
				#endif
					if(!this->check())
					{
						this->reset();
						return GAIA::False;
					}
					m_bInitialized = GAIA::True;
					return GAIA::True;
				}
				GINL GAIA::BL Release()
				{
					if(!m_bInitialized)
						return GAIA::False;
					m_bInitialized = GAIA::False;
					return GAIA::True;
				}
				GINL GAIA::BL IsInitialized() const
				{
					return m_bInitialized;
				}
				GINL GAIA::GVOID reset()
				{
					m_bInitialized = GAIA::False;
					GLPROCINIT(GetError);
					GLPROCINIT(GetBooleanv);
					GLPROCINIT(GetIntegerv);
					GLPROCINIT(GetFloatv);
					GLPROCINIT(GetDoublev);
					GLPROCINIT(Flush);
					GLPROCINIT(Enable);
					GLPROCINIT(Disable);
					GLPROCINIT(Hint);
					GLPROCINIT(BlendFunc);
					GLPROCINIT(ShadeModel);
					GLPROCINIT(DepthFunc);
					GLPROCINIT(ClearColor);
					GLPROCINIT(Clear);
					GLPROCINIT(LoadIdentity);
					GLPROCINIT(Ortho);
					GLPROCINIT(PointSize);
					GLPROCINIT(LineWidth);
					GLPROCINIT(EnableClientState);
					GLPROCINIT(DisableClientState);
					GLPROCINIT(VertexPointer);
					GLPROCINIT(NormalPointer);
					GLPROCINIT(ColorPointer);
					GLPROCINIT(TexCoordPointer);
					GLPROCINIT(DrawElements);
				}
				GINL GAIA::BL check() const
				{
					GLPROCCHECK(GetError);
					GLPROCCHECK(GetBooleanv);
					GLPROCCHECK(GetIntegerv);
					GLPROCCHECK(GetFloatv);
					GLPROCCHECK(GetDoublev);
					GLPROCCHECK(Flush);
					GLPROCCHECK(Enable);
					GLPROCCHECK(Disable);
					GLPROCCHECK(Hint);
					GLPROCCHECK(BlendFunc);
					GLPROCCHECK(ShadeModel);
					GLPROCCHECK(DepthFunc);
					GLPROCCHECK(ClearColor);
					GLPROCCHECK(Clear);
					GLPROCCHECK(LoadIdentity);
					GLPROCCHECK(Ortho);
					GLPROCCHECK(PointSize);
					GLPROCCHECK(LineWidth);
					GLPROCCHECK(EnableClientState);
					GLPROCCHECK(DisableClientState);
					GLPROCCHECK(VertexPointer);
					GLPROCCHECK(NormalPointer);
					GLPROCCHECK(ColorPointer);
					GLPROCCHECK(TexCoordPointer);
					GLPROCCHECK(DrawElements);
					return GAIA::True;
				}

			private:
				typedef GAIA::U32 (GAIA_BASEAPI* glGetErrorProc)();
				typedef GAIA::GVOID (GAIA_BASEAPI* glGetBooleanvProc)(GAIA::U32 pname, GAIA::U8* params);
				typedef GAIA::GVOID (GAIA_BASEAPI* glGetIntegervProc)(GAIA::U32 pname, GAIA::N32* params);
				typedef GAIA::GVOID (GAIA_BASEAPI* glGetFloatvProc)(GAIA::U32 pname, GAIA::F32* params);
				typedef GAIA::GVOID (GAIA_BASEAPI* glGetDoublevProc)(GAIA::U32 pname, GAIA::F64* params);
				typedef GAIA::GVOID (GAIA_BASEAPI* glFlushProc)();
				typedef GAIA::GVOID (GAIA_BASEAPI* glEnableProc)(GAIA::U32 cap);
				typedef GAIA::GVOID (GAIA_BASEAPI* glDisableProc)(GAIA::U32 cap);
				typedef GAIA::GVOID (GAIA_BASEAPI* glHintProc)(GAIA::U32 target, GAIA::U32 mode);
				typedef GAIA::GVOID (GAIA_BASEAPI* glBlendFuncProc)(GAIA::U32 sfactor, GAIA::U32 dfactor);
				typedef GAIA::GVOID (GAIA_BASEAPI* glShadeModelProc)(GAIA::U32 mode);
				typedef GAIA::GVOID (GAIA_BASEAPI* glDepthFuncProc)(GAIA::U32 func);
				typedef GAIA::GVOID (GAIA_BASEAPI* glClearColorProc)(GAIA::F32 r, GAIA::F32 g, GAIA::F32 b, GAIA::F32 a);
				typedef GAIA::GVOID (GAIA_BASEAPI* glClearProc)(GAIA::U32 clear_mask);
				typedef GAIA::GVOID (GAIA_BASEAPI* glLoadIdentityProc)();
				typedef GAIA::GVOID (GAIA_BASEAPI* glOrthoProc)(GAIA::F64 left, GAIA::F64 right, GAIA::F64 bottom, GAIA::F64 top, GAIA::F64 zNear, GAIA::F64 zFar);
				typedef GAIA::GVOID (GAIA_BASEAPI* glPointSizeProc)(GAIA::F32 size);
				typedef GAIA::GVOID (GAIA_BASEAPI* glLineWidthProc)(GAIA::F32 width);
				typedef GAIA::GVOID (GAIA_BASEAPI* glEnableClientStateProc)(GAIA::U32 array);
				typedef GAIA::GVOID (GAIA_BASEAPI* glDisableClientStateProc)(GAIA::U32 array);
				typedef GAIA::GVOID (GAIA_BASEAPI* glVertexPointerProc)(GAIA::N32 size, GAIA::U32 type, GAIA::N32 stride, const GAIA::GVOID* pointer);
				typedef GAIA::GVOID (GAIA_BASEAPI* glNormalPointerProc)(GAIA::U32 type, GAIA::N32 stride, const GAIA::GVOID* pointer);
				typedef GAIA::GVOID (GAIA_BASEAPI* glColorPointerProc)(GAIA::N32 size, GAIA::U32 type, GAIA::N32 stride, const GAIA::GVOID* pointer);
				typedef GAIA::GVOID (GAIA_BASEAPI* glTexCoordPointerProc)(GAIA::N32 size, GAIA::U32 type, GAIA::N32 stride, const GAIA::GVOID* pointer);
				typedef GAIA::GVOID (GAIA_BASEAPI* glDrawElementsProc)(GAIA::U32 mode, GAIA::N32 count, GAIA::U32 type, const GAIA::GVOID* indices);

			public:
				GLPROCINST(GetError);
				GLPROCINST(GetBooleanv);
				GLPROCINST(GetIntegerv);
				GLPROCINST(GetFloatv);
				GLPROCINST(GetDoublev);
				GLPROCINST(Flush);
				GLPROCINST(Enable);
				GLPROCINST(Disable);
				GLPROCINST(Hint);
				GLPROCINST(BlendFunc);
				GLPROCINST(ShadeModel);
				GLPROCINST(DepthFunc);
				GLPROCINST(ClearColor);
				GLPROCINST(Clear);
				GLPROCINST(LoadIdentity);
				GLPROCINST(Ortho);
				GLPROCINST(PointSize);
				GLPROCINST(LineWidth);
				GLPROCINST(EnableClientState);
				GLPROCINST(DisableClientState);
				GLPROCINST(VertexPointer);
				GLPROCINST(NormalPointer);
				GLPROCINST(ColorPointer);
				GLPROCINST(TexCoordPointer);
				GLPROCINST(DrawElements);

			private:
				GAIA::BL m_bInitialized;

			#undef GLPROCINST
			#undef GLPROCINIT
			#undef GLPROCMAP
			#undef GLPROCCHECK
			};

		public:
			class RenderDesc : public virtual GAIA::RENDER::Render3D::RenderDesc
			{
			public:
				virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::RenderDesc::reset();}
				virtual GAIA::BL check() const
				{
					if(!GAIA::RENDER::Render3D::RenderDesc::check())
						return GAIA::False;
					return GAIA::True;
				}
			};

			class Context : public virtual GAIA::RENDER::Render3D::Context
			{
			public:
				class ContextDesc : public virtual GAIA::RENDER::Render3D::Context::ContextDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::Context::ContextDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render3D::Context::ContextDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL Context(){this->init();}
				GINL ~Context(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render::Context::ContextDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::Context::ContextDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					GAIA_RELEASE_SAFE(pCurrentPen);
					GAIA_RELEASE_SAFE(pCurrentBrush);
					GAIA_RELEASE_SAFE(pCurrentFontFamily);
					GAIA_RELEASE_SAFE(pCurrentFontPainter);
					GAIA_RELEASE_SAFE(pCurrentFontFormat);
					for(GAIA::SIZE x = 0; x < sizeofarray(pCurrentTexture); ++x)
						GAIA_RELEASE_SAFE(pCurrentTexture[x]);
					for(GAIA::SIZE x = 0; x < sizeofarray(pCurrentTarget); ++x)
						GAIA_RELEASE_SAFE(pCurrentTarget[x]);
					GAIA_RELEASE_SAFE(pCurrentShader);

					slines.destroy();
					GAIA_RELEASE_SAFE(pSLineLastPen);
					pszSLineLastAlphaBlendState = GNILSTR;
					pszSLineLastQualityState = GNILSTR;

					bEnableAlphaBlend = GAIA::False;
					bEnableAlphaTest = GAIA::False;

					m_desc.reset();
				}
				virtual const ContextDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_CONTEXT;}
			public:
				class Line2DNode : public GAIA::Base
				{
				public:
					GAIA::MATH::VEC2<GAIA::REAL> pos;
					GAIA::MATH::ARGB<GAIA::REAL> cr;
				};
			public:
				typedef GAIA::CTN::Vector<Line2DNode> __Line2DListType;
			public:
				GAIA::RENDER::Render2D::Pen* pCurrentPen;
				GAIA::RENDER::Render2D::Brush* pCurrentBrush;
				GAIA::RENDER::Render2D::FontFamily* pCurrentFontFamily;
				GAIA::RENDER::Render2D::FontPainter* pCurrentFontPainter;
				GAIA::RENDER::Render2D::FontFormat* pCurrentFontFormat;
				GAIA::RENDER::Render2D::Texture* pCurrentTexture[4];
				GAIA::RENDER::Render2D::Target* pCurrentTarget[1];
				GAIA::RENDER::Render2D::Shader* pCurrentShader;

				__Line2DListType slines; // Screen lines buffer.
				GAIA::RENDER::Render2D::Pen* pSLineLastPen;
				const GAIA::CH* pszSLineLastQualityState;
				const GAIA::CH* pszSLineLastAlphaBlendState;

				GAIA::U8 bEnableAlphaBlend : 1;
				GAIA::U8 bEnableAlphaTest : 1;
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
					pCurrentPen = GNIL;
					pCurrentBrush = GNIL;
					pCurrentFontFamily = GNIL;
					pCurrentFontPainter = GNIL;
					pCurrentFontFormat = GNIL;
					GAIA::ALGO::nil(pCurrentTexture, sizeofarray(pCurrentTexture));
					GAIA::ALGO::nil(pCurrentTarget, sizeofarray(pCurrentTarget));
					pCurrentShader = GNIL;

					pSLineLastPen = GNIL;
					pszSLineLastQualityState = GNILSTR;
					pszSLineLastAlphaBlendState = GNILSTR;

					bEnableAlphaBlend = GAIA::False;
					bEnableAlphaTest = GAIA::False;
				}
			private:
				ContextDesc m_desc;
			};

		public:
			class Pen : public virtual GAIA::RENDER::Render2D::Pen
			{
			public:
				class PenDesc : public virtual GAIA::RENDER::Render2D::Pen::PenDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Pen::PenDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Pen::PenDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL Pen(){this->init();}
				GINL ~Pen(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Pen::PenDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::Pen::PenDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const PenDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_PEN;}
				virtual GAIA::BL SetColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr)
				{
					m_cr = cr;
					return GAIA::True;
				}
				virtual GAIA::BL GetColor(GAIA::MATH::ARGB<GAIA::REAL>& cr) const
				{
					cr = m_cr;
					return GAIA::True;
				}
				virtual GAIA::BL SetWidth(const GAIA::REAL& rWidth)
				{
					m_rWidth = rWidth;
					return GAIA::True;
				}
				virtual GAIA::BL GetWidth(GAIA::REAL& rWidth) const
				{
					rWidth = m_rWidth;
					return GAIA::True;
				}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
					m_cr.fromu32(0xFF000000);
					m_cr.torealmode();
					m_rWidth = 1;
				}
			private:
				PenDesc m_desc;
				GAIA::MATH::ARGB<GAIA::REAL> m_cr;
				GAIA::REAL m_rWidth;
			};

			class Brush : public virtual GAIA::RENDER::Render2D::Brush
			{
			public:
				class BrushDesc : public virtual GAIA::RENDER::Render2D::Brush::BrushDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Brush::BrushDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Brush::BrushDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL Brush(){this->init();}
				GINL ~Brush(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Brush::BrushDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::Brush::BrushDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const BrushDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_BRUSH;}
				virtual GAIA::BL SetColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr)
				{
					m_cr = cr;
					return GAIA::True;
				}
				virtual GAIA::BL GetColor(GAIA::MATH::ARGB<GAIA::REAL>& cr) const
				{
					cr = m_cr;
					return GAIA::True;
				}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
					m_cr.fromu32(0xFF000000);
				}
			private:
				BrushDesc m_desc;
				GAIA::MATH::ARGB<GAIA::REAL> m_cr;
			};

			class FontFamily : public virtual GAIA::RENDER::Render2D::FontFamily
			{
			public:
				class FontFamilyDesc : public virtual GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL FontFamily(){this->init();}
				GINL ~FontFamily(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::FontFamily::FontFamilyDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const FontFamilyDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_FONTFAMILY;}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
				}
			private:
				FontFamilyDesc m_desc;
			};

			class FontPainter : public virtual GAIA::RENDER::Render2D::FontPainter
			{
			public:
				class FontPainterDesc : public virtual GAIA::RENDER::Render2D::FontPainter::FontPainterDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::FontPainter::FontPainterDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::FontPainter::FontPainterDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL FontPainter(){this->init();}
				GINL ~FontPainter(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::FontPainter::FontPainterDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const FontPainterDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_FONTPAINTER;}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
				}
			private:
				FontPainterDesc m_desc;
			};

			class FontFormat : public virtual GAIA::RENDER::Render2D::FontFormat
			{
			public:
				class FontFormatDesc : public virtual GAIA::RENDER::Render2D::FontFormat::FontFormatDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::FontFormat::FontFormatDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::FontFormat::FontFormatDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL FontFormat(){this->init();}
				GINL ~FontFormat(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::FontFormat::FontFormatDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const FontFormatDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_FONTFORMAT;}
				virtual GAIA::BL SetAlignDirectionH(GAIA::N8 nDirection)
				{
					m_nAlignDirH = nDirection;
					return GAIA::True;
				}
				virtual GAIA::BL GetAlignDirectionH(GAIA::N8& nDirection)
				{
					nDirection = m_nAlignDirH;
					return GAIA::True;
				}
				virtual GAIA::BL SetAlignDirectionV(GAIA::N8 nDirection)
				{
					m_nAlignDirV = nDirection;
					return GAIA::True;
				}
				virtual GAIA::BL GetAlignDirectionV(GAIA::N8& nDirection)
				{
					nDirection = m_nAlignDirV;
					return GAIA::True;
				}
				virtual GAIA::BL EnableWrap(GAIA::BL bEnable)
				{
					m_bEnableWrap = bEnable;
					return GAIA::True;
				}
				virtual GAIA::BL IsEnableWrap(GAIA::BL& bEnable)
				{
					bEnable = m_bEnableWrap;
					return GAIA::True;
				}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
					m_nAlignDirH = -1;
					m_nAlignDirV = -1;
					m_bEnableWrap = GAIA::True;
				}
			private:
				FontFormatDesc m_desc;
				GAIA::N8 m_nAlignDirH;
				GAIA::N8 m_nAlignDirV;
				GAIA::U8 m_bEnableWrap : 1;
			};

			class Target : public virtual GAIA::RENDER::Render2D::Target
			{
			public:
				class TargetDesc : public virtual GAIA::RENDER::Render2D::Target::TargetDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Target::TargetDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Target::TargetDesc::check()) return GAIA::False; return GAIA::True;}
				};
				class FetchData : public virtual GAIA::RENDER::Render2D::Target::FetchData
				{
				public:
					class FetchDataDesc : public virtual GAIA::RENDER::Render2D::Target::FetchData::FetchDataDesc
					{
					public:
						virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Target::FetchData::FetchDataDesc::reset();}
						virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Target::FetchData::FetchDataDesc::check()) return GAIA::False; return GAIA::True;}
					};
				public:
					GINL FetchData(){this->init();}
					GINL ~FetchData(){this->Destroy();}
					virtual GAIA::BL Create(const GAIA::FAVO::FetchData::FetchDataDesc& desc)
					{
						if(!desc.check())
							return GAIA::False;
						m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::Target::FetchData::FetchDataDesc&)(desc);
						return GAIA::True;
					}
					virtual GAIA::GVOID Destroy()
					{
						m_desc.reset();
					}
					virtual const GAIA::FAVO::FetchData::FetchDataDesc& GetDesc() const{return m_desc;}
					virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_TARGETFETCHDATA;}
					virtual GAIA::SIZE GetSize() const
					{
						return GNIL;
					}
					virtual GAIA::BL Set(const GAIA::GVOID* p, const GAIA::SIZE& sSize, const GAIA::SIZE& sStrideInBits, const GAIA::SIZE& sDstOffsetIndex)
					{
						return GAIA::True;
					}
					virtual GAIA::BL Get(GAIA::GVOID* p, const GAIA::SIZE& sSize, const GAIA::SIZE& sStrideInBits, const GAIA::SIZE& sDstOffsetIndex)
					{
						return GAIA::True;
					}
					virtual GAIA::SIZE GetStrideInBits() const
					{
						return 0;
					}
					virtual GAIA::SIZE GetCount() const
					{
						return 0;
					}
					virtual GAIA::GVOID* GetHead(const GAIA::SIZE& sIndex) const
					{
						return GNIL;
					}
					virtual GAIA::SIZE GetLineStride() const
					{
						return 0;
					}
					virtual GAIA::SIZE GetLineCount() const
					{
						return 0;
					}
					virtual GAIA::GVOID* GetLineHead(const GAIA::SIZE& sLineIndex) const
					{
						return GNIL;
					}
				private:
					GINL GAIA::GVOID init()
					{
						m_desc.reset();
					}
				private:
					FetchDataDesc m_desc;
				};
			public:
				GINL Target(){this->init();}
				GINL ~Target(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Target::TargetDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::Target::TargetDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const TargetDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_TARGET;}
				virtual GAIA::FAVO::FetchData* CreateFetchData(GAIA::RENDER::Render::Context& ctx, const GAIA::FAVO::FetchData::FetchDataDesc& desc)
				{
					return GNIL;
				}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
				}
			private:
				TargetDesc m_desc;
			};

			class Shader : public virtual GAIA::RENDER::Render2D::Shader
			{
			public:
				class ShaderDesc : public virtual GAIA::RENDER::Render2D::Shader::ShaderDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Shader::ShaderDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Shader::ShaderDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL Shader(){this->init();}
				GINL ~Shader(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::Shader::ShaderDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const ShaderDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_SHADER;}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
				}
			private:
				ShaderDesc m_desc;
			};

			class Texture : public virtual GAIA::RENDER::Render2D::Texture
			{
			public:
				class TextureDesc : public virtual GAIA::RENDER::Render2D::Texture::TextureDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Texture::TextureDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Texture::TextureDesc::check()) return GAIA::False; return GAIA::True;}
				};
				class FetchData : public virtual GAIA::RENDER::Render2D::Texture::FetchData
				{
				public:
					class FetchDataDesc : public virtual GAIA::RENDER::Render2D::Texture::FetchData::FetchDataDesc
					{
					public:
						virtual GAIA::GVOID reset(){GAIA::RENDER::Render2D::Texture::FetchData::FetchDataDesc::reset();}
						virtual GAIA::BL check() const{if(!GAIA::RENDER::Render2D::Texture::FetchData::FetchDataDesc::check()) return GAIA::False; return GAIA::True;}
					};
				public:
					GINL FetchData(){this->init();}
					GINL ~FetchData(){this->Destroy();}
					virtual GAIA::BL Create(const GAIA::FAVO::FetchData::FetchDataDesc& desc)
					{
						if(!desc.check())
							return GAIA::False;
						m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::Texture::FetchData::FetchDataDesc&)(desc);
						return GAIA::True;
					}
					virtual GAIA::GVOID Destroy()
					{
						m_desc.reset();
					}
					virtual const GAIA::FAVO::FetchData::FetchDataDesc& GetDesc() const{return m_desc;}
					virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_TEXTUREFETCHDATA;}
					virtual GAIA::SIZE GetSize() const
					{
						return GNIL;
					}
					virtual GAIA::BL Set(const GAIA::GVOID* p, const GAIA::SIZE& sSize, const GAIA::SIZE& sStrideInBits, const GAIA::SIZE& sDstOffsetIndex)
					{
						return GAIA::True;
					}
					virtual GAIA::BL Get(GAIA::GVOID* p, const GAIA::SIZE& sSize, const GAIA::SIZE& sStrideInBits, const GAIA::SIZE& sDstOffsetIndex)
					{
						return GAIA::True;
					}
					virtual GAIA::SIZE GetStrideInBits() const
					{
						return 0;
					}
					virtual GAIA::SIZE GetCount() const
					{
						return 0;
					}
					virtual GAIA::GVOID* GetHead(const GAIA::SIZE& sIndex) const
					{
						return GNIL;
					}
					virtual GAIA::SIZE GetLineStride() const
					{
						return 0;
					}
					virtual GAIA::SIZE GetLineCount() const
					{
						return 0;
					}
					virtual GAIA::GVOID* GetLineHead(const GAIA::SIZE& sLineIndex) const
					{
						return GNIL;
					}
				private:
					GINL GAIA::GVOID init()
					{
						m_desc.reset();
					}
				private:
					FetchDataDesc m_desc;
				};
			public:
				GINL Texture(){this->init();}
				GINL ~Texture(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render2D::Texture::TextureDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::Texture::TextureDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const TextureDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_TEXTURE;}
				virtual GAIA::FAVO::FetchData* CreateFetchData(GAIA::RENDER::Render::Context& ctx, const GAIA::FAVO::FetchData::FetchDataDesc& desc)
				{
					return GNIL;
				}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
				}
			private:
				TextureDesc m_desc;
			};

		public:
			class VertexDeclaration : public virtual GAIA::RENDER::Render3D::VertexDeclaration
			{
			public:
				class VertexDeclarationDesc : public virtual GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc::check()) return GAIA::False; return GAIA::True;}
				};
			public:
				GINL VertexDeclaration(){this->init();}
				GINL ~VertexDeclaration(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::VertexDeclaration::VertexDeclarationDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const VertexDeclarationDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_VERTEXDECLARATION;}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
				}
			private:
				VertexDeclarationDesc m_desc;
			};

			class IndexBuffer : public virtual GAIA::RENDER::Render3D::IndexBuffer
			{
			public:
				class IndexBufferDesc : public virtual GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc::check()) return GAIA::False; return GAIA::True;}
				};
				class FetchData : public virtual GAIA::RENDER::Render3D::IndexBuffer::FetchData
				{
				public:
					class FetchDataDesc : public virtual GAIA::RENDER::Render3D::IndexBuffer::FetchData::FetchDataDesc
					{
					public:
						virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::IndexBuffer::FetchData::FetchDataDesc::reset();}
						virtual GAIA::BL check() const{if(GAIA::RENDER::Render3D::IndexBuffer::FetchData::FetchDataDesc::check()) return GAIA::False; return GAIA::True;}
					};
				public:
					GINL FetchData(){this->init();}
					GINL ~FetchData(){this->Destroy();}
					virtual GAIA::BL Create(const GAIA::FAVO::FetchData::FetchDataDesc& desc)
					{
						if(!desc.check())
							return GAIA::False;
						m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::IndexBuffer::FetchData::FetchDataDesc&)(desc);
						return GAIA::True;
					}
					virtual GAIA::GVOID Destroy()
					{
						m_desc.reset();
					}
					virtual const GAIA::FAVO::FetchData::FetchDataDesc& GetDesc() const{return m_desc;}
					virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_INDEXBUFFERFETCHDATA;}
					virtual GAIA::SIZE GetSize() const
					{
						return GNIL;
					}
					virtual GAIA::BL Set(const GAIA::GVOID* p, const GAIA::SIZE& sSize, const GAIA::SIZE& sStrideInBits, const GAIA::SIZE& sDstOffsetIndex)
					{
						return GAIA::True;
					}
					virtual GAIA::BL Get(GAIA::GVOID* p, const GAIA::SIZE& sSize, const GAIA::SIZE& sStrideInBits, const GAIA::SIZE& sDstOffsetIndex)
					{
						return GAIA::True;
					}
					virtual GAIA::SIZE GetStrideInBits() const
					{
						return 0;
					}
					virtual GAIA::SIZE GetCount() const
					{
						return 0;
					}
					virtual GAIA::GVOID* GetHead(const GAIA::SIZE& sIndex) const
					{
						return GNIL;
					}
				private:
					GINL GAIA::GVOID init()
					{
						m_desc.reset();
					}
				private:
					FetchDataDesc m_desc;
				};
			public:
				GINL IndexBuffer(){this->init();}
				GINL ~IndexBuffer(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::IndexBuffer::IndexBufferDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const IndexBufferDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_INDEXBUFFER;}
				virtual GAIA::FAVO::FetchData* CreateFetchData(GAIA::RENDER::Render::Context& ctx, const GAIA::FAVO::FetchData::FetchDataDesc& desc)
				{
					return GNIL;
				}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
				}
			private:
				IndexBufferDesc m_desc;
			};

			class VertexBuffer : public virtual GAIA::RENDER::Render3D::VertexBuffer
			{
			public:
				class VertexBufferDesc : public virtual GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc
				{
				public:
					virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc::reset();}
					virtual GAIA::BL check() const{if(!GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc::check()) return GAIA::False; return GAIA::True;}
				};
				class FetchData : public virtual GAIA::RENDER::Render3D::VertexBuffer::FetchData
				{
				public:
					class FetchDataDesc : public virtual GAIA::RENDER::Render3D::VertexBuffer::FetchData::FetchDataDesc
					{
					public:
						virtual GAIA::GVOID reset(){GAIA::RENDER::Render3D::VertexBuffer::FetchData::FetchDataDesc::reset();}
						virtual GAIA::BL check() const{if(GAIA::RENDER::Render3D::VertexBuffer::FetchData::FetchDataDesc::check()) return GAIA::False; return GAIA::True;}
					};
				public:
					GINL FetchData(){this->init();}
					GINL ~FetchData(){this->Destroy();}
					virtual GAIA::BL Create(const GAIA::FAVO::FetchData::FetchDataDesc& desc)
					{
						if(!desc.check())
							return GAIA::False;
						m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::VertexBuffer::FetchData::FetchDataDesc&)(desc);
						return GAIA::True;
					}
					virtual GAIA::GVOID Destroy()
					{
						m_desc.reset();
					}
					virtual const GAIA::FAVO::FetchData::FetchDataDesc& GetDesc() const{return m_desc;}
					virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_VERTEXBUFFERFETCHDATA;}
					virtual GAIA::SIZE GetSize() const
					{
						return GNIL;
					}
					virtual GAIA::BL Set(const GAIA::GVOID* p, const GAIA::SIZE& sSize, const GAIA::SIZE& sStrideInBits, const GAIA::SIZE& sDstOffsetIndex)
					{
						return GAIA::True;
					}
					virtual GAIA::BL Get(GAIA::GVOID* p, const GAIA::SIZE& sSize, const GAIA::SIZE& sStrideInBits, const GAIA::SIZE& sDstOffsetIndex)
					{
						return GAIA::True;
					}
					virtual GAIA::SIZE GetStrideInBits() const
					{
						return 0;
					}
					virtual GAIA::SIZE GetCount() const
					{
						return 0;
					}
					virtual GAIA::GVOID* GetHead(const GAIA::SIZE& sIndex) const
					{
						return GNIL;
					}
				private:
					GINL GAIA::GVOID init()
					{
						m_desc.reset();
					}
				private:
					FetchDataDesc m_desc;
				};
			public:
				GINL VertexBuffer(){this->init();}
				GINL ~VertexBuffer(){this->Destroy();}
				virtual GAIA::BL Create(const GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc& desc)
				{
					if(!desc.check())
						return GAIA::False;
					m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::VertexBuffer::VertexBufferDesc&)(desc);
					return GAIA::True;
				}
				virtual GAIA::GVOID Destroy()
				{
					m_desc.reset();
				}
				virtual const VertexBufferDesc& GetDesc() const{return m_desc;}
				virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1_VERTEXBUFFER;}
				virtual GAIA::FAVO::FetchData* CreateFetchData(GAIA::RENDER::Render::Context& ctx, const GAIA::FAVO::FetchData::FetchDataDesc& desc)
				{
					return GNIL;
				}
			private:
				GINL GAIA::GVOID init()
				{
					m_desc.reset();
				}
			private:
				VertexBufferDesc m_desc;
			};

		public:
			GINL Render3DGL1(){this->init();}
			GINL ~Render3DGL1(){}

			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_RENDER_3D_GL1;}

			virtual GAIA::BL Create(const GAIA::RENDER::Render::RenderDesc& desc)
			{
				if(m_bCreated)
					return GAIA::False;

				if(!desc.check())
					return GAIA::False;

				desc.pCanvas->Reference();
				m_desc = GDCAST(const GAIA::RENDER::Render3DGL1::RenderDesc&)(desc);

				GAIA::GVOID* pHandle = desc.pCanvas->GetHandle();
				GAIA_AST(pHandle != GNIL);

				m_incindexbuf.reserve(2 * 3 * 4 * 1000); // 2, 3, 4 must be the common divisor.
				for(GAIA::SIZE x = 0; x < 2 * 3 * 4 * 1000; ++x)
					m_incindexbuf.push_back(x);

			#if defined(GAIA_PLATFORM_OPENGL1)
				HWND hWnd = GSCAST(HWND)(pHandle);
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

				m_gl.Initialize();
				m_gl.ShadeModel(GL_SMOOTH);
			#endif

				m_bCreated = GAIA::True;
				return GAIA::True;
			}
			virtual GAIA::BL Destroy()
			{
				if(!m_bCreated)
					return GAIA::False;

				GAIA::GVOID* pHandle = m_desc.pCanvas->GetHandle();
				GAIA_AST(pHandle != GNIL);

				m_gl.Release();

			#if defined(GAIA_PLATFORM_OPENGL1)
				HWND hWnd = GSCAST(HWND)(pHandle);
				if(m_hGLRC != GNIL)
				{
					::wglDeleteContext(m_hGLRC);
					m_hGLRC = GNIL;
				}

				if(m_hDC != GNIL)
				{
					::ReleaseDC(hWnd, m_hDC);
					m_hDC = GNIL;
				}
			#endif

				m_desc.pCanvas->Release();
				m_desc.reset();

				m_bCreated = GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsCreated() const
			{
				return m_bCreated;
			}
			virtual const GAIA::RENDER::Render::RenderDesc& GetDesc() const
			{
				return m_desc;
			}

			virtual GAIA::RENDER::Render::Context* CreateContext(const GAIA::RENDER::Render::Context::ContextDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
			#if defined(GAIA_PLATFORM_OPENGL1)
				Context* pContext = GDCAST(Context*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_3D_GL1_CONTEXT, GNIL));
				GAIA_AST(pContext != GNIL);
				if(pContext == GNIL)
					return GNIL;
				pContext->SetRender(this);
				if(!pContext->Create(desc))
				{
					pContext->Release();
					return GNIL;
				}
				return pContext;
			#else
				return GNIL;
			#endif
			}

			virtual GAIA::BL BeginStatePipeline()
			{
				GAIA_AST(!this->IsBeginStatePipeline());
				if(m_bBeginStatePipeline)
					return GAIA::False;
				m_bBeginStatePipeline = GAIA::True;
				return GAIA::True;
			}
			virtual GAIA::BL EndStatePipeline()
			{
				GAIA_AST(this->IsBeginStatePipeline());
				if(!m_bBeginStatePipeline)
					return GAIA::False;
				m_bBeginStatePipeline = GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsBeginStatePipeline() const
			{
				return m_bBeginStatePipeline;
			}

			virtual GAIA::GVOID Flush(GAIA::RENDER::Render::Context& ctx, GAIA::BL bWait)
			{
				GPCHR_TRUE(this->IsBeginStatePipeline());
			#if defined(GAIA_PLATFORM_OPENGL1)
				if(m_hDC == GNIL)
					return;

				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;

				m_bFlushing = GAIA::True;

				this->FlushScreenLine(*pContext);

				if(bWait)
					::SwapBuffers(m_hDC);
				else
					m_gl.Flush();

				m_bFlushing = GAIA::False;
			#endif
			}
			virtual GAIA::BL IsFlushing() const{return m_bFlushing;}

		public:
			/* Scissor. */
			virtual GAIA::GVOID SetScissor(GAIA::RENDER::Render::Context& ctx, const GAIA::MATH::AABR<GAIA::REAL>& aabr){if(aabr.isidentity()) return;}
			virtual GAIA::GVOID GetScissor(GAIA::RENDER::Render::Context& ctx, GAIA::MATH::AABR<GAIA::REAL>& aabr) const{}

			/* Clear. */
			virtual GAIA::GVOID ClearColor(const GAIA::MATH::ARGB<GAIA::REAL>& cr)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
			#if defined(GAIA_PLATFORM_OPENGL1)
				m_gl.ClearColor(cr.r, cr.g, cr.b, cr.a);
				m_gl.Clear(GL_COLOR_BUFFER_BIT);
			#endif
			}

			/* State. */
			virtual GAIA::GVOID SetQuality2DState(GAIA::RENDER::Render::Context& ctx, const QUALITY2D_STATE& qs, const GAIA::CH* pszState)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				if(!GAIA_ENUM_VALID(QUALITY2D_STATE, qs))
					return;
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(GAIA::ALGO::stremp(pszState))
					this->SetQuality2DState(ctx, qs, RENDER2D_QUALITYSTATE_DEFAULT[qs]);
				switch(qs)
				{
				case GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS:
					{
					}
					break;
				case GAIA::RENDER::Render2D::QUALITY2D_STATE_FONTANTIALIAS:
					{
					}
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
			}
			virtual const GAIA::CH* GetQuality2DState(GAIA::RENDER::Render::Context& ctx, const QUALITY2D_STATE& qs) const
			{
				GPCHR_FALSE_RET(this->IsBeginStatePipeline() || this->IsFlushing(), GNIL);
				if(!GAIA_ENUM_VALID(QUALITY2D_STATE, qs))
					return GNILSTR;
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNILSTR;
				switch(qs)
				{
				case GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS:
					{
					}
					break;
				case GAIA::RENDER::Render2D::QUALITY2D_STATE_FONTANTIALIAS:
					{
					}
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return GNILSTR;
			}
			virtual GAIA::GVOID SetRender2DState(GAIA::RENDER::Render::Context& ctx, const RENDER2D_STATE& rs, const GAIA::CH* pszState)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				if(!GAIA_ENUM_VALID(RENDER2D_STATE, rs))
					return;
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(GAIA::ALGO::stremp(pszState))
					this->SetRender2DState(ctx, rs, RENDER2D_RENDERSTATE_DEFAULT[rs]);
				switch(rs)
				{
				case GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND:
					{
						if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]) == 0)
							pContext->bEnableAlphaBlend = GAIA::True;
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_OFF]) == 0)
							pContext->bEnableAlphaBlend = GAIA::False;
					}
					break;

				case GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHATEST:
					{
						if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON]) == 0)
							pContext->bEnableAlphaTest = GAIA::True;
						else if(GAIA::ALGO::strcmp(pszState, GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_OFF]) == 0)
							pContext->bEnableAlphaTest = GAIA::False;
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
			}
			virtual const GAIA::CH* GetRender2DState(GAIA::RENDER::Render::Context& ctx, const RENDER2D_STATE& rs) const
			{
				GPCHR_FALSE_RET(this->IsBeginStatePipeline() || this->IsFlushing(), GNIL);
				if(!GAIA_ENUM_VALID(RENDER2D_STATE, rs))
					return GNILSTR;
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNILSTR;
				switch(rs)
				{
				case GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND:
					{
						if(pContext->bEnableAlphaBlend)
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON];
						else
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_OFF];
					}
					break;

				case GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHATEST:
					{
						if(pContext->bEnableAlphaTest)
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_ON];
						else
							return GAIA::RENDER::RENDER_STATEWORD_STRING[GAIA::RENDER::RENDER_STATEWORD_OFF];
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return GNILSTR;
			}
			virtual GAIA::GVOID SetSampler2DState(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss, const GAIA::CH* pszState)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				if(!GAIA_ENUM_VALID(SAMPLER2D_STATE, ss))
					return;
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(GAIA::ALGO::stremp(pszState))
					this->SetSampler2DState(ctx, nSamplerIndex, ss, RENDER2D_SAMPLERSTATE_DEFAULT[ss]);
				switch(ss)
				{
				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_ADDRESSU:
					{
					}
					break;

				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_ADDRESSV:
					{
					}
					break;

				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_MINFILTER:
					{
					}
					break;

				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_MAXFILTER:
					{
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
			}
			virtual const GAIA::CH* GetSampler2DState(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nSamplerIndex, const SAMPLER2D_STATE& ss) const
			{
				GPCHR_FALSE_RET(this->IsBeginStatePipeline() || this->IsFlushing(), GNIL);
				if(!GAIA_ENUM_VALID(SAMPLER2D_STATE, ss))
					return GNILSTR;
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNILSTR;
				switch(ss)
				{
				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_ADDRESSU:
					{
					}
					break;

				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_ADDRESSV:
					{
					}
					break;

				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_MINFILTER:
					{
					}
					break;

				case GAIA::RENDER::Render2D::SAMPLER2D_STATE_MAXFILTER:
					{
					}
					break;

				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return GNILSTR;
			}

			/* Pen. */
			virtual GAIA::RENDER::Render2D::Pen* CreatePen(GAIA::RENDER::Render::Context& ctx, const GAIA::RENDER::Render2D::Pen::PenDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNIL;
			#if defined(GAIA_PLATFORM_OPENGL1)
				Pen* pPen = GDCAST(Pen*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_3D_GL1_PEN, GNIL));
				GAIA_AST(pPen != GNIL);
				if(pPen == GNIL)
					return GNIL;
				pPen->SetRender(this);
				if(!pPen->Create(desc))
				{
					pPen->Release();
					return GNIL;
				}
				return pPen;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::GVOID SetPen(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Pen* pPen)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pPen != GNIL)
					pPen->Reference();
				if(pContext->pCurrentPen != GNIL)
					pContext->pCurrentPen->Release();
				pContext->pCurrentPen = pPen;
			}
			virtual GAIA::GVOID GetPen(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Pen*& pPen) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pContext->pCurrentPen != GNIL)
					pContext->pCurrentPen->Reference();
				pPen = pContext->pCurrentPen;
			}

			/* Brush. */
			virtual GAIA::RENDER::Render2D::Brush* CreateBrush(GAIA::RENDER::Render::Context& ctx, const GAIA::RENDER::Render2D::Brush::BrushDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNIL;
			#if defined(GAIA_PLATFORM_OPENGL1)
				Brush* pBrush = GDCAST(Brush*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_3D_GL1_BRUSH, GNIL));
				pBrush->SetRender(this);
				if(!pBrush->Create(desc))
				{
					pBrush->Release();
					return GNIL;
				}
				return pBrush;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::GVOID SetBrush(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Brush* pBrush)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pBrush != GNIL)
					pBrush->Reference();
				if(pContext->pCurrentBrush != GNIL)
					pContext->pCurrentBrush->Release();
				pContext->pCurrentBrush = pBrush;
			}
			virtual GAIA::GVOID GetBrush(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Brush*& pBrush) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pContext->pCurrentBrush != GNIL)
					pContext->pCurrentBrush->Reference();
				pBrush = pContext->pCurrentBrush;
			}

			/* FontPainter. */
			virtual GAIA::RENDER::Render2D::FontFamily* CreateFontFamily(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontFamily::FontFamilyDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNIL;
			#if defined(GAIA_PLATFORM_OPENGL1)
				FontFamily* pFontFamily = GDCAST(FontFamily*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_3D_GL1_FONTFAMILY, GNIL));
				GAIA_AST(pFontFamily != GNIL);
				if(pFontFamily == GNIL)
					return GNIL;
				pFontFamily->SetRender(this);
				if(!pFontFamily->Create(desc))
				{
					pFontFamily->Release();
					return GNIL;
				}
				return pFontFamily;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::RENDER::Render2D::FontPainter* CreateFontPainter(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontPainter::FontPainterDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNIL;
			#if defined(GAIA_PLATFORM_OPENGL1)
				FontPainter* pFontPainter = GDCAST(FontPainter*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_3D_GL1_FONTPAINTER, GNIL));
				GAIA_AST(pFontPainter != GNIL);
				if(pFontPainter == GNIL)
					return GNIL;
				pFontPainter->SetRender(this);
				if(!pFontPainter->Create(desc))
				{
					pFontPainter->Release();
					return GNIL;
				}
				return pFontPainter;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::RENDER::Render2D::FontFormat* CreateFontFormat(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::FontFormat::FontFormatDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNIL;
			#if defined(GAIA_PLATFORM_OPENGL1)
				FontFormat* pFontFormat = GDCAST(FontFormat*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_3D_GL1_FONTFORMAT, GNIL));
				GAIA_AST(pFontFormat != GNIL);
				if(pFontFormat == GNIL)
					return GNIL;
				pFontFormat->SetRender(this);
				if(!pFontFormat->Create(desc))
				{
					pFontFormat->Release();
					return GNIL;
				}
				return pFontFormat;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::GVOID SetFontFamily(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFamily* pFontFamily)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pFontFamily != GNIL)
					pFontFamily->Reference();
				if(pContext->pCurrentFontFamily != GNIL)
					pContext->pCurrentFontFamily->Release();
				pContext->pCurrentFontFamily = pFontFamily;
			}
			virtual GAIA::GVOID GetFontFamily(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFamily*& pFontFamily) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pContext->pCurrentFontFamily != GNIL)
					pContext->pCurrentFontFamily->Reference();
				pFontFamily = pContext->pCurrentFontFamily;
			}
			virtual GAIA::GVOID SetFontPainter(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontPainter* pFontPainter)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pFontPainter != GNIL)
					pFontPainter->Reference();
				if(pContext->pCurrentFontPainter != GNIL)
					pContext->pCurrentFontPainter->Release();
				pContext->pCurrentFontPainter = pFontPainter;
			}
			virtual GAIA::GVOID GetFontPainter(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontPainter*& pFontPainter) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pContext->pCurrentFontPainter != GNIL)
					pContext->pCurrentFontPainter->Reference();
				pFontPainter = pContext->pCurrentFontPainter;
			}
			virtual GAIA::GVOID SetFontFormat(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFormat* pFontFormat)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pFontFormat != GNIL)
					pFontFormat->Reference();
				if(pContext->pCurrentFontFormat != GNIL)
					pContext->pCurrentFontFormat->Release();
				pContext->pCurrentFontFormat = pFontFormat;
			}
			virtual GAIA::GVOID GetFontFormat(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::FontFormat*& pFontFormat) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pContext->pCurrentFontFormat != GNIL)
					pContext->pCurrentFontFormat->Reference();
				pFontFormat = pContext->pCurrentFontFormat;
			}

			/* Texture. */
			virtual GAIA::RENDER::Render2D::Texture* CreateTexture(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Texture::TextureDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNIL;
			#if defined(GAIA_PLATFORM_OPENGL1)
				Texture* pTex = GDCAST(Texture*)(this->GetFactory()->CreateInstance(GAIA::FWORK::CLSID_RENDER_3D_GL1_TEXTURE, GNIL));
				GAIA_AST(pTex != GNIL);
				if(pTex == GNIL)
					return GNIL;
				pTex->SetRender(this);
				if(!pTex->Create(desc))
				{
					pTex->Release();
					return GNIL;
				}
				return pTex;
			#else
				return GNIL;
			#endif
			}
			virtual GAIA::GVOID SetTexture(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture* pTexture)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GAIA_AST(nTextureIndex >= 0);
				if(nTextureIndex < 0)
					return;
				GAIA_AST(nTextureIndex < sizeofarray(pContext->pCurrentTexture));
				if(nTextureIndex >= sizeofarray(pContext->pCurrentTexture))
					return;
				if(pTexture != GNIL)
					pTexture->Reference();
				if(pContext->pCurrentTexture[nTextureIndex] != GNIL)
					pContext->pCurrentTexture[nTextureIndex]->Release();
				pContext->pCurrentTexture[nTextureIndex] = pTexture;
			}
			virtual GAIA::GVOID GetTexture(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTextureIndex, GAIA::RENDER::Render2D::Texture*& pTexture) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GAIA_AST(nTextureIndex >= 0);
				if(nTextureIndex < 0)
					return;
				GAIA_AST(nTextureIndex < sizeofarray(pContext->pCurrentTexture));
				if(nTextureIndex >= sizeofarray(pContext->pCurrentTexture))
					return;
				if(pContext->pCurrentTexture[nTextureIndex] != GNIL)
					pContext->pCurrentTexture[nTextureIndex]->Reference();
				pTexture = pContext->pCurrentTexture[nTextureIndex];
			}

			/* Target. */
			virtual GAIA::RENDER::Render2D::Target* CreateTarget(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Target::TargetDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNIL;

				return GNIL;
			}
			virtual GAIA::GVOID SetTarget(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target* pTarget)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GAIA_AST(nTargetIndex >= 0);
				if(nTargetIndex < 0)
					return;
				GAIA_AST(nTargetIndex < sizeofarray(pContext->pCurrentTarget));
				if(nTargetIndex >= sizeofarray(pContext->pCurrentTarget))
					return;
				if(pTarget != GNIL)
					pTarget->Reference();
				if(pContext->pCurrentTarget[nTargetIndex] != GNIL)
					pContext->pCurrentTarget[nTargetIndex]->Release();
				pContext->pCurrentTarget[nTargetIndex] = pTarget;
			}
			virtual GAIA::GVOID GetTarget(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nTargetIndex, GAIA::RENDER::Render2D::Target*& pTarget) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GAIA_AST(nTargetIndex >= 0);
				if(nTargetIndex < 0)
					return;
				GAIA_AST(nTargetIndex < sizeofarray(pContext->pCurrentTarget));
				if(nTargetIndex >= sizeofarray(pContext->pCurrentTarget))
					return;
				if(pContext->pCurrentTarget[nTargetIndex] != GNIL)
					pContext->pCurrentTarget[nTargetIndex]->Reference();
				pTarget = pContext->pCurrentTarget[nTargetIndex];
			}

			/* Shader. */
			virtual GAIA::RENDER::Render2D::Shader* CreateShader(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render2D::Shader::ShaderDesc& desc)
			{
				GPCHR_NULL_RET(this->GetFactory(), GNIL);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return GNIL;

				return GNIL;
			}
			virtual GAIA::GVOID SetShader(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Shader* pShader)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pShader != GNIL)
					pShader->Reference();
				if(pContext->pCurrentShader != GNIL)
					pContext->pCurrentShader->Release();
				pContext->pCurrentShader = pShader;
			}
			virtual GAIA::GVOID GetShader(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render2D::Shader*& pShader) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				if(pContext->pCurrentShader != GNIL)
					pContext->pCurrentShader->Reference();
				pShader = pContext->pCurrentShader;
			}
			virtual GAIA::GVOID SetShaderConstant(GAIA::RENDER::Render::Context& ctx, const GAIA::SIZE& sStartIndex, const GAIA::REAL* p, const GAIA::SIZE& sSize)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
			}
			virtual GAIA::GVOID GetShaderConstant(GAIA::RENDER::Render::Context& ctx, const GAIA::SIZE& sStartIndex, GAIA::REAL* p, const GAIA::SIZE& sSize, GAIA::SIZE& sResultSize) const
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
			}

			/* Draw. */
			virtual GAIA::GVOID DrawLine(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::VEC2<GAIA::REAL>& s,
				const GAIA::MATH::VEC2<GAIA::REAL>& e)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GPCHR_NULL(pContext->pCurrentPen);
			#if defined(GAIA_PLATFORM_OPENGL1)
				GAIA::BL bNeedSwitchContext = GAIA::False;
				if(pContext->pSLineLastPen == GNIL)
					bNeedSwitchContext = GAIA::True;
				else
				{
					GAIA::REAL rWidth, rLastWidth;
					GAIA::MATH::ARGB<GAIA::REAL> cr, crLast;
					pContext->pCurrentPen->GetWidth(rWidth);
					pContext->pSLineLastPen->GetWidth(rLastWidth);
					pContext->pCurrentPen->GetColor(cr);
					pContext->pSLineLastPen->GetColor(crLast);
					if(rWidth != rLastWidth || cr != crLast)
						bNeedSwitchContext = GAIA::True;
					else
					{
						const GAIA::CH* pszAlphaBlend = this->GetRender2DState(ctx, GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND);
						const GAIA::CH* pszQualityState = this->GetQuality2DState(ctx, GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS);
						if(GAIA::ALGO::strcmp(pszAlphaBlend, pContext->pszSLineLastAlphaBlendState) != 0 || 
							GAIA::ALGO::strcmp(pszQualityState, pContext->pszSLineLastQualityState) != 0)
							bNeedSwitchContext = GAIA::True;
					}
				}
				if(pContext->slines.size() + 2 > m_incindexbuf.size())
					bNeedSwitchContext = GAIA::True;
				if(bNeedSwitchContext)
					this->FlushScreenLine(*pContext);
				Context::Line2DNode n;
				n.pos = s;
				pContext->pCurrentPen->GetColor(n.cr);
				pContext->slines.push_back(n);
				n.pos = e;
				pContext->slines.push_back(n);
				if(bNeedSwitchContext)
				{
					pContext->pszSLineLastAlphaBlendState = this->GetRender2DState(ctx, GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND);
					pContext->pszSLineLastQualityState = this->GetQuality2DState(ctx, GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS);
					GAIA_RELEASE_SAFE(pContext->pSLineLastPen);
					pContext->pSLineLastPen = pContext->pCurrentPen;
					pContext->pSLineLastPen->Reference();
				}
			#endif
			}
			virtual GAIA::GVOID DrawRect(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::AABR<GAIA::REAL>& aabr)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GPCHR_NULL(pContext->pCurrentBrush);
			}
			virtual GAIA::GVOID DrawTriangle(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::VEC2<GAIA::REAL>& pos1,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos2,
				const GAIA::MATH::VEC2<GAIA::REAL>& pos3)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GPCHR_NULL(pContext->pCurrentBrush);
			}
			virtual GAIA::GVOID DrawFontPainter(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::TCH* pszText,
				const GAIA::MATH::AABR<GAIA::REAL>& aabr)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GPCHR_NULLSTRPTR(pszText);
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GPCHR_NULL(pContext->pCurrentFontPainter);
				GPCHR_NULL(pContext->pCurrentBrush);
			}
			virtual GAIA::GVOID DrawTexture(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::MATH::AABR<GAIA::REAL>& aabr,
				const GAIA::MATH::MTX33<GAIA::REAL>& mtxTM)
			{
				GPCHR_FALSE(this->IsBeginStatePipeline() || this->IsFlushing());
				GAIA::RENDER::Render3DGL1::Context* pContext = GDCAST(GAIA::RENDER::Render3DGL1::Context*)(&ctx);
				if(pContext == GNIL)
					return;
				GPCHR_NULL(pContext->pCurrentTexture[0]);
			}

		public:
			/* Viewport. */
			virtual GAIA::GVOID SetViewport(const VIEWPORT& vp)
			{
			}
			virtual GAIA::GVOID GetViewport(VIEWPORT& vp) const
			{
			}

			/* Clip planes. */
			virtual GAIA::GVOID SetClipPlane(GAIA::U8 uClipPlaneIndex, const GAIA::MATH::PLANE<GAIA::REAL>& planes){}
			virtual GAIA::GVOID GetClipPlane(GAIA::U8 uClipPlaneIndex, GAIA::MATH::PLANE<GAIA::REAL>& planes) const{}

			/* State. */
			virtual GAIA::GVOID SetQuality3DState(const QUALITY3D_STATE& qs, const GAIA::CH* pszState)
			{
			}
			virtual const GAIA::CH* GetQuality3DState(const QUALITY3D_STATE& qs) const
			{
				return GNIL;
			}
			virtual GAIA::GVOID SetRender3DState(const RENDER3D_STATE& rs, const GAIA::CH* pszState)
			{
			}
			virtual const GAIA::CH* GetRender3DState(const RENDER3D_STATE& rs) const
			{
				return GNIL;
			}
			virtual GAIA::GVOID SetSampler3DState(GAIA::N32 nSamplerIndex, const SAMPLER3D_STATE& ss, const GAIA::CH* pszState)
			{
			}
			virtual const GAIA::CH* GetSampler3DState(GAIA::N32 nSamplerIndex, const SAMPLER3D_STATE& ss) const
			{
				return GNIL;
			}

			/* Declaration. */
			virtual GAIA::RENDER::Render3D::VertexDeclaration* CreateVertexDeclaration(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render3D::VertexDeclaration::VertexDeclarationDesc& desc)
			{
				return GNIL;
			}
			virtual GAIA::GVOID SetVertexDeclaration(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render3D::VertexDeclaration* pVDecl)
			{
			}
			virtual GAIA::GVOID GetVertexDeclaration(GAIA::RENDER::Render::Context& ctx, GAIA::RENDER::Render3D::VertexDeclaration*& pVDecl) const
			{
			}

			/* Index buffer. */
			virtual GAIA::RENDER::Render3D::IndexBuffer* CreateIndexBuffer(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render3D::IndexBuffer::IndexBufferDesc& desc)
			{
				return GNIL;
			}
			virtual GAIA::GVOID SetIndexBuffer(GAIA::RENDER::Render::Context& ctx, const GAIA::RENDER::Render3D::IndexBuffer* pIB)
			{
			}
			virtual GAIA::GVOID GetIndexBuffer(GAIA::RENDER::Render::Context& ctx, const GAIA::RENDER::Render3D::IndexBuffer*& pIB) const
			{
			}

			/* Vertex buffer. */
			virtual GAIA::RENDER::Render3D::VertexBuffer* CreateVertexBuffer(GAIA::RENDER::Render::Context& ctx, 
				const GAIA::RENDER::Render3D::VertexBuffer::VertexBufferDesc& desc)
			{
				return GNIL;
			}
			virtual GAIA::GVOID SetVertexBuffer(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nStream, const GAIA::RENDER::Render3D::VertexBuffer* pVB)
			{
			}
			virtual GAIA::GVOID GetVertexBuffer(GAIA::RENDER::Render::Context& ctx, GAIA::N32 nStream, const GAIA::RENDER::Render3D::VertexBuffer*& pVB) const
			{
			}

			/* Draw. */
			virtual GAIA::GVOID SetTriangleType(GAIA::RENDER::Render::Context& ctx, DRAW_TRIANGLE_TYPE dtt)
			{
			}
			virtual GAIA::GVOID GetTriangleType(GAIA::RENDER::Render::Context& ctx, DRAW_TRIANGLE_TYPE& dtt) const
			{
			}
			virtual GAIA::GVOID DrawTriangle(GAIA::RENDER::Render::Context& ctx)
			{
			}
			virtual GAIA::GVOID DrawIndexedTriangle(GAIA::RENDER::Render::Context& ctx)
			{
			}

		private:
			GINL GAIA::GVOID init()
			{
				m_bCreated = GAIA::False;
				m_desc.reset();
				m_bBeginStatePipeline = GAIA::False;
				m_bFlushing = GAIA::False;
			#if defined(GAIA_PLATFORM_OPENGL1)
				m_hDC = GNIL;
				m_hGLRC = GNIL;
			#endif
			}
			GINL GAIA::GVOID FlushScreenLine(GAIA::RENDER::Render3DGL1::Context& ctx)
			{
				if(ctx.slines.size() == 0)
					return;
				GAIA_AST(ctx.slines.size() % 2 == 0);
				GAIA_AST(ctx.pSLineLastPen != GNIL);

			#if defined(GAIA_PLATFORM_OPENGL1)
				const GAIA::UI::Canvas::__SizeType& sizeCanvas = m_desc.pCanvas->Size();

				/* Get old pipeline parameter. */
				GAIA::F32 fLastLineWidth;
				m_gl.GetFloatv(GL_LINE_WIDTH, &fLastLineWidth);
				GAIA::U8 bLastEnableVertexArray;
				GAIA::U8 bLastEnableColorArray;
				m_gl.GetBooleanv(GL_VERTEX_ARRAY, &bLastEnableVertexArray);
				m_gl.GetBooleanv(GL_COLOR_ARRAY, &bLastEnableColorArray);
				const GAIA::CH* pszLastAlphaBlend = this->GetRender2DState(ctx, GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND);
				const GAIA::CH* pszLastAntiAlias = this->GetQuality2DState(ctx, GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS);

				/* Setup current pipeline parameter and draw. */
				m_gl.LoadIdentity();
				m_gl.Ortho(0.0F, sizeCanvas.x, 0.0F, sizeCanvas.y, 0.0F, 1000.0F);

				this->SetRender2DState(ctx, GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND, ctx.pszSLineLastAlphaBlendState);
				this->SetQuality2DState(ctx, GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS, ctx.pszSLineLastQualityState);

				GAIA::REAL rWidth;
				ctx.pSLineLastPen->GetWidth(rWidth);
				m_gl.LineWidth(rWidth);

				m_gl.EnableClientState(GL_VERTEX_ARRAY);
				m_gl.EnableClientState(GL_COLOR_ARRAY);
				m_gl.VertexPointer(2, GL_REAL, sizeof(Context::Line2DNode), &ctx.slines.front().pos);
				m_gl.ColorPointer(4, GL_REAL, sizeof(Context::Line2DNode), &ctx.slines.front().cr);
				m_gl.DrawElements(GL_LINES, ctx.slines.size(), GL_UNSIGNED_INT, m_incindexbuf.front_ptr());

				/* Restore old pipeline parameter. */
				m_gl.LineWidth(fLastLineWidth);
				if(bLastEnableVertexArray)
					m_gl.EnableClientState(GL_VERTEX_ARRAY);
				else
					m_gl.DisableClientState(GL_VERTEX_ARRAY);
				if(bLastEnableColorArray)
					m_gl.EnableClientState(GL_COLOR_ARRAY);
				else
					m_gl.DisableClientState(GL_COLOR_ARRAY);
				this->SetRender2DState(ctx, GAIA::RENDER::Render2D::RENDER2D_STATE_ALPHABLEND, pszLastAlphaBlend);
				this->SetQuality2DState(ctx, GAIA::RENDER::Render2D::QUALITY2D_STATE_ANTIALIAS, pszLastAntiAlias);
			#endif
				ctx.slines.clear();
			}
			
		private:
			GAIA::BL m_bCreated;
			RenderDesc m_desc;
			GAIA::BL m_bBeginStatePipeline;
			GAIA::BL m_bFlushing;
			GLI m_gl;

			GAIA::CTN::Vector<GAIA::U32> m_incindexbuf; // self-increase-index-buffer.

		#if defined(GAIA_PLATFORM_OPENGL1)
			HDC m_hDC;
			HGLRC m_hGLRC;
		#endif
		};
	};
};

#endif
