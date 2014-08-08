#ifndef		__GAIA_UI_CANVAS_INDP_H__
#define		__GAIA_UI_CANVAS_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	include <windows.h>
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
				::PostQuitMessage(0);
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::Create(const ConvasDesc& desc)
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
			if(desc.bFrameStyle)
			{
				dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
				if(desc.bResizeAble)
					dwStyle |= WS_THICKFRAME;
			}
			else if(desc.bPopupStyle)
				dwStyle = WS_POPUP;
			else if(desc.bChildStyle)
				dwStyle = WS_CHILD;
			else
				dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
			if(desc.bMinimizeBox)
				dwStyle |= WS_MINIMIZEBOX;
			if(desc.bMaximizeBox)
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
			m_pszClassName = GAIA::ALGORITHM::strnew(szWindowClass);
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::SetParent(GAIA::UI::Canvas* pParent)
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::UI::Canvas* Canvas::GetParent() const
		{
			if(!this->IsCreated())
				return GNULL;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#else
			return GNULL;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Canvas::Show(GAIA::BL bShow)
		{
			if(!this->IsCreated())
				return;
		#if GAIA_OS == GAIA_OS_WINDOWS
			::ShowWindow(m_hWnd, SW_SHOW);
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Canvas::IsShow() const
		{
			if(!this->IsCreated())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			::ShowWindow(m_hWnd, SW_HIDE);
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Canvas::Position(const Canvas::__PosType& pos)
		{
			if(!this->IsCreated())
				return;
		#if GAIA_OS == GAIA_OS_WINDOWS
			::SetWindowPos(m_hWnd, GNULL, (GAIA::N32)pos.x, (GAIA::N32)pos.y, 0, 0, SWP_NOSIZE);
		#else
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Canvas::Size(const Canvas::__SizeType& size)
		{
			if(!this->IsCreated())
				return;
		#if GAIA_OS == GAIA_OS_WINDOWS
			::SetWindowPos(m_hWnd, GNULL, 0, 0, size.x, size.y, SWP_NOREPOSITION);
		#else
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Canvas::SetCaptionText(const GAIA::TCH* pszCaptionText)
		{
			if(!this->IsCreated())
				return;
			if(pszCaptionText == GNULL)
				pszCaptionText = _T("");
		#if GAIA_OS == GAIA_OS_WINDOWS
			::SetWindowText(m_hWnd, pszCaptionText);
		#else
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
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Canvas::init()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			m_hWnd = GNULL;
			m_pszClassName = GNULL;
		#else
		#endif
		}
	};
};

#endif