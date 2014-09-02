#ifndef		__GAIA_UI_CANVAS_INDP_H__
#define		__GAIA_UI_CANVAS_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <windows.h>
#else
#endif

#if GAIA_OS == GAIA_OS_WINDOWS
extern GAIA::SYNC::Lock g_windowlistlock;
extern GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<GAIA::UI::Canvas> > g_windowlist;
#else
#endif

namespace GAIA
{
	namespace UI
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if(message == WM_DESTROY)
			{
				::PostQuitMessage(0);
				return 0;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	#else
	#endif

		GAIA_DEBUG_CODEPURE_MEMFUNC Canvas::Canvas()
		{
			this->init();
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Canvas::~Canvas()
		{
			if(this->IsCreated())
				this->Destroy();
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::Create(const CanvasDesc& desc)
		{
			if(this->IsCreated())
				return GAIA::False;
			if(!desc.check())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			static const GAIA::TCH CLASS_PREFIX[] = _T("class_");
			GAIA::TCH szWindowClass[1024];
			if((GAIA::N32)GAIA::ALGORITHM::strlen(desc.pszCaptionText) >= 
				(GAIA::N32)sizeofarray(szWindowClass) - GAIA::ALGORITHM::strlen(CLASS_PREFIX))
				return GAIA::False;
			GAIA::ALGORITHM::strcpy(szWindowClass, CLASS_PREFIX);
			GAIA::ALGORITHM::strcat(szWindowClass, desc.pszCaptionText);
			WNDCLASSEX wcex;
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style			= CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc	= WindowProc;
			wcex.cbClsExtra		= 0;
			wcex.cbWndExtra		= 0;
			wcex.hInstance		= (HINSTANCE)GetModuleHandle(GNULL);
			wcex.hIcon			= GNULL;
			wcex.hCursor		= LoadCursor(GNULL, IDC_ARROW);
			wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName	= GNULL;
			wcex.lpszClassName	= szWindowClass;
			wcex.hIconSm		= GNULL;
			if(RegisterClassEx(&wcex) == 0)
				return GAIA::False;

			DWORD dwStyle;
			if(desc.style.bFrameStyle)
			{
				dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
				if(desc.style.bResizeAble)
					dwStyle |= WS_THICKFRAME;
			}
			else if(desc.style.bPopupStyle)
				dwStyle = WS_POPUP;
			else if(desc.style.bChildStyle)
				dwStyle = WS_CHILD;
			else
				dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
			if(desc.style.bMinimizeBox)
				dwStyle |= WS_MINIMIZEBOX;
			if(desc.style.bMaximizeBox)
				dwStyle |= WS_MAXIMIZEBOX;
			m_hWnd = ::CreateWindow(szWindowClass, 
				desc.pszCaptionText, 
				dwStyle, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				desc.pParent != GNULL ? desc.pParent->m_hWnd : GNULL, 
				GNULL, (HINSTANCE)GetModuleHandle(GNULL), GNULL);
			if(m_hWnd == GNULL)
			{
				::UnregisterClass(szWindowClass, (HINSTANCE)GetModuleHandle(GNULL));
				return GAIA::False;
			}
			if(!this->RegistToGlobalList())
			{
				GAIA_AST(GAIA::ALWAYSFALSE);
				return GAIA::False;
			}
			m_pszClassName = GAIA::ALGORITHM::strnew(szWindowClass);
			if(desc.pParent != GNULL)
			{
				if(!this->SetParent(desc.pParent))
				{
					this->Destroy();
					return GAIA::False;
				}
			}
			m_style = desc.style;
			return ::UpdateWindow(m_hWnd);
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::Destroy()
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(!this->UnregistToGlobalList())
			{
				GAIA_AST(GAIA::ALWAYSFALSE);
				return GAIA::False;
			}
			::DestroyWindow(m_hWnd);
			m_hWnd = GNULL;

			::UnregisterClass(m_pszClassName, (HINSTANCE)GetModuleHandle(GNULL));
			GAIA_MFREE(m_pszClassName);
			m_pszClassName = GNULL;

			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::IsCreated() const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(m_hWnd != GNULL)
				return GAIA::True;
			return GAIA::False;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::Quit()
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			::PostMessage(m_hWnd, WM_QUIT, 0, 0);
		#else
		#endif
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::SetParent(GAIA::UI::Canvas* pParent)
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(pParent == GNULL)
			{
				if(this->GetParent() == GNULL)
					return GAIA::False;
				::SetParent(m_hWnd, GNULL);
				DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
				if(m_style.bResizeAble)
					dwStyle |= WS_THICKFRAME;
				if(m_style.bMinimizeBox)
					dwStyle |= WS_MINIMIZEBOX;
				if(m_style.bMaximizeBox)
					dwStyle |= WS_MAXIMIZEBOX;
				if(::SetWindowLongPtr(m_hWnd, GWL_STYLE, dwStyle) == 0)
					return GAIA::False;
			}
			else
			{
				if(!pParent->IsCreated())
					return GAIA::False;
				GAIA::BL bExistParent = this->GetParent() != GNULL;
				::SetParent(m_hWnd, pParent->m_hWnd);
				if(!bExistParent)
				{
					if(::SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_CHILD) == 0)
						return GAIA::False;
				}
			}
			::ShowWindow(m_hWnd, SW_SHOW);
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UI::Canvas* Canvas::GetParent() const
		{
			if(!this->IsCreated())
				return GNULL;
		#if GAIA_OS == GAIA_OS_WINDOWS
			WINDOWINFO winfo;
			winfo.cbSize = sizeof(winfo);
			if(!::GetWindowInfo(m_hWnd, &winfo))
				return GAIA::False;
			if(winfo.dwStyle & WS_CHILD)
			{
				HWND hParent = ::GetParent(m_hWnd);
				if(hParent == GNULL)
					return GNULL;
				if(hParent == GetDesktopWindow())
					return GNULL;
				GAIA::UI::Canvas finder;
				finder.m_hWnd = hParent;
				GAIA::SYNC::AutoLock al(g_windowlistlock);
				GAIA::CONTAINER::Ref<GAIA::UI::Canvas> finderref(&finder);
				GAIA::CONTAINER::Ref<GAIA::UI::Canvas>* pFinded = g_windowlist.find(finderref);
				GAIA_AST(pFinded != GNULL);
				finder.m_hWnd = GNULL;
				return *pFinded;
			}
			return GNULL;
		#else
			return GNULL;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::Show(GAIA::BL bShow)
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(bShow)
			{
				if(this->IsShow())
					return GAIA::False;
				::ShowWindow(m_hWnd, SW_SHOW);
				return GAIA::True;
			}
			else
			{
				if(!this->IsShow())
					return GAIA::False;
				::ShowWindow(m_hWnd, SW_HIDE);
				return GAIA::True;
			}
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::IsShow() const
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::IsWindowVisible(m_hWnd))
				return GAIA::True;
			return GAIA::False;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::Position(const Canvas::__PosType& pos)
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(!::SetWindowPos(m_hWnd, GNULL, (GAIA::N32)pos.x, (GAIA::N32)pos.y, 0, 0, SWP_NOSIZE))
				return GAIA::False;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Canvas::__PosType Canvas::Position() const
		{
			if(!this->IsCreated())
			{
				__PosType ret;
				ret.x = 0;
				ret.y = 0;
				return ret;
			}
		#if GAIA_OS == GAIA_OS_WINDOWS
			RECT rc;
			if(!::GetWindowRect(m_hWnd, &rc))
			{
				__PosType ret;
				ret.x = 0;
				ret.y = 0;
				return ret;
			}
			__PosType ret;
			ret.x = (__PosType::_datatype)rc.left;
			ret.y = (__PosType::_datatype)rc.top;
			return ret;
		#else
			__PosType ret;
			ret.x = 0;
			ret.y = 0;
			return ret;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::Size(const Canvas::__SizeType& size)
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(!::SetWindowPos(m_hWnd, GNULL, 0, 0, size.x, size.y, SWP_NOMOVE))
				return GAIA::False;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Canvas::__SizeType Canvas::Size() const
		{
			if(!this->IsCreated())
			{
				__SizeType ret;
				ret.x = 0;
				ret.y = 0;
				return ret;
			}
		#if GAIA_OS == GAIA_OS_WINDOWS
			RECT rc;
			if(!::GetWindowRect(m_hWnd, &rc))
			{
				__SizeType ret;
				ret.x = 0;
				ret.y = 0;
				return ret;
			}
			__SizeType ret;
			ret.x = (__SizeType::_datatype)rc.right - rc.left;
			ret.y = (__SizeType::_datatype)rc.bottom - rc.top;
			return ret;
		#else
			__SizeType ret;
			ret.x = 0;
			ret.y = 0;
			return ret;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::SetCaptionText(const GAIA::TCH* pszCaptionText)
		{
			if(!this->IsCreated())
				return GAIA::False;
			if(pszCaptionText == GNULL)
				pszCaptionText = _T("");
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(!::SetWindowText(m_hWnd, pszCaptionText))
				return GAIA::False;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::GetCaptionText(GAIA::TCH* pszResult, GAIA::SIZE sResultMaxCharCount, GAIA::SIZE& sResultCount) const
		{
			if(!this->IsCreated())
				return GAIA::False;
			if(pszResult == GNULL)
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			sResultCount = ::GetWindowText(m_hWnd, pszResult, sResultMaxCharCount);
			if(sResultCount == 0)
				return GAIA::False;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::operator == (const GAIA::UI::Canvas& src) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return m_hWnd == src.m_hWnd;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::operator != (const GAIA::UI::Canvas& src) const
		{
			return !(this->operator == (src));
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::operator >= (const GAIA::UI::Canvas& src) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return m_hWnd >= src.m_hWnd;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::operator <= (const GAIA::UI::Canvas& src) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return m_hWnd <= src.m_hWnd;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::operator > (const GAIA::UI::Canvas& src) const
		{
			return !(this->operator <= (src));
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::operator < (const GAIA::UI::Canvas& src) const
		{
			return !(this->operator >= (src));
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Canvas::init()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			m_hWnd = GNULL;
			m_pszClassName = GNULL;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::RegistToGlobalList()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::SYNC::AutoLock al(g_windowlistlock);
			GAIA::CONTAINER::Ref<GAIA::UI::Canvas> finder(this);
			const GAIA::CONTAINER::Ref<GAIA::UI::Canvas>* pFinded = g_windowlist.find(finder);
			if(pFinded != GNULL)
				return GAIA::False;
			return g_windowlist.insert(finder);
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::UnregistToGlobalList()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::SYNC::AutoLock al(g_windowlistlock);
			GAIA::CONTAINER::Ref<GAIA::UI::Canvas> finder(this);
			const GAIA::CONTAINER::Ref<GAIA::UI::Canvas>* pFinded = g_windowlist.find(finder);
			if(pFinded == GNULL)
				return GAIA::False;
			return g_windowlist.erase(finder);
		#else
			return GAIA::False;
		#endif
		}
	};
};

#endif
