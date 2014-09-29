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
			GINL Canvas();
			GINL ~Canvas();
			GINL GAIA::BL Create(const CanvasDesc& desc);
			GINL GAIA::BL Destroy();
			GINL GAIA::BL IsCreated() const;
			GINL GAIA::BL Quit();
			GINL GAIA::BL SetParent(GAIA::UI::Canvas* pParent);
			GINL GAIA::UI::Canvas* GetParent() const;
			GINL GAIA::BL Show(GAIA::BL bShow);
			GINL GAIA::BL IsShow() const;
			GINL GAIA::BL Position(const __PosType& pos);
			GINL __PosType Position() const;
			GINL GAIA::BL Size(const __SizeType& size);
			GINL __SizeType Size() const;
			GINL GAIA::BL SetCaptionText(const GAIA::TCH* pszCaptionText);
			GINL GAIA::BL GetCaptionText(GAIA::TCH* pszResult, GAIA::SIZE sResultMaxCharCount, GAIA::SIZE& sResultCount) const;
			GINL GAIA::GVOID* GetHandle() const;
			GINL GAIA::BL operator == (const GAIA::UI::Canvas& src) const;
			GINL GAIA::BL operator != (const GAIA::UI::Canvas& src) const;
			GINL GAIA::BL operator >= (const GAIA::UI::Canvas& src) const;
			GINL GAIA::BL operator <= (const GAIA::UI::Canvas& src) const;
			GINL GAIA::BL operator > (const GAIA::UI::Canvas& src) const;
			GINL GAIA::BL operator < (const GAIA::UI::Canvas& src) const;
		private:
			GINL GAIA::GVOID init();
			GINL GAIA::BL RegistToGlobalList();
			GINL GAIA::BL UnregistToGlobalList();
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