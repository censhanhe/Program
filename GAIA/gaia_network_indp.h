#ifndef 	__GAIA_NETWORK_INDP_H__
#define 	__GAIA_NETWORK_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
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
		/* Handle's implement. */
		GINL GAIA::BL Handle::Connect(const ConnectDesc& desc)
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
			if(setsockopt(m_h, SOL_SOCKET, SO_SNDBUF, (GAIA::N8*)&m_nSendBufferSize, sizeof(m_nSendBufferSize)) != 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				closesocket(m_h);
			#else
				close(m_h);
			#endif
				m_h = GINVALID;
				return GAIA::False;
			}
			if(setsockopt(m_h, SOL_SOCKET, SO_RCVBUF, (GAIA::N8*)&m_nRecvBufferSize, sizeof(m_nRecvBufferSize)) != 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				closesocket(m_h);
			#else
				close(m_h);
			#endif
				m_h = GINVALID;
				return GAIA::False;
			}

			// Construct network address.
			sockaddr_in sinaddr;
			GAIA::ALGO::xmemset(&sinaddr, 0, sizeof(sinaddr));
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
			if(!desc.bSync)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				GAIA::UM bNotBlockModeEnable = 1; ioctlsocket(m_h, FIONBIO, &bNotBlockModeEnable);
			#else
				GAIA::N32 flags = fcntl(m_h, F_GETFL, 0);
				fcntl(m_h, F_SETFL, flags | O_NONBLOCK);
			#endif
			}

			//
			m_bConnected = GAIA::True;

			return GAIA::True;
		}
		GINL GAIA::BL Handle::Disconnect()
		{
			if(!this->IsConnected())
				return GAIA::False;

			m_bConnected = GAIA::False;

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
		GINL GAIA::GVOID Handle::SetSender(Sender* pSender)
		{
			GPCHR_TRUE(m_conndesc.bSync);
			if(pSender == m_pSender)
				return;
			if(m_pSender != GNIL)
				m_pSender->Remove(*this);
			if(pSender != GNIL)
				pSender->Add(*this);
			m_pSender = pSender;
		}
		GINL GAIA::GVOID Handle::SetReceiver(Receiver* pReceiver)
		{
			GPCHR_TRUE(m_conndesc.bSync);
			if(pReceiver == m_pReceiver)
				return;
			if(m_pReceiver != GNIL)
				m_pReceiver->Remove(*this);
			if(pReceiver != GNIL)
				pReceiver->Add(*this);
			m_pReceiver = pReceiver;
		}
		GINL BL Handle::Send(const GAIA::U8* p, GAIA::U32 uSize)
		{
			GAIA_AST(!!p);
			GAIA_AST(uSize > 0);
			if(p == GNIL || uSize == 0)
				return GAIA::False;
			if(!this->IsStabilityLink())
			{
				if(uSize <= sizeof(GAIA::NETWORK::Addr))
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
				if(uSize > MAX_NOSTABILITY_SENDSIZE + sizeof(GAIA::NETWORK::Addr))
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			GAIA::U8* pNew = GAIA_MALLOC(GAIA::U8, uSize);
			GAIA::ALGO::xmemcpy(pNew, p, uSize);
			GAIA::SYNC::AutoLock al(m_lock);
			SendRec r;
			r.p = pNew;
			r.uSize = uSize;
			m_sendque.push_back(r);
			if(m_conndesc.bSync)
				this->FlushSendQueue();
			return GAIA::True;
		}
		GINL BL Handle::Recv(GAIA::U8* p, GAIA::U32 uSize, GAIA::U32& uResultSize)
		{
			GPCHR_NULL_RET(p, GAIA::False);
			GPCHR_BELOWEQUALZERO_RET(uSize, GAIA::False);
			GPCHR_FALSE_RET(m_conndesc.bSync, GAIA::False);
			if(m_conndesc.bStabilityLink)
				uResultSize = (GAIA::U32)recv(m_h, (GAIA::N8*)p, (GAIA::N32)uSize, 0);
			else
			{
				GAIA_AST(uSize > (GAIA::SIZE)sizeof(GAIA::NETWORK::Addr));
				socklen_t recvfrom_addr_len;
				sockaddr_in recvfrom_addr;
				GAIA::ALGO::xmemset(&recvfrom_addr, 0, sizeof(recvfrom_addr));
				recvfrom_addr_len = sizeof(recvfrom_addr);
				uResultSize = (GAIA::U32)recvfrom(
					m_h,
					(GAIA::N8*)p + sizeof(GAIA::NETWORK::Addr),
					(GAIA::N32)uSize - sizeof(GAIA::NETWORK::Addr), 0,
					(sockaddr*)&recvfrom_addr,
					&recvfrom_addr_len);
				GAIA::NETWORK::Addr na;
				na.ip.u0 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
				na.ip.u1 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
				na.ip.u2 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
				na.ip.u3 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
				na.uPort = ntohs(recvfrom_addr.sin_port);
				GAIA::ALGO::xmemcpy(p, &na, sizeof(na));
			}
			if(uResultSize == (GAIA::U32)GINVALID)
				return GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::BL Handle::FlushSendQueue()
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
					m_sendque.pop_front();
				}
			}

			// Send temp send vector.
			{
				for(GAIA::N32 x = 0; x < m_tempsendlist.size(); ++x)
				{
					SendRec& r = m_tempsendlist[x];
					GAIA_AST(!!r.p);
					GAIA::U8* p = r.p;
					GAIA::U32 uSize = r.uSize;
					if(!this->IsStabilityLink())
					{
						p += sizeof(GAIA::NETWORK::Addr);
						uSize -= sizeof(GAIA::NETWORK::Addr);
					}
					while(uSize > 0)
					{
						GAIA::N32 nSended;
						if(this->IsStabilityLink())
						{
						#if GAIA_OS == GAIA_OS_LINUX || GAIA_OS == GAIA_OS_UNIX
							nSended = static_cast<GAIA::N32>(send(
								m_h, GRCAST(const GAIA::N8*)(p), uSize, MSG_NOSIGNAL));
						#else
							nSended = static_cast<GAIA::N32>(send(
								m_h, GRCAST(const GAIA::N8*)(p), uSize, 0));
						#endif
						}
						else
						{
							GAIA::NETWORK::Addr& na = *GRCAST(GAIA::NETWORK::Addr*)(r.p);
							sockaddr_in sinaddr;
							GAIA::ALGO::xmemset(&sinaddr, 0, sizeof(sinaddr));
							sinaddr.sin_family = AF_INET;
							sinaddr.sin_port = htons(na.uPort);
							sinaddr.sin_addr.s_addr =
								(na.ip.u0 << 0) |
								(na.ip.u1 << 8) |
								(na.ip.u2 << 16) |
								(na.ip.u3 << 24);
						#if GAIA_OS == GAIA_OS_LINUX || GAIA_OS == GAIA_OS_UNIX
							nSended = static_cast<GAIA::N32>(sendto(
								m_h, GRCAST(const GAIA::N8*)(p), uSize, MSG_NOSIGNAL,
								(sockaddr*)&sinaddr, sizeof(sinaddr)));
						#else
							nSended = static_cast<GAIA::N32>(sendto(
								m_h, GRCAST(const GAIA::N8*)(p), uSize, 0,
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
									GAIA::NETWORK::Addr& na = *GRCAST(GAIA::NETWORK::Addr*)(r.p);
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
									GAIA::NETWORK::Addr& na = *GRCAST(GAIA::NETWORK::Addr*)(r.p);
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
								GAIA::NETWORK::Addr& na = *GRCAST(GAIA::NETWORK::Addr*)(r.p);
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
					GAIA_MFREE(r.p);
				}
			}
			return GAIA::True;
		}
		GINL GAIA::BL GetHostName(GAIA::CH* pszResult, const GAIA::N32& size){return gethostname(pszResult, size) != GINVALID;}
		GINL GAIA::GVOID GetHostIPList(const GAIA::CH* pszHostName, GAIA::CTN::Vector<GAIA::NETWORK::IP>& listResult)
		{
			hostent* pHostEnt = gethostbyname(pszHostName);
			if(pHostEnt != GNIL)
			{
				GAIA::N32 nIndex = 0;
				while(pHostEnt->h_addr_list[nIndex] != GNIL)
				{
					if(pHostEnt->h_addrtype == AF_INET)
					{
						in_addr* addr = GRCAST(in_addr*)(pHostEnt->h_addr_list[nIndex]);
						GAIA::NETWORK::IP ip;
						ip.Invalid();
						ip.u0 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)((*(GAIA::U32*)addr) & 0x000000FF) >> 0);
						ip.u1 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)((*(GAIA::U32*)addr) & 0x0000FF00) >> 8);
						ip.u2 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)((*(GAIA::U32*)addr) & 0x00FF0000) >> 16);
						ip.u3 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)((*(GAIA::U32*)addr) & 0xFF000000) >> 24);
						listResult.push_back(ip);
						++nIndex;
					}
					else if(pHostEnt->h_addrtype == AF_INET6)
					{
					}
				}
			}
		}
		/* Listener's implement. */
		GINL GAIA::BL Listener::Begin()
		{
			if(this->IsBegin())
				return GAIA::False;
			m_bBegin = GAIA::True;
			this->Run();
			return GAIA::True;
		}
		GINL GAIA::BL Listener::End()
		{
			if(!this->IsBegin())
				return GAIA::False;
			m_bStopCmd = GAIA::True;
			{
				Handle::ConnectDesc descConn;
				descConn.addr = m_desc.addr;
				descConn.bStabilityLink = GAIA::True;
				Handle h;
				h.Connect(descConn);
				this->Wait();
			}
			m_bStopCmd = GAIA::False;
			m_bBegin = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID Listener::WorkProcedure()
		{
			GAIA::N32 listensock = GINVALID;

			// Create socket.
			listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(listensock == GINVALID)
				return;
			if(setsockopt(listensock, SOL_SOCKET, SO_SNDBUF, (GAIA::N8*)&m_desc.nListenSendBufSize, sizeof(m_desc.nListenSendBufSize)) != 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				closesocket(listensock);
			#else
				close(listensock);
			#endif
				listensock = GINVALID;
				return;
			}
			if(setsockopt(listensock, SOL_SOCKET, SO_RCVBUF, (GAIA::N8*)&m_desc.nListenRecvBufSize, sizeof(m_desc.nListenRecvBufSize)) != 0)
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
				closesocket(listensock);
			#else
				close(listensock);
			#endif
				listensock = GINVALID;
				return;
			}

			// Bind.
			sockaddr_in addr;
			GAIA::ALGO::xmemset(&addr, 0, sizeof(addr));
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
				listensock = GINVALID;
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
				listensock = GINVALID;
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
				socklen_t new_addr_len = sizeof(addrnew);
				GAIA::N32 newsock = accept(listensock, (sockaddr*)&addrnew, &new_addr_len);
				if(newsock != GINVALID)
				{
					// Setup socket.
					if(setsockopt(newsock, SOL_SOCKET, SO_SNDBUF, (GAIA::N8*)&m_desc.nAcceptSendBufSize, sizeof(m_desc.nAcceptSendBufSize)) != 0)
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
						shutdown(newsock, SD_BOTH);
						closesocket(newsock);
					#else
						shutdown(newsock, SHUT_RDWR);
						close(newsock);
					#endif
						newsock = GINVALID;
						break;
					}
					if(setsockopt(newsock, SOL_SOCKET, SO_RCVBUF, (GAIA::N8*)&m_desc.nAcceptRecvBufSize, sizeof(m_desc.nAcceptRecvBufSize)) != 0)
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
						shutdown(newsock, SD_BOTH);
						closesocket(newsock);
					#else
						shutdown(newsock, SHUT_RDWR);
						close(newsock);
					#endif
						newsock = GINVALID;
						break;
					}
					if(!m_desc.bSync)
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
						GAIA::UM bNotBlockModeEnable = 1; ioctlsocket(newsock, FIONBIO, &bNotBlockModeEnable);
					#else
						GAIA::N32 flags = fcntl(newsock, F_GETFL, 0);
						fcntl(newsock, F_SETFL, flags | O_NONBLOCK);
					#endif
					}

					//
					Handle* h = GNIL;
					if(m_pAcceptCallBack != GNIL)
						h = m_pAcceptCallBack->CreateNetworkHandle();
					else
						h = new Handle;
					if(h != GNIL)
					{
						h->m_h = newsock;
						h->m_addr_self = m_desc.addr;
						h->m_conndesc.addr.ip.u0 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(addrnew.sin_addr.s_addr & 0x000000FF) >> 0);
						h->m_conndesc.addr.ip.u1 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(addrnew.sin_addr.s_addr & 0x0000FF00) >> 8);
						h->m_conndesc.addr.ip.u2 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(addrnew.sin_addr.s_addr & 0x00FF0000) >> 16);
						h->m_conndesc.addr.ip.u3 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(addrnew.sin_addr.s_addr & 0xFF000000) >> 24);
						h->m_addr_self.uPort = ntohs(addrnew.sin_port);
						h->m_bConnected = GAIA::True;
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
		/* Sender's implement. */
		GINL GAIA::BL Sender::Begin()
		{
			if(this->IsBegin())
				return GAIA::False;
			m_bBegin = GAIA::True;
			this->Run();
			return GAIA::True;
		}
		GINL GAIA::BL Sender::End()
		{
			if(!this->IsBegin())
				return GAIA::False;
			m_bStopCmd = GAIA::True;
			this->Wait();
			m_bStopCmd = GAIA::False;
			m_bBegin = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID Sender::WorkProcedure()
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
					for(; !iter.empty(); ++iter)
					{
						Handle* pHandle = *iter;
						GAIA_AST(!!pHandle);
						if(pHandle->IsConnected())
						{
							pHandle->Reference();
							m_hl.push_back(pHandle);
						}
					}
				}

				// Flush all send buffer which in the handle list.
				{
					__HandleListType::it iter = m_hl.front_it();
					for(; !iter.empty(); ++iter)
					{
						Handle* pHandle = *iter;
						if(pHandle->FlushSendQueue())
							bExistWork = GAIA::True;
						pHandle->Release();
					}
				}

				//
				if(!bExistWork)
					GAIA::SYNC::xsleep(1);
			}
		}
		/* Receiver's implement. */
		GINL GAIA::BL Receiver::Begin()
		{
			if(this->IsBegin())
				return GAIA::False;
			m_bBegin = GAIA::True;
			this->Run();
			return GAIA::True;
		}
		GINL GAIA::BL Receiver::End()
		{
			if(!this->IsBegin())
				return GAIA::False;
			m_bStopCmd = GAIA::True;
			this->Wait();
			m_bStopCmd = GAIA::False;
			m_bBegin = GAIA::False;
			return GAIA::True;
		}
		GINL GAIA::GVOID Receiver::WorkProcedure()
		{
			sockaddr_in recvfrom_addr;
			GAIA::ALGO::xmemset(&recvfrom_addr, 0, sizeof(recvfrom_addr));
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
					for(; !iter.empty(); ++iter)
					{
						Handle* pHandle = *iter;
						GAIA_AST(!!pHandle);
						if(pHandle->IsConnected())
						{
							pHandle->Reference();
							m_hl.push_back(pHandle);
						}
					}
				}

				// Receive all socket which in the handle list.
				{
					__HandleListType::it iter = m_hl.front_it();
					for(; !iter.empty(); ++iter)
					{
						Handle* pHandle = *iter;
						GAIA::BL bNeedRelease = GAIA::True;
						for(;;)
						{

							GAIA::N32 nRecv;
							if(pHandle->IsStabilityLink())
								nRecv = (GAIA::N32)recv(pHandle->m_h, (GAIA::N8*)m_buf.front_ptr(), (GAIA::N32)m_buf.write_size(), 0);
							else
							{
								socklen_t recvfrom_addr_len;
								recvfrom_addr_len = sizeof(recvfrom_addr);
								GAIA::ALGO::xmemset(&recvfrom_addr, 0, recvfrom_addr_len);
								GAIA_AST(m_buf.write_size() > (GAIA::SIZE)sizeof(GAIA::NETWORK::Addr));
								nRecv = (GAIA::N32)recvfrom(
									pHandle->m_h,
									(GAIA::N8*)m_buf.front_ptr() + sizeof(GAIA::NETWORK::Addr),
									(GAIA::N32)m_buf.write_size() - sizeof(GAIA::NETWORK::Addr), 0,
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
										GAIA::NETWORK::Addr na_recvfrom;
										na_recvfrom.ip.u0 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
										na_recvfrom.ip.u1 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
										na_recvfrom.ip.u2 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
										na_recvfrom.ip.u3 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
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
										GAIA::NETWORK::Addr na_recvfrom;
										na_recvfrom.ip.u0 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
										na_recvfrom.ip.u1 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
										na_recvfrom.ip.u2 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
										na_recvfrom.ip.u3 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
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
									GAIA::NETWORK::Addr na_recvfrom;
									na_recvfrom.ip.u0 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
									na_recvfrom.ip.u1 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
									na_recvfrom.ip.u2 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
									na_recvfrom.ip.u3 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
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
									GAIA::NETWORK::Addr na;
									na.ip.u0 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x000000FF) >> 0);
									na.ip.u1 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x0000FF00) >> 8);
									na.ip.u2 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0x00FF0000) >> 16);
									na.ip.u3 = GSCAST(GAIA::U8)(GSCAST(GAIA::U32)(recvfrom_addr.sin_addr.s_addr & 0xFF000000) >> 24);
									na.uPort = ntohs(recvfrom_addr.sin_port);
									GAIA::ALGO::xmemcpy(m_buf.front_ptr(), &na, sizeof(na));
									this->Receive(*pHandle, m_buf.front_ptr(), GSCAST(GAIA::U32)(nRecv + sizeof(GAIA::NETWORK::Addr)));
								}
								bExistWork = GAIA::True;
								if(nRecv < m_buf.write_size())
									break;
							}
						}
						if(bNeedRelease)
							pHandle->Release();
					}
				}

				//
				if(!bExistWork)
					GAIA::SYNC::xsleep(1);
			}
		}
	};
};

#endif
