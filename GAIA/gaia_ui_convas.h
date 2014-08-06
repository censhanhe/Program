#ifndef		__GAIA_UI_CONVAS_H__
#define		__GAIA_UI_CONVAS_H__

namespace GAIA
{
	namespace UI
	{
		class Convas : public GAIA::FRAMEWORK::Instance
		{
		public:
			typedef GAIA::MATH::VEC2<GAIA::N32> __PosType;
			typedef __PosType __SizeType;
		public:
			class ConvasDesc
			{
			public:
				GINL ConvasDesc(){this->init();}
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
			private:
				GINL GAIA::GVOID init()
				{
					pszCaptionText = GNULL;
					pParent = GNULL;
					bFrameStyle = GAIA::True;
					bPopupStyle = GAIA::False;
					bChildStyle = GAIA::False;
					bMaximizeBox = GAIA::True;
					bMinimizeBox = GAIA::True;
				}
			public:
				GAIA::TCH* pszCaptionText;
				Convas* pParent;
				GAIA::U8 bFrameStyle : 1;
				GAIA::U8 bPopupStyle : 1;
				GAIA::U8 bChildStyle : 1;
				GAIA::U8 bMaximizeBox : 1;
				GAIA::U8 bMinimizeBox : 1;
			};
		public:
			GAIA_DEBUG_CODEPURE_MEMFUNC Convas();
			GAIA_DEBUG_CODEPURE_MEMFUNC ~Convas();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Create(const ConvasDesc& desc);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Destroy();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL IsCreated() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL SetParent(GAIA::UI::Convas* pParent);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UI::Convas* GetParent() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Show(GAIA::BL bShow);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL IsShow() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Position(const __PosType& pos);
			GAIA_DEBUG_CODEPURE_MEMFUNC __PosType Position() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Size(const __SizeType& size);
			GAIA_DEBUG_CODEPURE_MEMFUNC __SizeType Size() const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID SetCaptionText(const GAIA::TCH* pszCaptionText);
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
#	include "gaia_ui_convas_indp.h"
#endif

#endif