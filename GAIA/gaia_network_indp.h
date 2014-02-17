#ifndef 	__GAIA_NETWORK_INDP_H__
#define 	__GAIA_NETWORK_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <sys/errno.h>
#	include <sys/fcntl.h>
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <netdb.h>
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
				if(desc.bStabilityLink)
					m_h = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				else
					m_h = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
				if(m_h == GINVALID)
					return GAIA::False;

				// Connect.
				if(desc.bStabilityLink)
				{
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
				}
			}
			else // IPv6 version dispatch.
			{
				// Create socket.
				if(desc.bStabilityLink)
					m_h = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
				else
					m_h = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
				if(m_h == GINVALID)
					return GAIA::False;

				// Connect.
				if(desc.bStabilityLink)
				{
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
				}
			}

			//
			m_conndesc = desc;

			// Setup socket.
			setsockopt(m_h, SOL_SOCKET, SO_SNDBUF, (GAIA::GCH*)&m_nSendBufferSize, sizeof(m_nSendBufferSize));
			setsockopt(m_h, SOL_SOCKET, SO_RCVBUF, (GAIA::GCH*)&m_nRecvBufferSize, sizeof(m_nRecvBufferSize));
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::UM bNotBlockModeEnable = 1; ioctlsocket(m_h, FIONBIO, &bNotBlockModeEnable);
		#else
			GAIA::N32 flags = fcntl(m_h, F_GETFL, 0);
			fcntl(m_h, F_SETFL, flags | O_NONBLOCK);
		#endif

			return GAIA::True;
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
			if(pSender != GNULL)
				pSender->Add(*this);
			m_pSender = pSender;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID NetworkHandle::SetReceiver(NetworkReceiver* pReceiver)
		{
			if(pReceiver == m_pReceiver)
				return;
			if(m_pReceiver != GNULL)
				m_pReceiver->Remove(*this);
			if(pReceiver != GNULL)
				pReceiver->Add(*this);
			m_pReceiver = pReceiver;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC BL NetworkHandle::Send(const GAIA::U8* p, GAIA::UM uSize)
		{
			GAIA_AST(p != GNULL);
			GAIA_AST(uSize > 0);
			if(p == GNULL || uSize == 0)
				return GAIA::False;
			GAIA::U8* pNew = new GAIA::U8[uSize];
			GAIA::ALGORITHM::memcpy(pNew, p, uSize);
			GAIA::SYNC::AutoLock al(m_lock);
			SendRec r;
			r.p = pNew;
			r.uSize = uSize;
			m_sendque.push(r);
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL NetworkHandle::FlushSendQueue()
		{
			GAIA_AST(m_h != GINVALID);

			// Swap send queue to temp send vector.
			{
				GAIA::SYNC::AutoLock al(m_lock);
				if(m_sendque.empty())
					return GAIA::False;
				m_tempsendlist.clear();
				while(!m_sendque.empty())
				{
					m_tempsendlist.push_back(m_sendque.front());
					m_sendque.pop();
				}
			}

			// Send temp send vector.
			{
				for(GAIA::N32 x = 0; x < m_tempsendlist.size(); ++x)
				{
					SendRec& r = m_tempsendlist[x];
					GAIA_AST(r.p != GNULL);
					GAIA::U8* p = r.p;
					GAIA::UM uSize = r.uSize;
					while(uSize > 0)
					{
					#if GAIA_OS == GAIA_OS_LINUX || GAIA_OS == GAIA_OS_UNIX
						GAIA::N32 nSended = static_cast<GAIA::N32>(send(m_h, (const GAIA::GCH*)p, uSize, MSG_NOSIGNAL));
					#else
						GAIA::N32 nSended = static_cast<GAIA::N32>(send(m_h, (const GAIA::GCH*)p, uSize, 0));
					#endif
						if(nSended == GINVALID)
						{
						#if GAIA_OS == GAIA_OS_WINDOWS
							GAIA::N32 nLastError = ::WSAGetLastError();
							if(nLastError == WSAEWOULDBLOCK){}
							else
							{
								this->Reference();
								{
									this->Disconnect(GAIA::False);
									if(this->IsConnected())
										this->Disconnect();
								}
								this->Release();
								break;
							}
						#else
							if(errno == EAGAIN){}
							else
							{
								this->Reference();
								{
									this->Disconnect(GAIA::False);
									if(this->IsConnected())
										this->Disconnect();
								}
								this->Release();
								break;
							}
						#endif
						}
						else if(nSended == 0)
						{
							this->Reference();
							{
								this->Disconnect(GAIA::False);
								if(this->IsConnected())
									this->Disconnect();
							}
							this->Release();
							break;
						}
						else
						{
							p += nSended;
							uSize -= nSended;
						}
					}
					delete[] r.p;
				}
			}
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_FUNC GAIA::BL GetHostName(GAIA::GCH* pszResult, const GAIA::UM& size)
		{
			return gethostname(pszResult, size) != GINVALID;
		}
		GAIA_DEBUG_CODEPURE_FUNC GAIA::GVOID GetHostIPList(const GAIA::GCH* pszHostName, GAIA::CONTAINER::Vector<IP>& listResult)
		{
			hostent* pHostEnt = gethostbyname(pszHostName);
			if(pHostEnt != GNULL)
			{
				GAIA::N32 nIndex = 0;
				while(pHostEnt->h_addr_list[nIndex] != GNULL)
				{
					if(pHostEnt->h_addrtype == AF_INET)
					{
						in_addr* addr = (in_addr*)pHostEnt->h_addr_list[nIndex];
						IP ip;
						ip.Invalid();
						ip.u0 = (GAIA::U8)((GAIA::U32)((*(GAIA::U32*)addr) & 0x000000FF) >> 0);
						ip.u1 = (GAIA::U8)((GAIA::U32)((*(GAIA::U32*)addr) & 0x0000FF00) >> 8);
						ip.u2 = (GAIA::U8)((GAIA::U32)((*(GAIA::U32*)addr) & 0x00FF0000) >> 16);
						ip.u3 = (GAIA::U8)((GAIA::U32)((*(GAIA::U32*)addr) & 0xFF000000) >> 24);
						listResult.push_back(ip);
						++nIndex;
					}
					else if(pHostEnt->h_addrtype == AF_INET6)
					{
						// TODO : IPv6 convert.
					}
				}
			}
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
			m_bStopCmd = GAIA::True;
			{
				NetworkHandle::ConnectDesc descConn;
				descConn.addr = m_desc.addr;
				descConn.bStabilityLink = GAIA::True;
				NetworkHandle h;
				h.Connect(descConn);
				this->Wait();
			}
			m_bStopCmd = GAIA::False;
			m_bBegin = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID NetworkListener::WorkProcedure()
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
				// Stop command.
				if(m_bStopCmd)
					break;

				// Accept.
				sockaddr_in addrnew;
			#if GAIA_OS == GAIA_OS_WINDOWS
				GAIA::N32 newsize = sizeof(addrnew);
				GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &newsize);
			#else
				GAIA::U32 newsize;
				GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &newsize);
			#endif
				if(newsock != GINVALID)
				{
					// Setup socket.
					setsockopt(newsock, SOL_SOCKET, SO_SNDBUF, (GAIA::GCH*)&m_nSendBufferSize, sizeof(m_nSendBufferSize));
					setsockopt(newsock, SOL_SOCKET, SO_RCVBUF, (GAIA::GCH*)&m_nRecvBufferSize, sizeof(m_nRecvBufferSize));
				#if GAIA_OS == GAIA_OS_WINDOWS
					GAIA::UM bNotBlockModeEnable = 1; ioctlsocket(newsock, FIONBIO, &bNotBlockModeEnable);
				#else
					GAIA::N32 flags = fcntl(newsock, F_GETFL, 0);
					fcntl(newsock, F_SETFL, flags | O_NONBLOCK);
				#endif

					//
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

			// Close listen socket.
		#if GAIA_OS == GAIA_OS_WINDOWS
			shutdown(listensock, SD_BOTH);
			closesocket(listensock);
		#else
			shutdown(listensock, SHUT_RDWR);
			close(listensock);
		#endif
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
			m_bStopCmd = GAIA::True;
			this->Wait();
			m_bStopCmd = GAIA::False;
			m_bBegin = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID NetworkSender::WorkProcedure()
		{
			for(;;)
			{
				// Stop command.
				if(m_bStopCmd)
					break;

				// 
				GAIA::BL bExistWork = GAIA::False;

				// Copy network handle to handle list.
				{
					GAIA::SYNC::AutoLock al(m_lock);
					m_hl.clear();
					__HandleSetType::it iter = m_hs.front_it();
					while(!iter.empty())
					{
						NetworkHandle* pHandle = *iter;
						GAIA_AST(pHandle != GNULL);
						pHandle->Reference();
						m_hl.push_back(pHandle);
						++iter;
					}
				}

				// Flush all send buffer which in the handle list.
				{
					__HandleListType::it iter = m_hl.front_it();
					while(!iter.empty())
					{
						NetworkHandle* pHandle = *iter;
						if(pHandle->FlushSendQueue())
							bExistWork = GAIA::True;
						pHandle->Release();
						++iter;
					}
				}

				//
				if(!bExistWork)
					GAIA::SYNC::sleep(1);
			}
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
			m_bStopCmd = GAIA::True;
			this->Wait();
			m_bStopCmd = GAIA::False;
			m_bBegin = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID NetworkReceiver::WorkProcedure()
		{
			for(;;)
			{
				// Stop command.
				if(m_bStopCmd)
					break;

				//
				GAIA::BL bExistWork = GAIA::False;

				// Copy network handle to handle list.
				{
					GAIA::SYNC::AutoLock al(m_lock);
					m_hl.clear();
					__HandleSetType::it iter = m_hs.front_it();
					while(!iter.empty())
					{
						NetworkHandle* pHandle = *iter;
						GAIA_AST(pHandle != GNULL);
						pHandle->Reference();
						m_hl.push_back(pHandle);
						++iter;
					}
				}

				// Receive all socket which in the handle list.
				{
					__HandleListType::it iter = m_hl.front_it();
					while(!iter.empty())
					{
						NetworkHandle* pHandle = *iter;
						GAIA::BL bNeedRelease = GAIA::True;
						for(;;)
						{
							GAIA::N32 nRecv = (GAIA::N32)recv(pHandle->m_h, (GAIA::N8*)m_buf.front_ptr(), (GAIA::N32)m_buf.size(), 0);
							if(nRecv == GINVALID)
							{
							#if GAIA_OS == GAIA_OS_WINDOWS
								GAIA::N32 nLastError = ::WSAGetLastError();
								if(nLastError == WSAEWOULDBLOCK)
									break;
								else
								{
									pHandle->Reference();
									{
										if(this->Remove(*pHandle))
											bNeedRelease = GAIA::False;
										pHandle->Disconnect(GAIA::True);
										if(pHandle->IsConnected())
											pHandle->Disconnect();
									}
									pHandle->Release();
									break;
								}
							#else
								if(errno == EAGAIN)
									break;
								else
								{
									pHandle->Reference();
									{
										if(this->Remove(*pHandle))
											bNeedRelease = GAIA::False;
										pHandle->Disconnect(GAIA::True);
										if(pHandle->IsConnected())
											pHandle->Disconnect();
									}
									pHandle->Release();
									break;
								}
							#endif
							}
							else if(nRecv == 0)
							{
								pHandle->Reference();
								{
									if(this->Remove(*pHandle))
										bNeedRelease = GAIA::False;
									pHandle->Disconnect(GAIA::True);
									if(pHandle->IsConnected())
										pHandle->Disconnect();
								}
								pHandle->Release();
								break;
							}
							else
							{
								this->Receive(*pHandle, m_buf.front_ptr(), (GAIA::U32)nRecv);
								bExistWork = GAIA::True;
								if(nRecv < m_buf.size())
									break;
							}
						}
						if(bNeedRelease)
							pHandle->Release();
						++iter;
					}
				}

				//
				if(!bExistWork)
					GAIA::SYNC::sleep(1);
			}
		}
	};
};

#endif
