#ifndef 	__GAIA_NETWORK_INDP_H__
#define 	__GAIA_NETWORK_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#endif

namespace GAIA
{
	namespace NETWORK
	{
		/* NetworkHandle's implement. */
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkHandle::Connect(const ConnectDesc& desc)
		{
			if(this->IsConnected())
				this->Disconnect();
			
			if(desc.addr.IsInvalid())
				return GAIA::False;

			if(desc.addr.ip.u4 == 0 && desc.addr.ip.u5 == 0) // IPv4 version dispatch.
			{
				// Create socket.
				if(this->IsStabilityLink())
					m_h = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				else
					m_h = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
				if(m_h == GINVALID)
					return GAIA::False;
		
				// Connect.
				sockaddr_in sinaddr;
				GAIA::ALGORITHM::memset(&sinaddr, 0, sizeof(sinaddr));
				sinaddr.sin_family = AF_INET;
				sinaddr.sin_port = htons(desc.addr.uPort);
				sinaddr.sin_addr.s_addr =
					(desc.addr.ip.u0 << 0) |
					(desc.addr.ip.u1 << 8) |
					(desc.addr.ip.u2 << 16) |
					(desc.addr.ip.u3 << 24);
				if(connect(m_h, (sockaddr*)&sinaddr, sizeof(sinaddr)) == GINVALID)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS
					closesocket(m_h);
				#else
					close(m_h);
				#endif
					m_h = GINVALID;
					return GAIA::False;
				}
				m_conndesc = desc;
				return GAIA::True;
			}
			else // IPv6 version dispatch.
			{
				// Create socket.
				if(this->IsStabilityLink())
					m_h = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
				else
					m_h = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
				if(m_h == GINVALID)
					return GAIA::False;

				// Connect.
				sockaddr_in6 sinaddr6;
				GAIA::ALGORITHM::memset(&sinaddr6, 0, sizeof(sinaddr6));
				sinaddr6.sin6_family = AF_INET6;
				sinaddr6.sin6_port = htons(desc.addr.uPort);
				// TODO : IPv6 convert.
				if(connect(m_h, (sockaddr*)&sinaddr6, sizeof(sinaddr6)) == GINVALID)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS
					closesocket(m_h);
				#else
					close(m_h);
				#endif
					m_h = GINVALID;
					return GAIA::False;
				}
				m_conndesc = desc;
				return GAIA::True;
			}
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkHandle::Disconnect()
		{
			if(!this->IsConnected())
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			shutdown(m_h, SD_BOTH);
			closesocket(m_h);
		#else
			shutdown(m_h, SHUT_RDWR);
			close(m_h);
		#endif
			this->init();
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID NetworkHandle::SetSender(NetworkSender* pSender)
		{
			if(pSender == m_pSender)
				return;
			if(m_pSender != GNULL)
				m_pSender->Remove(*this);
			pSender->Add(*this);
			m_pSender = pSender;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID NetworkHandle::SetReceiver(NetworkReceiver* pReceiver)
		{
			if(pReceiver == m_pReceiver)
				return;
			if(m_pReceiver != GNULL)
				m_pReceiver->Remove(*this);
			pReceiver->Add(*this);
			m_pReceiver = pReceiver;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC BL NetworkHandle::Send(const GAIA::U8* p, GAIA::UM uSize)
		{
			GAIA_AST(p != GNULL);
			GAIA_AST(uSize > 0);
			if(p == GNULL || uSize == 0)
				return GAIA::False;

			return GAIA::True;
		}
		/* NetworkListener's implement. */
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkListener::Begin()
		{
			if(this->IsBegin())
				return GAIA::False;
			m_bBegin = GAIA::True;
			this->Run();
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkListener::End()
		{
			if(!this->IsBegin())
				return GAIA::False;
			this->Wait();
			return GAIA::True;
		}
		GINL GAIA::GVOID NetworkListener::WorkProcedule()
		{
			GAIA::N32 listensock = GINVALID;
			if(m_desc.addr.ip.u4 == 0 && m_desc.addr.ip.u5 == 0) // IPv4 version dispatch.
			{
				// Create socket.
				listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				if(listensock == GINVALID)
					return;

				// Bind.
				sockaddr_in addr;
				GAIA::ALGORITHM::memset(&addr, 0, sizeof(addr));
				addr.sin_family = AF_INET;
				addr.sin_port = htons(m_desc.addr.uPort);
				addr.sin_addr.s_addr =
					(m_desc.addr.ip.u0 << 0) |
					(m_desc.addr.ip.u1 << 8) |
					(m_desc.addr.ip.u2 << 16) |
					(m_desc.addr.ip.u3 << 24);
				if(bind(listensock, (sockaddr*)&addr, sizeof(addr)) < 0)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS
					closesocket(listensock);
				#else
					close(listensock);
				#endif
					return;
				}

				// Listen.
				if(listen(listensock, SOMAXCONN) < 0)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS
					shutdown(listensock, SD_BOTH);
					closesocket(listensock);
				#else
					shutdown(listensock, SHUT_RDWR);
					close(listensock);
				#endif
					return;
				}

				// Accept.
				for(;;)
				{
					sockaddr_in addrnew;
				#if GAIA_OS == GAIA_OS_WINDOWS
					GAIA::N32 newsize;
					GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &newsize);
				#else
					GAIA::U32 newsize;
					GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &newsize);
				#endif
					if(newsock != GINVALID)
					{
						NetworkHandle* h = new NetworkHandle;
						h->m_h = newsock;
						h->m_addr_self = m_desc.addr;
						h->m_conndesc.addr.ip.u0 = (GAIA::U8)((GAIA::U32)(addrnew.sin_addr.s_addr & 0x000000FF) >> 0);
						h->m_conndesc.addr.ip.u1 = (GAIA::U8)((GAIA::U32)(addrnew.sin_addr.s_addr & 0x0000FF00) >> 8);
						h->m_conndesc.addr.ip.u2 = (GAIA::U8)((GAIA::U32)(addrnew.sin_addr.s_addr & 0x00FF0000) >> 16);
						h->m_conndesc.addr.ip.u3 = (GAIA::U8)((GAIA::U32)(addrnew.sin_addr.s_addr & 0xFF000000) >> 24);
						h->m_addr_self.uPort = ntohs(addrnew.sin_port);
						this->Accept(*h);
						h->Release();
					}
				}
			}
			else // IPv6 version dispatch.
			{
				// Create socket.
				listensock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
				if(listensock == GINVALID)
					return;

				// Bind.
				sockaddr_in6 addr;
				GAIA::ALGORITHM::memset(&addr, 0, sizeof(addr));
				addr.sin6_family = AF_INET6;
				addr.sin6_port = htons(m_desc.addr.uPort);
				// TODO : IPv6 convert.
				if(bind(listensock, (sockaddr*)&addr, sizeof(addr)) < 0)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS
					closesocket(listensock);
				#else
					close(listensock);
				#endif
					return;
				}

				// Listen.
				if(listen(listensock, SOMAXCONN) < 0)
				{
				#if GAIA_OS == GAIA_OS_WINDOWS
					shutdown(listensock, SD_BOTH);
					closesocket(listensock);
				#else
					shutdown(listensock, SHUT_RDWR);
					close(listensock);
				#endif
					return;
				}

				// Accept.
				for(;;)
				{
					sockaddr_in addrnew;
				#if GAIA_OS == GAIA_OS_WINDOWS
					GAIA::N32 newsize;
					GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &newsize);
				#else
					GAIA::U32 newsize;
					GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &newsize);
				#endif
					if(newsock != GINVALID)
					{
						NetworkHandle* h = new NetworkHandle;
						h->m_h = newsock;
						h->m_addr_self = m_desc.addr;
						// TODO : IPv6 convert.
						h->m_addr_self.uPort = ntohs(addrnew.sin_port);
						this->Accept(*h);
						h->Release();
					}
				}
			}
		}
		/* NetworkSender's implement. */
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkSender::Begin()
		{
			if(this->IsBegin())
				return GAIA::False;
			m_bBegin = GAIA::True;
			this->Run();
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkSender::End()
		{
			if(!this->IsBegin())
				return GAIA::False;
			this->Wait();
			return GAIA::True;
		}
		GINL GAIA::GVOID NetworkSender::WorkProcedule()
		{
		}
		/* NetworkReceiver's implement. */
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkReceiver::Begin()
		{
			if(this->IsBegin())
				return GAIA::False;
			m_bBegin = GAIA::True;
			this->Run();
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkReceiver::End()
		{
			if(!this->IsBegin())
				return GAIA::False;
			this->Wait();
			return GAIA::True;
		}
		GINL GAIA::GVOID NetworkReceiver::WorkProcedule()
		{
		}
	};
};

#endif
