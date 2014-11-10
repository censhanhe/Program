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
			if(Canvas::WindowsMessageCallBack(hWnd, message, wParam, lParam))
				return TRUE;
			if(message == WM_DESTROY)
			{
				::PostQuitMessage(0);
				return 0;
			}
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		}
		GINL GAIA::BL Canvas::WindowsMessageCallBack(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch(message)
			{
			case WM_DESTROY:
			case WM_SHOWWINDOW:
			case WM_MOVE:
			case WM_MOVING:
			case WM_SIZE:
			case WM_SIZING:
			case WM_ACTIVATE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_KEYDOWN:
			case WM_KEYUP:
				break;

			default:
				return GAIA::False;
			}

			/* Find canvas pointer. */
			GAIA::UI::Canvas canvas;
			canvas.m_hWnd = hWnd;
			GAIA::CTN::Ref<GAIA::UI::Canvas>* pFinded;
			{
				GAIA::SYNC::AutoLock al(g_gaia_windowlistlock);
				GAIA::CTN::Ref<GAIA::UI::Canvas> finder(&canvas);
				pFinded = g_gaia_windowlist.find(finder);
				if(pFinded == GNIL)
				{
					canvas.m_hWnd = GNIL;
					return GAIA::False;
				}
			}
			canvas.m_hWnd = GNIL;

			Canvas* pFindedCanvas = *pFinded;
			GAIA_AST(pFindedCanvas != GNIL);
			if(pFindedCanvas == GNIL)
				return GAIA::False;

			GAIA::UI::Canvas::CallBack* pCallBack = pFindedCanvas->GetCallBack();

			switch(message)
			{
			case WM_DESTROY:
				{
					/*
					* If the PostQuitMessage be called, 
					* and the caller didn't call GAIA::UI::Canvas::Destroy function, 
					* below code will been executed. 
					*
					* Because call GAIA::UI::Canvas::Destroy function manually will
					* call UnregistFromGlobalList first,
					* so the pFindedCanvas will been GNIL, and cannot execute codes below.
					*/
					if(pFindedCanvas != GNIL) 
					{
						if(pCallBack != GNIL)
						{
							GAIA::UI::Message msg;
							msg.SetMsgType(GAIA::UI::Message::TYPE_DESTROY);
							pCallBack->Message(*pFindedCanvas, msg);
						}

						if(!pFindedCanvas->UnregistFromGlobalList())
							GAIA_AST(GAIA::ALWAYSFALSE);

						pFindedCanvas->m_hWnd = GNIL;

						GAIA_AST(!GAIA::ALGO::stremp(pFindedCanvas->m_pszClassName));
					#if GAIA_CHARSET == GAIA_CHARSET_ANSI
						::UnregisterClassA(pFindedCanvas->m_pszClassName, (HINSTANCE)GetModuleHandle(GNIL));
					#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
						::UnregisterClassW(pFindedCanvas->m_pszClassName, (HINSTANCE)GetModuleHandle(GNIL));
					#endif
						GAIA_MFREE(pFindedCanvas->m_pszClassName);
						pFindedCanvas->m_pszClassName = GNIL;

						return GAIA::False;
					}
				}
				break;

			case WM_SHOWWINDOW:
				{
					GAIA::UI::Message msg;
					if((BOOL)wParam)
						msg.SetMsgType(GAIA::UI::Message::TYPE_SHOW);
					else
						msg.SetMsgType(GAIA::UI::Message::TYPE_HIDE);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_MOVE:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_MOVED);
					GAIA::UI::Canvas::__PosType pos;
					pos.x = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(LOWORD(lParam));
					pos.y = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(HIWORD(lParam));
					msg.SetParam(0, &pos);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_MOVING:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_MOVE);
					GAIA::UI::Canvas::__PosType pos;
					const RECT* pRect = GRCAST(const RECT*)(lParam);
					pos.x = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(pRect->left);
					pos.y = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(pRect->top);
					msg.SetParam(0, &pos);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_SIZE:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_RESIZED);
					GAIA::UI::Canvas::__SizeType size;
					size.x = GSCAST(GAIA::UI::Canvas::__SizeType::_datatype)(LOWORD(lParam));
					size.y = GSCAST(GAIA::UI::Canvas::__SizeType::_datatype)(HIWORD(lParam));
					msg.SetParam(0, &size);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_SIZING:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_RESIZE);
					GAIA::UI::Canvas::__SizeType size;
					const RECT* pRect = GRCAST(const RECT*)(lParam);
					size.x = GSCAST(GAIA::UI::Canvas::__SizeType::_datatype)(pRect->right - pRect->left);
					size.y = GSCAST(GAIA::UI::Canvas::__SizeType::_datatype)(pRect->bottom - pRect->top);
					msg.SetParam(0, &size);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_ACTIVATE:
				{
					GAIA::UI::Message msg;
					if(wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
						msg.SetMsgType(GAIA::UI::Message::TYPE_ACTIVE);
					else
						msg.SetMsgType(GAIA::UI::Message::TYPE_INACTIVE);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_LBUTTONDOWN:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_CURSORDOWN);
					GAIA::UI::Canvas::__PosType pos;
					pos.x = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(LOWORD(lParam));
					pos.y = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(HIWORD(lParam));
					msg.SetParam(0, &pos);
					msg.SetParam(1, GAIA::INPUT::KEY_LBTN);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_LBUTTONUP:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_CURSORUP);
					GAIA::UI::Canvas::__PosType pos;
					pos.x = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(LOWORD(lParam));
					pos.y = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(HIWORD(lParam));
					msg.SetParam(0, &pos);
					msg.SetParam(1, GAIA::INPUT::KEY_LBTN);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_RBUTTONDOWN:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_CURSORDOWN);
					GAIA::UI::Canvas::__PosType pos;
					pos.x = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(LOWORD(lParam));
					pos.y = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(HIWORD(lParam));
					msg.SetParam(0, &pos);
					msg.SetParam(1, GAIA::INPUT::KEY_RBTN);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_RBUTTONUP:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_CURSORUP);
					GAIA::UI::Canvas::__PosType pos;
					pos.x = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(LOWORD(lParam));
					pos.y = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(HIWORD(lParam));
					msg.SetParam(0, &pos);
					msg.SetParam(1, GAIA::INPUT::KEY_RBTN);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_MBUTTONDOWN:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_CURSORDOWN);
					GAIA::UI::Canvas::__PosType pos;
					pos.x = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(LOWORD(lParam));
					pos.y = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(HIWORD(lParam));
					msg.SetParam(0, &pos);
					msg.SetParam(1, GAIA::INPUT::KEY_MBTN);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_MBUTTONUP:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_CURSORUP);
					GAIA::UI::Canvas::__PosType pos;
					pos.x = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(LOWORD(lParam));
					pos.y = GSCAST(GAIA::UI::Canvas::__PosType::_datatype)(HIWORD(lParam));
					msg.SetParam(0, &pos);
					msg.SetParam(1, GAIA::INPUT::KEY_MBTN);
					if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
						return GAIA::True;
				}
				break;

			case WM_KEYDOWN:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_KEYDOWN);

					GAIA::BL bCallBackAble = GAIA::True;
					if(GAIA::ALGO::isalpha(wParam))
					{
						GAIA::N32 nLower = GAIA::ALGO::tolower(wParam);
						msg.SetParam(0, nLower);
						msg.SetParam(1, GAIA::INPUT::KEY_A + nLower - 'a');
					}
					else if(GAIA::ALGO::isdigit(wParam))
					{
						msg.SetParam(0, GSCAST(GAIA::N32)(wParam));
						msg.SetParam(1, GAIA::INPUT::KEY_0 + wParam - '0');
					}
					else
					{
						switch(wParam)
						{
						case VK_SPACE:
							msg.SetParam(0, GSCAST(GAIA::N32)(' '));
							msg.SetParam(1, GAIA::INPUT::KEY_SPACE);
							break;
						case VK_TAB:
							msg.SetParam(0, GSCAST(GAIA::N32)('\t'));
							msg.SetParam(1, GAIA::INPUT::KEY_TAB);
							break;
						case VK_RETURN:
							msg.SetParam(0, GSCAST(GAIA::N32)('\n'));
							msg.SetParam(1, GAIA::INPUT::KEY_ENTER);
							break;
						case VK_OEM_4:
							msg.SetParam(0, GSCAST(GAIA::N32)('['));
							msg.SetParam(1, GAIA::INPUT::KEY_LEFTSQUAREBRACKET);
							break;
						case VK_OEM_6:
							msg.SetParam(0, GSCAST(GAIA::N32)(']'));
							msg.SetParam(1, GAIA::INPUT::KEY_RIGHTSQUAREBRACKET);
							break;
						case VK_OEM_COMMA:
							msg.SetParam(0, GSCAST(GAIA::N32)(','));
							msg.SetParam(1, GAIA::INPUT::KEY_COMMA);
							break;
						case VK_OEM_PERIOD:
							msg.SetParam(0, GSCAST(GAIA::N32)('.'));
							msg.SetParam(1, GAIA::INPUT::KEY_POINT);
							break;
						case VK_OEM_2:
							msg.SetParam(0, GSCAST(GAIA::N32)('/'));
							msg.SetParam(1, GAIA::INPUT::KEY_SLASH);
							break;
						case VK_OEM_5:
							msg.SetParam(0, GSCAST(GAIA::N32)('\\'));
							msg.SetParam(1, GAIA::INPUT::KEY_INVERSESLASH);
							break;
						case VK_OEM_3:
							msg.SetParam(0, GSCAST(GAIA::N32)('`'));
							msg.SetParam(1, GAIA::INPUT::KEY_UPPOINT);
							break;
						case VK_OEM_1:
							msg.SetParam(0, GSCAST(GAIA::N32)(';'));
							msg.SetParam(1, GAIA::INPUT::KEY_SEMICOLON);
							break;
						case VK_OEM_7:
							msg.SetParam(0, GSCAST(GAIA::N32)('\''));
							msg.SetParam(1, GAIA::INPUT::KEY_QUOTES);
							break;
						case VK_BACK:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_BACKSPACE);
							break;
						case VK_DELETE:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_DELETE);
							break;
						case VK_LEFT:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_LEFT);
							break;
						case VK_RIGHT:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_RIGHT);
							break;
						case VK_UP:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_UP);
							break;
						case VK_DOWN:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_DOWN);
							break;
						case VK_HOME:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_HOME);
							break;
						case VK_END:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_END);
							break;
						case VK_PRIOR:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_PAGEUP);
							break;
						case VK_NEXT:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_PAGEDOWN);
							break;
						case VK_F1:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F1);
							break;
						case VK_F2:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F2);
							break;
						case VK_F3:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F3);
							break;
						case VK_F4:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F4);
							break;
						case VK_F5:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F5);
							break;
						case VK_F6:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F6);
							break;
						case VK_F7:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F7);
							break;
						case VK_F8:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F8);
							break;
						case VK_F9:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F9);
							break;
						case VK_F10:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F10);
							break;
						case VK_F11:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F11);
							break;
						case VK_F12:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F12);
							break;
						case VK_NUMPAD0:
							msg.SetParam(0, GSCAST(GAIA::N32)('0'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM0);
							break;
						case VK_NUMPAD1:
							msg.SetParam(0, GSCAST(GAIA::N32)('1'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM1);
							break;
						case VK_NUMPAD2:
							msg.SetParam(0, GSCAST(GAIA::N32)('2'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM2);
							break;
						case VK_NUMPAD3:
							msg.SetParam(0, GSCAST(GAIA::N32)('3'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM3);
							break;
						case VK_NUMPAD4:
							msg.SetParam(0, GSCAST(GAIA::N32)('4'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM4);
							break;
						case VK_NUMPAD5:
							msg.SetParam(0, GSCAST(GAIA::N32)('5'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM5);
							break;
						case VK_NUMPAD6:
							msg.SetParam(0, GSCAST(GAIA::N32)('6'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM6);
							break;
						case VK_NUMPAD7:
							msg.SetParam(0, GSCAST(GAIA::N32)('7'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM7);
							break;
						case VK_NUMPAD8:
							msg.SetParam(0, GSCAST(GAIA::N32)('8'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM8);
							break;
						case VK_NUMPAD9:
							msg.SetParam(0, GSCAST(GAIA::N32)('9'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM9);
							break;
						case VK_CONTROL:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_CTRL);
							break;
						case VK_MENU:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_ALT);
							break;
						case VK_SHIFT:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_SHIFT);
							break;
						case VK_ESCAPE:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_ESC);
							break;
						default:
							bCallBackAble = GAIA::False;
							break;
						}
					}

					if(bCallBackAble)
					{
						if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
							return GAIA::True;
					}
				}
				break;

			case WM_KEYUP:
				{
					GAIA::UI::Message msg;
					msg.SetMsgType(GAIA::UI::Message::TYPE_KEYUP);

					GAIA::BL bCallBackAble = GAIA::True;
					if(GAIA::ALGO::isalpha(wParam))
					{
						GAIA::N32 nLower = GAIA::ALGO::tolower(wParam);
						msg.SetParam(0, nLower);
						msg.SetParam(1, GAIA::INPUT::KEY_A + nLower - 'a');
					}
					else if(GAIA::ALGO::isdigit(wParam))
					{
						msg.SetParam(0, GSCAST(GAIA::N32)(wParam));
						msg.SetParam(1, GAIA::INPUT::KEY_0 + wParam - '0');
					}
					else
					{
						switch(wParam)
						{
						case VK_SPACE:
							msg.SetParam(0, GSCAST(GAIA::N32)(' '));
							msg.SetParam(1, GAIA::INPUT::KEY_SPACE);
							break;
						case VK_TAB:
							msg.SetParam(0, GSCAST(GAIA::N32)('\t'));
							msg.SetParam(1, GAIA::INPUT::KEY_TAB);
							break;
						case VK_RETURN:
							msg.SetParam(0, GSCAST(GAIA::N32)('\n'));
							msg.SetParam(1, GAIA::INPUT::KEY_ENTER);
							break;
						case VK_OEM_4:
							msg.SetParam(0, GSCAST(GAIA::N32)('['));
							msg.SetParam(1, GAIA::INPUT::KEY_LEFTSQUAREBRACKET);
							break;
						case VK_OEM_6:
							msg.SetParam(0, GSCAST(GAIA::N32)(']'));
							msg.SetParam(1, GAIA::INPUT::KEY_RIGHTSQUAREBRACKET);
							break;
						case VK_OEM_COMMA:
							msg.SetParam(0, GSCAST(GAIA::N32)(','));
							msg.SetParam(1, GAIA::INPUT::KEY_COMMA);
							break;
						case VK_OEM_PERIOD:
							msg.SetParam(0, GSCAST(GAIA::N32)('.'));
							msg.SetParam(1, GAIA::INPUT::KEY_POINT);
							break;
						case VK_OEM_2:
							msg.SetParam(0, GSCAST(GAIA::N32)('/'));
							msg.SetParam(1, GAIA::INPUT::KEY_SLASH);
							break;
						case VK_OEM_5:
							msg.SetParam(0, GSCAST(GAIA::N32)('\\'));
							msg.SetParam(1, GAIA::INPUT::KEY_INVERSESLASH);
							break;
						case VK_OEM_3:
							msg.SetParam(0, GSCAST(GAIA::N32)('`'));
							msg.SetParam(1, GAIA::INPUT::KEY_UPPOINT);
							break;
						case VK_OEM_1:
							msg.SetParam(0, GSCAST(GAIA::N32)(';'));
							msg.SetParam(1, GAIA::INPUT::KEY_SEMICOLON);
							break;
						case VK_OEM_7:
							msg.SetParam(0, GSCAST(GAIA::N32)('\''));
							msg.SetParam(1, GAIA::INPUT::KEY_QUOTES);
							break;
						case VK_BACK:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_BACKSPACE);
							break;
						case VK_DELETE:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_DELETE);
							break;
						case VK_LEFT:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_LEFT);
							break;
						case VK_RIGHT:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_RIGHT);
							break;
						case VK_UP:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_UP);
							break;
						case VK_DOWN:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_DOWN);
							break;
						case VK_HOME:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_HOME);
							break;
						case VK_END:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_END);
							break;
						case VK_PRIOR:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_PAGEUP);
							break;
						case VK_NEXT:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_PAGEDOWN);
							break;
						case VK_F1:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F1);
							break;
						case VK_F2:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F2);
							break;
						case VK_F3:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F3);
							break;
						case VK_F4:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F4);
							break;
						case VK_F5:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F5);
							break;
						case VK_F6:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F6);
							break;
						case VK_F7:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F7);
							break;
						case VK_F8:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F8);
							break;
						case VK_F9:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F9);
							break;
						case VK_F10:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F10);
							break;
						case VK_F11:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F11);
							break;
						case VK_F12:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_F12);
							break;
						case VK_NUMPAD0:
							msg.SetParam(0, GSCAST(GAIA::N32)('0'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM0);
							break;
						case VK_NUMPAD1:
							msg.SetParam(0, GSCAST(GAIA::N32)('1'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM1);
							break;
						case VK_NUMPAD2:
							msg.SetParam(0, GSCAST(GAIA::N32)('2'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM2);
							break;
						case VK_NUMPAD3:
							msg.SetParam(0, GSCAST(GAIA::N32)('3'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM3);
							break;
						case VK_NUMPAD4:
							msg.SetParam(0, GSCAST(GAIA::N32)('4'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM4);
							break;
						case VK_NUMPAD5:
							msg.SetParam(0, GSCAST(GAIA::N32)('5'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM5);
							break;
						case VK_NUMPAD6:
							msg.SetParam(0, GSCAST(GAIA::N32)('6'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM6);
							break;
						case VK_NUMPAD7:
							msg.SetParam(0, GSCAST(GAIA::N32)('7'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM7);
							break;
						case VK_NUMPAD8:
							msg.SetParam(0, GSCAST(GAIA::N32)('8'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM8);
							break;
						case VK_NUMPAD9:
							msg.SetParam(0, GSCAST(GAIA::N32)('9'));
							msg.SetParam(1, GAIA::INPUT::KEY_NUM9);
							break;
						case VK_CONTROL:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_CTRL);
							break;
						case VK_MENU:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_ALT);
							break;
						case VK_SHIFT:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_SHIFT);
							break;
						case VK_ESCAPE:
							msg.SetParam(0, GSCAST(GAIA::N32)(0));
							msg.SetParam(1, GAIA::INPUT::KEY_ESC);
							break;
						default:
							bCallBackAble = GAIA::False;
							break;
						}
					}

					if(bCallBackAble)
					{
						if(pCallBack != GNIL && pCallBack->Message(*pFindedCanvas, msg))
							return GAIA::True;
					}
				}
				break;

			default:
				break;
			}

			return GAIA::False;
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
		GINL GAIA::BL Canvas::Create(const Desc& desc)
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

			if(m_pCallBack != GNIL)
			{
				GAIA::UI::Message msg;
				msg.SetMsgType(GAIA::UI::Message::TYPE_CREATE);
				m_pCallBack->Message(*this, msg);
			}

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
			if(m_pCallBack != GNIL)
			{
				GAIA::UI::Message msg;
				msg.SetMsgType(GAIA::UI::Message::TYPE_DESTROY);
				m_pCallBack->Message(*this, msg);
			}

			if(!this->UnregistFromGlobalList())
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
			m_pCallBack = GNIL;
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
			GAIA_AST(pFinded == GNIL);
			if(pFinded != GNIL)
				return GAIA::False;
			return g_gaia_windowlist.insert(finder);
		#else
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Canvas::UnregistFromGlobalList()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::SYNC::AutoLock al(g_gaia_windowlistlock);
			GAIA::CTN::Ref<GAIA::UI::Canvas> finder(this);
			const GAIA::CTN::Ref<GAIA::UI::Canvas>* pFinded = g_gaia_windowlist.find(finder);
			GAIA_AST(pFinded != GNIL);
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
