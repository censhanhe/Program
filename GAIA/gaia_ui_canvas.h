#ifndef		__GAIA_UI_CANVAS_H__
#define		__GAIA_UI_CANVAS_H__

namespace GAIA
{
	namespace UI
	{
		class Canvas : public virtual GAIA::FRAMEWORK::Instance
		{
		public:
			typedef GAIA::MATH::VEC2<GAIA::N32> __PosType;
			typedef __PosType __SizeType;
		public:
			class CanvasDesc
			{
			public:
				GINL CanvasDesc(){this->reset();}
				GINL GAIA::GVOID reset()
				{
					pszCaptionText = GNULL;
					pParent = GNULL;
					bFrameStyle = GAIA::True;
					bPopupStyle = GAIA::False;
					bChildStyle = GAIA::False;
					bMaximizeBox = GAIA::True;
					bMinimizeBox = GAIA::True;
					bResizeAble = GAIA::True;
				}
				GINL GAIA::BL check() const
				{
					GAIA::SIZE nMutexGroup = 0;
					if(bFrameStyle)
						++nMutexGroup;
					if(bPopupStyle)
						++nMutexGroup;
					if(bChildStyle)
						++nMutexGroup;
					if(nMutexGroup != 1)
						return GAIA::False;
					if(bChildStyle && pParent == GNULL)
						return GAIA::False;
					return GAIA::True;
				}
			public:
				GAIA::TCH* pszCaptionText;
				Canvas* pParent;
				GAIA::U8 bFrameStyle : 1;
				GAIA::U8 bPopupStyle : 1;
				GAIA::U8 bChildStyle : 1;
				GAIA::U8 bMaximizeBox : 1;
				GAIA::U8 bMinimizeBox : 1;
				GAIA::U8 bResizeAble : 1;
			};
		public:
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::CLSID_CANVAS;}
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
		private:
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID init();
		private:
		#if GAIA_OS == GAIA_OS_WINDOWS
			HWND m_hWnd;
			GAIA::TCH* m_pszClassName;
		#else
		#endif
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_ui_canvas_indp.h"
#endif

#endif