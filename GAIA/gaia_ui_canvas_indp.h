#ifndef		__GAIA_UI_CANVAS_INDP_H__
#define		__GAIA_UI_CANVAS_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#endif

#if GAIA_OS == GAIA_OS_WINDOWS
	extern GAIA::SYNC::Lock g_gaia_windowlistlock;
	extern GAIA::CTN::Set<GAIA::CTN::Ref<GAIA::UI::Canvas> > g_gaia_windowlist;
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

		GINL Canvas::Canvas()
		{
			this->init();
		}
		GINL Canvas::~Canvas()
		{
			if(this->IsCreated())
				this->Destroy();
		}
		GINL GAIA::BL Canvas::Create(const CanvasDesc& desc)
		{
			if(this->IsCreated())
				return GAIA::False;
			if(!desc.check())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			static const GAIA::TCH CLASS_PREFIX[] = _T("class_");
			GAIA::TCH szWindowClass[1024];
			if((GAIA::N32)GAIA::ALGO::strlen(desc.pszCaptionText) >= 
				(GAIA::N32)sizeofarray(szWindowClass) - GAIA::ALGO::strlen(CLASS_PREFIX))
				return GAIA::False;
			GAIA::ALGO::strcpy(szWindowClass, CLASS_PREFIX);
			GAIA::ALGO::strcat(szWindowClass, desc.pszCaptionText);
		#if GAIA_CHARSET == GAIA_CHARSET_ANSI
			WNDCLASSEXA wcex;
		#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
			WNDCLASSEXW wcex;
		#endif
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style			= CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc	= WindowProc;
			wcex.cbClsExtra		= 0;
			wcex.cbWndExtra		= 0;
			wcex.hInstance		= (HINSTANCE)GetModuleHandle(GNIL);
			wcex.hIcon			= GNIL;
			wcex.hCursor		= LoadCursor(GNIL, IDC_ARROW);
			wcex.hbrBackground	= GRCAST(HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName	= GNIL;
			wcex.lpszClassName	= szWindowClass;
			wcex.hIconSm		= GNIL;
		#if GAIA_CHARSET == GAIA_CHARSET_ANSI
			if(RegisterClassExA(&wcex) == 0)
		#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
			if(RegisterClassExW(&wcex) == 0)
		#endif
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
		#if GAIA_CHARSET == GAIA_CHARSET_ANSI
			m_hWnd = ::CreateWindowA(szWindowClass, 
				desc.pszCaptionText, 
				dwStyle, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				desc.pParent != GNIL ? desc.pParent->m_hWnd : GNIL, 
				GNIL, (HINSTANCE)GetModuleHandle(GNIL), GNIL);
		#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
			m_hWnd = ::CreateWindowW(szWindowClass, 
				desc.pszCaptionText, 
				dwStyle, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				CW_USEDEFAULT, 
				desc.pParent != GNIL ? desc.pParent->m_hWnd : GNIL, 
				GNIL, (HINSTANCE)GetModuleHandle(GNIL), GNIL);
		#endif
			if(m_hWnd == GNIL)
			{
		#if GAIA_CHARSET == GAIA_CHARSET_ANSI
				::UnregisterClassA(szWindowClass, (HINSTANCE)GetModuleHandle(GNIL));
		#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				::UnregisterClassW(szWindowClass, (HINSTANCE)GetModuleHandle(GNIL));
		#endif
				return GAIA::False;
			}
			if(!this->RegistToGlobalList())
			{
				GAIA_AST(GAIA::ALWAYSFALSE);
				return GAIA::False;
			}
			m_pszClassName = GAIA::ALGO::strnew(szWindowClass);
			if(desc.pParent != GNIL)
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
		GINL GAIA::BL Canvas::Destroy()
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
			m_hWnd = GNIL;

		#if GAIA_CHARSET == GAIA_CHARSET_ANSI
			::UnregisterClassA(m_pszClassName, (HINSTANCE)GetModuleHandle(GNIL));
		#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
			::UnregisterClassW(m_pszClassName, (HINSTANCE)GetModuleHandle(GNIL));
		#endif

			GAIA_MFREE(m_pszClassName);
			m_pszClassName = GNIL;

			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Canvas::IsCreated() const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(m_hWnd != GNIL)
				return GAIA::True;
			return GAIA::False;
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Canvas::Quit()
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			::PostMessage(m_hWnd, WM_QUIT, 0, 0);
		#else
		#endif
			return GAIA::True;
		}
		GINL GAIA::BL Canvas::SetParent(GAIA::UI::Canvas* pParent)
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(pParent == GNIL)
			{
				if(this->GetParent() == GNIL)
					return GAIA::False;
				::SetParent(m_hWnd, GNIL);
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
				GAIA::BL bExistParent = this->GetParent() != GNIL;
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
		GINL GAIA::UI::Canvas* Canvas::GetParent() const
		{
			if(!this->IsCreated())
				return GNIL;
		#if GAIA_OS == GAIA_OS_WINDOWS
			WINDOWINFO winfo;
			winfo.cbSize = sizeof(winfo);
			if(!::GetWindowInfo(m_hWnd, &winfo))
				return GAIA::False;
			if(winfo.dwStyle & WS_CHILD)
			{
				HWND hParent = ::GetParent(m_hWnd);
				if(hParent == GNIL)
					return GNIL;
				if(hParent == GetDesktopWindow())
					return GNIL;
				GAIA::UI::Canvas finder;
				finder.m_hWnd = hParent;
				GAIA::SYNC::AutoLock al(g_gaia_windowlistlock);
				GAIA::CTN::Ref<GAIA::UI::Canvas> finderref(&finder);
				GAIA::CTN::Ref<GAIA::UI::Canvas>* pFinded = g_gaia_windowlist.find(finderref);
				GAIA_AST(pFinded != GNIL);
				finder.m_hWnd = GNIL;
				return *pFinded;
			}
			return GNIL;
		#else
			return GNIL;
		#endif
		}
		GINL GAIA::BL Canvas::Show(GAIA::BL bShow)
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
		GINL GAIA::BL Canvas::IsShow() const
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
		GINL GAIA::BL Canvas::Position(const Canvas::__PosType& pos)
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(!::SetWindowPos(m_hWnd, GNIL, GSCAST(GAIA::N32)(pos.x), GSCAST(GAIA::N32)(pos.y), 0, 0, SWP_NOSIZE))
				return GAIA::False;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GINL Canvas::__PosType Canvas::Position() const
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
		GINL GAIA::BL Canvas::Size(const Canvas::__SizeType& size)
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			RECT rc, rcClient;
			::GetWindowRect(m_hWnd, &rc);
			::GetClientRect(m_hWnd, &rcClient);
			if(!::SetWindowPos(m_hWnd, GNIL, 0, 0, 
				size.x + (rc.right - rc.left) - (rcClient.right - rcClient.left), 
				size.y + (rc.bottom - rc.top) - (rcClient.bottom - rcClient.top), SWP_NOMOVE))
				return GAIA::False;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GINL Canvas::__SizeType Canvas::Size() const
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
			if(!::GetClientRect(m_hWnd, &rc))
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
		GINL GAIA::BL Canvas::SetCaptionText(const GAIA::TCH* pszCaptionText)
		{
			if(!this->IsCreated())
				return GAIA::False;
			if(pszCaptionText == GNIL)
				pszCaptionText = _T("");
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				if(!::SetWindowTextA(m_hWnd, pszCaptionText))
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				if(!::SetWindowTextW(m_hWnd, pszCaptionText))
		#	endif
				return GAIA::False;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Canvas::GetCaptionText(GAIA::TCH* pszResult, GAIA::SIZE sResultMaxCharCount, GAIA::SIZE& sResultCount) const
		{
			if(!this->IsCreated())
				return GAIA::False;
			if(pszResult == GNIL)
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				sResultCount = ::GetWindowTextA(m_hWnd, pszResult, sResultMaxCharCount);
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				sResultCount = ::GetWindowTextW(m_hWnd, pszResult, sResultMaxCharCount);
		#	endif
			if(sResultCount == 0)
				return GAIA::False;
			return GAIA::True;
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::GVOID* Canvas::GetHandle() const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return GSCAST(GAIA::GVOID*)(m_hWnd);
		#else
			return GNIL;
		#endif
		}
		GINL GAIA::BL Canvas::operator == (const GAIA::UI::Canvas& src) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return m_hWnd == src.m_hWnd;
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Canvas::operator != (const GAIA::UI::Canvas& src) const
		{
			return !(this->operator == (src));
		}
		GINL GAIA::BL Canvas::operator >= (const GAIA::UI::Canvas& src) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return m_hWnd >= src.m_hWnd;
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Canvas::operator <= (const GAIA::UI::Canvas& src) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			return m_hWnd <= src.m_hWnd;
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Canvas::operator > (const GAIA::UI::Canvas& src) const
		{
			return !(this->operator <= (src));
		}
		GINL GAIA::BL Canvas::operator < (const GAIA::UI::Canvas& src) const
		{
			return !(this->operator >= (src));
		}
		GINL GAIA::GVOID Canvas::init()
		{
			m_style.reset();
		#if GAIA_OS == GAIA_OS_WINDOWS
			m_hWnd = GNIL;
			m_pszClassName = GNIL;
		#else
		#endif
		}
		GINL GAIA::BL Canvas::RegistToGlobalList()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::SYNC::AutoLock al(g_gaia_windowlistlock);
			GAIA::CTN::Ref<GAIA::UI::Canvas> finder(this);
			const GAIA::CTN::Ref<GAIA::UI::Canvas>* pFinded = g_gaia_windowlist.find(finder);
			if(pFinded != GNIL)
				return GAIA::False;
			return g_gaia_windowlist.insert(finder);
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Canvas::UnregistToGlobalList()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::SYNC::AutoLock al(g_gaia_windowlistlock);
			GAIA::CTN::Ref<GAIA::UI::Canvas> finder(this);
			const GAIA::CTN::Ref<GAIA::UI::Canvas>* pFinded = g_gaia_windowlist.find(finder);
			if(pFinded == GNIL)
				return GAIA::False;
			return g_gaia_windowlist.erase(finder);
		#else
			return GAIA::False;
		#endif
		}
	};
};

#endif
