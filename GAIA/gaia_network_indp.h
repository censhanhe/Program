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

			// Create socket.
			if(desc.bStabilityLink)
				m_h = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			else
				m_h = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if(m_h == GINVALID)
				return GAIA::False;

			// Setup socket buffer size.
			if(setsockopt(m_h, SOL_SOCKET, SO_SNDBUF, (GAIA::GCH*)&m_nSendBufferSize, sizeof(m_nSendBufferSize)) != 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				closesocket(m_h);
			#else
				close(m_h);
			#endif
				return GAIA::False;
			}
			if(setsockopt(m_h, SOL_SOCKET, SO_RCVBUF, (GAIA::GCH*)&m_nRecvBufferSize, sizeof(m_nRecvBufferSize)) != 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				closesocket(m_h);
			#else
				close(m_h);
			#endif
				return GAIA::False;
			}

			// Construct network address.
			sockaddr_in sinaddr;
			GAIA::ALGORITHM::memset(&sinaddr, 0, sizeof(sinaddr));
			sinaddr.sin_family = AF_INET;
			sinaddr.sin_port = htons(desc.addr.uPort);
			sinaddr.sin_addr.s_addr =
				(desc.addr.ip.u0 << 0) |
				(desc.addr.ip.u1 << 8) |
				(desc.addr.ip.u2 << 16) |
				(desc.addr.ip.u3 << 24);

			// Connect.
			if(desc.bStabilityLink)
			{
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
			else
			{
				if(bind(m_h, (sockaddr*)&sinaddr, sizeof(sinaddr)) < 0)
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

			//
			m_conndesc = desc;

			// Setup socket mode.
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if defined(GAIA_DEBUG_CODEPURE) && !defined(GAIA_NOCANCEL_ORIGINTYPE)
		#		undef long
		#	endif
			GAIA::UM bNotBlockModeEnable = 1; ioctlsocket(m_h, FIONBIO, &bNotBlockModeEnable);
		#	if defined(GAIA_DEBUG_CODEPURE) && !defined(GAIA_NOCANCEL_ORIGINTYPE)
		#		define long GAIA_INVALID_ORIGINTYPE
		#	endif
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
		GAIA_DEBUG_CODEPURE_MEMFUNC BL NetworkHandle::Send(const GAIA::U8* p, GAIA::U32 uSize)
		{
			GAIA_AST(p != GNULL);
			GAIA_AST(uSize > 0);
			if(p == GNULL || uSize == 0)
				return GAIA::False;
			if(!this->IsStabilityLink())
			{
				if(uSize <= sizeof(NetworkAddress))
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				if(uSize > MAX_NOSTABILITY_SENDSIZE + sizeof(NetworkAddress))
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			GAIA::U8* pNew = GAIA_MALLOC(GAIA::U8, uSize);
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
					GAIA::U32 uSize = r.uSize;
					if(!this->IsStabilityLink())
					{
						p += sizeof(NetworkAddress);
						uSize -= sizeof(NetworkAddress);
					}
					while(uSize > 0)
					{
						GAIA::N32 nSended;
						if(this->IsStabilityLink())
						{
						#if GAIA_OS == GAIA_OS_LINUX || GAIA_OS == GAIA_OS_UNIX
							nSended = static_cast<GAIA::N32>(send(
								m_h, (const GAIA::GCH*)p, uSize, MSG_NOSIGNAL));
						#else
							nSended = static_cast<GAIA::N32>(send(
								m_h, (const GAIA::GCH*)p, uSize, 0));
						#endif
						}
						else
						{
							NetworkAddress& na = *(NetworkAddress*)r.p;
							sockaddr_in sinaddr;
							GAIA::ALGORITHM::memset(&sinaddr, 0, sizeof(sinaddr));
							sinaddr.sin_family = AF_INET;
							sinaddr.sin_port = htons(na.uPort);
							sinaddr.sin_addr.s_addr =
								(na.ip.u0 << 0) |
								(na.ip.u1 << 8) |
								(na.ip.u2 << 16) |
								(na.ip.u3 << 24);
						#if GAIA_OS == GAIA_OS_LINUX || GAIA_OS == GAIA_OS_UNIX
							nSended = static_cast<GAIA::N32>(sendto(
								m_h, (const GAIA::GCH*)p, uSize, MSG_NOSIGNAL, 
								(sockaddr*)&sinaddr, sizeof(sinaddr)));
						#else
							nSended = static_cast<GAIA::N32>(sendto(
								m_h, (const GAIA::GCH*)p, uSize, 0, 
								(sockaddr*)&sinaddr, sizeof(sinaddr)));
						#endif
						}
						if(nSended == GINVALID)
						{
						#if GAIA_OS == GAIA_OS_WINDOWS
							GAIA::N32 nLastError = ::WSAGetLastError();
							if(nLastError == WSAEWOULDBLOCK){}
							else
							{

								if(this->IsStabilityLink())
								{
									this->Reference();
									{
										this->LostConnection(this->GetRemoteAddress(), GAIA::False);
										if(this->IsConnected())
											this->Disconnect();
									}
									this->Release();
								}
								else
								{
									NetworkAddress& na = *(NetworkAddress*)r.p;
									this->LostConnection(na, GAIA::False);
								}
								break;
							}
						#else
							if(errno == EAGAIN){}
							else
							{
								if(this->IsStabilityLink())
								{
									this->Reference();
									{
										this->LostConnection(this->GetRemoteAddress(), GAIA::False);
										if(this->IsConnected())
											this->Disconnect();
									}
									this->Release();
								}
								else
								{
									NetworkAddress& na = *(NetworkAddress*)r.p;
									this->LostConnection(na, GAIA::False);
								}
								break;
							}
						#endif
						}
						else if(nSended == 0)
						{
							if(this->IsStabilityLink())
							{
								this->Reference();
								{
									this->LostConnection(this->GetRemoteAddress(), GAIA::False);
									if(this->IsConnected())
										this->Disconnect();

								}
								this->Release();
							}
							else
							{
								NetworkAddress& na = *(NetworkAddress*)r.p;
								this->LostConnection(na, GAIA::False);
							}
							break;
						}
						else
						{
							p += nSended;
							uSize -= nSended;
						}
					}
					GAIA_MRELEASE(r.p);
				}
			}
			return GAIA::True;
		}
		GAIA_DEBUG_CODEPURE_FUNC GAIA::BL GetHostName(GAIA::GCH* pszResult, const GAIA::N32& size){return gethostname(pszResult, size) != GINVALID;}
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

			// Create socket.
			listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(listensock == GINVALID)
				return;
			if(setsockopt(listensock, SOL_SOCKET, SO_SNDBUF, (GAIA::GCH*)&m_desc.nListenSendBufSize, sizeof(m_desc.nListenSendBufSize)) != 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				closesocket(listensock);
			#else
				close(listensock);
			#endif
				return;
			}
			if(setsockopt(listensock, SOL_SOCKET, SO_RCVBUF, (GAIA::GCH*)&m_desc.nListenRecvBufSize, sizeof(m_desc.nListenRecvBufSize)) != 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				closesocket(listensock);
			#else
				close(listensock);
			#endif
				return;
			}

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
				// Stop command.
				if(m_bStopCmd)
					break;

				// Accept.
				sockaddr_in addrnew;
			#if GAIA_OS == GAIA_OS_WINDOWS
				GAIA::N32 newsize = sizeof(addrnew);
				GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &newsize);
			#else
				GAIA::U32 newsize = sizeof(addrnew);
				GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &newsize);
			#endif
				if(newsock != GINVALID)
				{
					// Setup socket.
					if(setsockopt(newsock, SOL_SOCKET, SO_SNDBUF, (GAIA::GCH*)&m_desc.nAcceptSendBufSize, sizeof(m_desc.nAcceptSendBufSize)) != 0)
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
						shutdown(newsock, SD_BOTH);
						closesocket(newsock);
					#else
						shutdown(newsock, SHUT_RDWR);
						close(newsock);
					#endif
						break;
					}
					if(setsockopt(newsock, SOL_SOCKET, SO_RCVBUF, (GAIA::GCH*)&m_desc.nAcceptRecvBufSize, sizeof(m_desc.nAcceptRecvBufSize)) != 0)
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
						shutdown(newsock, SD_BOTH);
						closesocket(newsock);
					#else
						shutdown(newsock, SHUT_RDWR);
						close(newsock);
					#endif
						break;
					}
				#if GAIA_OS == GAIA_OS_WINDOWS
				#	if defined(GAIA_DEBUG_CODEPURE) && !defined(GAIA_NOCANCEL_ORIGINTYPE)
				#		undef long
				#	endif
					GAIA::UM bNotBlockModeEnable = 1; ioctlsocket(newsock, FIONBIO, &bNotBlockModeEnable);
				#	if defined(GAIA_DEBUG_CODEPURE) && !defined(GAIA_NOCANCEL_ORIGINTYPE)
				#		define long GAIA_INVALID_ORIGINTYPE
				#	endif
				#else
					GAIA::N32 flags = fcntl(newsock, F_GETFL, 0);
					fcntl(newsock, F_SETFL, flags | O_NONBLOCK);
				#endif

					//
					NetworkHandle* h = GNULL;
					if(m_pAcceptCallBack != GNULL)
						h = m_pAcceptCallBack->CreateNetworkHandle();
					else
						h = new NetworkHandle;
					if(h != GNULL)
					{
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
			sockaddr_in recvfrom_addr;
			GAIA::ALGORITHM::memset(&recvfrom_addr, 0, sizeof(recvfrom_addr));
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
						#if GAIA_OS == GAIA_OS_WINDOWS
							GAIA::N32 recvfrom_addr_len;
						#else
							GAIA::U32 recvfrom_addr_len;
						#endif
							GAIA::N32 nRecv;
							if(pHandle->IsStabilityLink())
								nRecv = (GAIA::N32)recv(pHandle->m_h, (GAIA::N8*)m_buf.front_ptr(), (GAIA::N32)m_buf.write_size(), 0);
							else
							{
								recvfrom_addr_len = sizeof(recvfrom_addr);
								GAIA::ALGORITHM::memset(&recvfrom_addr, 0, recvfrom_addr_len);
								GAIA_AST(m_buf.write_size() > sizeof(NetworkAddress));
								nRecv = (GAIA::N32)recvfrom(
									pHandle->m_h, 
									(GAIA::N8*)m_buf.front_ptr() + sizeof(NetworkAddress), 
									(GAIA::N32)m_buf.write_size() - sizeof(NetworkAddress), 0, 
									(sockaddr*)&recvfrom_addr, 
									&recvfrom_addr_len);
							}
							if(nRecv == GINVALID)
							{
							#if GAIA_OS == GAIA_OS_WINDOWS
								GAIA::N32 nLastError = ::WSAGetLastError();
								if(nLastError == WSAEWOULDBLOCK)break;
								else
								{
									if(pHandle->IsStabilityLink())
									{
										pHandle->Reference();
										{
											if(this->Remove(*pHandle))
												bNeedRelease = GAIA::False;
											pHandle->LostConnection(pHandle->GetRemoteAddress(), GAIA::True);
											if(pHandle->IsConnected())
												pHandle->Disconnect();
										}
										pHandle->Release();
									}
									else
									{
										NetworkAddress na_recvfrom;
										na_recvfrom.ip.u0 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
										na_recvfrom.ip.u1 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
										na_recvfrom.ip.u2 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
										na_recvfrom.ip.u3 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
										na_recvfrom.uPort = ntohs(recvfrom_addr.sin_port);
										pHandle->LostConnection(na_recvfrom, GAIA::True);
									}
									break;
								}
							#else
								if(errno == EAGAIN)
									break;
								else
								{
									if(pHandle->IsStabilityLink())
									{
										pHandle->Reference();
										{
											if(this->Remove(*pHandle))
												bNeedRelease = GAIA::False;
											pHandle->LostConnection(pHandle->GetRemoteAddress(), GAIA::True);
											if(pHandle->IsConnected())
												pHandle->Disconnect();
										}
										pHandle->Release();
									}
									else
									{
										NetworkAddress na_recvfrom;
										na_recvfrom.ip.u0 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
										na_recvfrom.ip.u1 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
										na_recvfrom.ip.u2 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
										na_recvfrom.ip.u3 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
										na_recvfrom.uPort = ntohs(recvfrom_addr.sin_port);
										pHandle->LostConnection(na_recvfrom, GAIA::True);
									}
									break;
								}
							#endif
							}
							else if(nRecv == 0)
							{
								if(pHandle->IsStabilityLink())
								{
									pHandle->Reference();
									{
										if(this->Remove(*pHandle))
											bNeedRelease = GAIA::False;
										pHandle->LostConnection(pHandle->GetRemoteAddress(), GAIA::True);
										if(pHandle->IsConnected())
											pHandle->Disconnect();
									}
									pHandle->Release();
								}
								else
								{
									NetworkAddress na_recvfrom;
									na_recvfrom.ip.u0 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
									na_recvfrom.ip.u1 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
									na_recvfrom.ip.u2 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
									na_recvfrom.ip.u3 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
									na_recvfrom.uPort = ntohs(recvfrom_addr.sin_port);
									pHandle->LostConnection(na_recvfrom, GAIA::True);
								}
								break;
							}
							else
							{
								if(pHandle->IsStabilityLink())
									this->Receive(*pHandle, m_buf.front_ptr(), (GAIA::U32)nRecv);
								else
								{
									NetworkAddress na;
									na.ip.u0 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
									na.ip.u1 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
									na.ip.u2 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
									na.ip.u3 = (GAIA::U8)((GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
									na.uPort = ntohs(recvfrom_addr.sin_port);
									GAIA::ALGORITHM::memcpy(m_buf.front_ptr(), &na, sizeof(na));
									this->Receive(*pHandle, m_buf.front_ptr(), (GAIA::U32)(nRecv + sizeof(NetworkAddress)));
								}
								bExistWork = GAIA::True;
								if(nRecv < m_buf.write_size())
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
