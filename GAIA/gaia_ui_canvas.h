#ifndef		__GAIA_UI_CANVAS_H__
#define		__GAIA_UI_CANVAS_H__

namespace GAIA
{
	namespace UI
	{
		class Canvas : public virtual GAIA::FWORK::Instance
		{
		public:
			typedef GAIA::MATH::VEC2<GAIA::N32> __PosType;
			typedef GAIA::MATH::VEC2<GAIA::N32> __SizeType;
		public:
			class CanvasStyle
			{
			public:
				GINL GAIA::GVOID reset()
				{
					bFrameStyle = GAIA::True;
					bPopupStyle = GAIA::False;
					bChildStyle = GAIA::False;
					bMaximizeBox = GAIA::True;
					bMinimizeBox = GAIA::True;
					bResizeAble = GAIA::True;
				}
			public:
				GAIA::U8 bFrameStyle : 1;
				GAIA::U8 bPopupStyle : 1;
				GAIA::U8 bChildStyle : 1;
				GAIA::U8 bMaximizeBox : 1;
				GAIA::U8 bMinimizeBox : 1;
				GAIA::U8 bResizeAble : 1;
			};
			class CanvasDesc
			{
			public:
				GINL GAIA::GVOID reset()
				{
					pszCaptionText = GNIL;
					pParent = GNIL;
					style.reset();
				}
				GINL GAIA::BL check() const
				{
					GAIA::SIZE nMutexGroup = 0;
					if(style.bFrameStyle)
						++nMutexGroup;
					if(style.bPopupStyle)
						++nMutexGroup;
					if(style.bChildStyle)
						++nMutexGroup;
					if(nMutexGroup != 1)
						return GAIA::False;
					if(style.bChildStyle && pParent == GNIL)
						return GAIA::False;
					return GAIA::True;
				}
			public:
				GAIA::TCH* pszCaptionText;
				Canvas* pParent;
				CanvasStyle style;
			};
		public:
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_UI_CANVAS;}
		public:
			GAIA_DEBUG_CODEPURE_MEMFUNC Canvas();
			GAIA_DEBUG_CODEPURE_MEMFUNC ~Canvas();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Create(const CanvasDesc& desc);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Destroy();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL IsCreated() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Quit();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL SetParent(GAIA::UI::Canvas* pParent);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UI::Canvas* GetParent() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Show(GAIA::BL bShow);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL IsShow() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Position(const __PosType& pos);
			GAIA_DEBUG_CODEPURE_MEMFUNC __PosType Position() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Size(const __SizeType& size);
			GAIA_DEBUG_CODEPURE_MEMFUNC __SizeType Size() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL SetCaptionText(const GAIA::TCH* pszCaptionText);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL GetCaptionText(GAIA::TCH* pszResult, GAIA::SIZE sResultMaxCharCount, GAIA::SIZE& sResultCount) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID* GetHandle() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL operator == (const GAIA::UI::Canvas& src) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL operator != (const GAIA::UI::Canvas& src) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL operator >= (const GAIA::UI::Canvas& src) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL operator <= (const GAIA::UI::Canvas& src) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL operator > (const GAIA::UI::Canvas& src) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL operator < (const GAIA::UI::Canvas& src) const;
		private:
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID init();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL RegistToGlobalList();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL UnregistToGlobalList();
		private:
			CanvasStyle m_style;
		#if GAIA_OS == GAIA_OS_WINDOWS
			HWND m_hWnd;
			GAIA::TCH* m_pszClassName;
		#else
		#endif
		};
	};
};

#include "gaia_ui_canvas_indp.h"

#endif