#ifndef 	__GAIA_NETWORK_INDP_H__
#define 	__GAIA_NETWORK_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
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

			if(desc.addr.ip.u4 == 0 && desc.addr.ip.u5 == 0)
			{
				if(this->IsStabilityLink())
					m_h = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				else
					m_h = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
				if(m_h == GINVALID)
					return GAIA::False;
		
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
			else
			{
				if(this->IsStabilityLink())
					m_h = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
				else
					m_h = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
				if(m_h == GINVALID)
					return GAIA::False;
				
				sockaddr_in6 sinaddr6;
				GAIA::ALGORITHM::memset(&sinaddr6, 0, sizeof(sinaddr6));
				sinaddr6.sin6_family = AF_INET6;
				sinaddr6.sin6_port = htons(desc.addr.uPort);
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

		/* NetworkSender's implement. */
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkSender::Begin()
		{
			if(this->IsBegin())
				return GAIA::False;
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkSender::End()
		{
			if(!this->IsBegin())
				return GAIA::False;
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
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkReceiver::End()
		{
			if(!this->IsBegin())
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID NetworkReceiver::WorkProcedule()
		{
		}
	};
};

#endif
