#ifndef		__GAIA_NETWORK_H__
#define		__GAIA_NETWORK_H__

namespace GAIA
{
	namespace NETWORK
	{
		class IP
		{
		public:
			GINL IP(){}
			GINL IP(const IP& src){this->operator = (src);}
			GINL IP(const GAIA::GCH* psz){this->operator = (psz);}
			GINL ~IP(){}
			GINL GAIA::GVOID Invalid(){GAIA::ALGORITHM::set(u, 0, 6);}
			GINL GAIA::BL IsInvalid() const{return GAIA::ALGORITHM::cmp(u, 0, 6) == 0;}
			GINL GAIA::GVOID FromString(const GAIA::GCH* psz)
			{
				const GAIA::GCH* p = psz;
				GAIA::UM uDotCnt = GAIA::ALGORITHM::strcnt(psz, '.');
				if(uDotCnt == 3)
				{
					for(GAIA::N32 x = 0; x < 3; ++x)
					{
						p = GAIA::ALGORITHM::str2int(p, u[x]);
						++p;
					}
					GAIA::ALGORITHM::str2int(p, u[3]);
					u[4] = 0;
					u[5] = 0;
				}
				else if(uDotCnt == 5)
				{
					for(GAIA::N32 x = 0; x < 5; ++x)
					{
						p = GAIA::ALGORITHM::str2int(p, u[x]);
						++p;
					}
					GAIA::ALGORITHM::str2int(p, u[5]);
				}
			}
			GINL GAIA::GVOID ToString(GAIA::GCH* psz) const
			{
				GAIA::GCH* p = psz;
				GAIA::N32 nPart = (u4 == 0 && u5 == 0) ? 4 : 6;
				for(GAIA::N32 x = 0; x < nPart; ++x)
				{
					p = GAIA::ALGORITHM::int2str(u[x], p);
					*(p - 1) = '.';
				}
				*(p - 1) = 0;
			}
			GINL IP& operator = (const IP& src){uIPv4 = src.uIPv4; uIPv6 = src.uIPv6; return *this;}
			GINL IP& operator = (const GAIA::GCH* psz){this->FromString(psz); return *this;}
			GINL GAIA::BL operator == (const IP& src) const{return uIPv4 == src.uIPv4 && uIPv6 == src.uIPv6;}
			GINL GAIA::BL operator != (const IP& src) const{return !(this->operator == (src));}
			GINL GAIA::BL operator >= (const IP& src) const
			{
				if(uIPv4 < src.uIPv4)
					return GAIA::False;
				else if(uIPv4 > src.uIPv4)
					return GAIA::True;
				else
				{
					if(uIPv6 < src.uIPv6)
						return GAIA::False;
					else
						return GAIA::True;
				}
			}
			GINL GAIA::BL operator <= (const IP& src) const
			{
				if(uIPv4 > src.uIPv4)
					return GAIA::False;
				else if(uIPv4 < src.uIPv4)
					return GAIA::True;
				else
				{
					if(uIPv6 > src.uIPv6)
						return GAIA::False;
					else
						return GAIA::True;
				}
			}
			GINL GAIA::BL operator > (const IP& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const IP& src) const{return !(this->operator >= (src));}
		public:
			union
			{
				GAIA::U8 u[6];
				struct{GAIA::U8 u0, u1, u2, u3, u4, u5;};
				struct{GAIA::U8 uIPv4_0, uIPv4_1, uIPv4_2, uIPv4_3, uIPv6_0, uIPv6_1;};
				struct{GAIA::U32 uIPv4; GAIA::U16 uIPv6;};
			};
		};
		class NetworkAddress
		{
		public:
			GINL NetworkAddress(){}
			GINL NetworkAddress(const NetworkAddress& src){this->operator = (src);}
			GINL NetworkAddress(const IP& ip, GAIA::U16 uPort){this->ip = ip; this->uPort = uPort;}
			GINL ~NetworkAddress(){}
			GINL GAIA::GVOID Invalid(){ip.Invalid(); uPort = 0;}
			GINL GAIA::BL IsInvalid() const{return ip.IsInvalid() || uPort == 0;}
			GINL GAIA::GVOID FromString(const GAIA::GCH* psz)
			{
				ip.FromString(psz);
				const GAIA::GCH* p = GAIA::ALGORITHM::strch(psz, ':');
				++p;
				GAIA::ALGORITHM::str2int(p, uPort);
			}
			GINL GAIA::GVOID ToString(GAIA::GCH* psz) const
			{
				ip.ToString(psz);
				GAIA::GCH* p = GAIA::ALGORITHM::strend(psz);
				*p = ':';
				++p;
				p = GAIA::ALGORITHM::int2str(uPort, p);
				*(p - 1) = 0;
			}
			GINL NetworkAddress& operator = (const NetworkAddress& src){ip = src.ip; uPort = src.uPort; return *this;}
			GINL GAIA::BL operator == (const NetworkAddress& src) const{return ip == src.ip && uPort == src.uPort;}
			GINL GAIA::BL operator != (const NetworkAddress& src) const{return !(this->operator == (src));}
			GINL GAIA::BL operator >= (const NetworkAddress& src) const
			{
				if(ip < src.ip)
					return GAIA::False;
				else if(ip > src.ip)
					return GAIA::True;
				else
				{
					if(uPort < src.uPort)
						return GAIA::False;
					else
						return GAIA::True;
				}
			}
			GINL GAIA::BL operator <= (const NetworkAddress& src) const
			{
				if(ip > src.ip)
					return GAIA::False;
				else if(ip < src.ip)
					return GAIA::True;
				else
				{
					if(uPort > src.uPort)
						return GAIA::False;
					else
						return GAIA::True;
				}
			}
			GINL GAIA::BL operator > (const NetworkAddress& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const NetworkAddress& src) const{return !(this->operator >= (src));}
		public:
			IP ip;
			GAIA::U16 uPort;
		};
		class NetworkSender;
		class NetworkReceiver;
		class NetworkHandle : public RefObject
		{
		private:
			friend class NetworkListener;
			friend class NetworkSender;
			friend class NetworkReceiver;
		private:
			class SendRec
			{
			public:
				GAIA::U8* p;
				GAIA::UM uSize;
			};
		private:
			typedef GAIA::CONTAINER::Queue<SendRec> __SendQueueType;
			typedef GAIA::CONTAINER::Vector<SendRec> __SendListType;
		public:
			class ConnectDesc
			{
			public:
				GINL GAIA::GVOID Reset()
				{
					addr.Invalid();
					bStabilityLink = GAIA::True;
				}
				NetworkAddress addr;
				GAIA::U8 bStabilityLink : 1;
			};
		public:
			GAIA_DEBUG_CODEPURE_MEMFUNC NetworkHandle(){this->init();}
			GAIA_DEBUG_CODEPURE_MEMFUNC ~NetworkHandle(){if(this->IsConnected()) this->Disconnect(); this->init();}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Connect(const ConnectDesc& desc);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Disconnect();
			GINL GAIA::BL IsConnected() const{return m_h != GINVALID;}
			GINL GAIA::GVOID SetSelfAddress(const NetworkAddress& addr){m_addr_self = addr;}
			GINL const NetworkAddress& GetSelfNetAddress() const{return m_addr_self;}
			GINL const NetworkAddress& GetRemoteAddress() const{return m_conndesc.addr;}
			GINL GAIA::BL IsStabilityLink() const{return m_conndesc.bStabilityLink;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID SetSender(NetworkSender* pSender);
			GINL NetworkSender* GetSender() const{return m_pSender;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID SetReceiver(NetworkReceiver* pReceiver);
			GINL NetworkReceiver* GetReceiver() const{return m_pReceiver;}
			GAIA_DEBUG_CODEPURE_MEMFUNC BL Send(const GAIA::U8* p, GAIA::UM uSize);
			template<typename _DataType> GINL GAIA::BL Send(const _DataType& t){return this->Send(&t, sizeof(t));}
			template<typename _DataType> GINL GAIA::BL operator << (const _DataType& t){return this->Send(t);}
			GINL GAIA::BL operator == (const NetworkHandle& src) const{return m_h == src.m_h;}
			GINL GAIA::BL operator != (const NetworkHandle& src) const{return !(this->operator == (src));}
			GINL GAIA::BL operator >= (const NetworkHandle& src) const{return m_h <= src.m_h;}
			GINL GAIA::BL operator <= (const NetworkHandle& src) const{return m_h >= src.m_h;}
			GINL GAIA::BL operator > (const NetworkHandle& src) const{return !(this->operator <= (src));}
			GINL GAIA::BL operator < (const NetworkHandle& src) const{return !(this->operator >= (src));}
		private:
			GINL GAIA::GVOID init()
			{
				m_h = GINVALID;
				m_addr_self.Invalid();
				m_conndesc.Reset();
				m_pSender = GNULL;
				m_pReceiver = GNULL;
				m_nSendBufferSize = 1024 * 128;
				m_nRecvBufferSize = 1024 * 128;
				while(!m_sendque.empty())
				{
					SendRec sr = m_sendque.front();
					delete[] sr.p;
					m_sendque.pop();
				}
			}
			GINL virtual GAIA::GVOID Disconnect(GAIA::BL bRecvTrueSendFalse){}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL FlushSendQueue();
		private:
			GAIA::N32 m_h;
			NetworkAddress m_addr_self;
			ConnectDesc m_conndesc;
			NetworkSender* m_pSender;
			NetworkReceiver* m_pReceiver;
			GAIA::SYNC::Lock m_lock;
			__SendQueueType m_sendque;
			__SendListType m_tempsendlist;
			GAIA::N32 m_nSendBufferSize;
			GAIA::N32 m_nRecvBufferSize;
		};
		class NetworkListener : public GAIA::THREAD::Thread
		{
		public:
			class ListenDesc
			{
			public:
				GINL GAIA::GVOID Reset(){addr.Invalid();}
				NetworkAddress addr;
			};
		public:
			GINL NetworkListener(){this->init();}
			GINL ~NetworkListener(){if(this->IsBegin()) this->End();}
			GINL GAIA::GVOID SetDesc(const ListenDesc& desc){m_desc = desc;}
			GINL const ListenDesc& GetDesc() const{return m_desc;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Begin();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL End();
			GINL GAIA::BL IsBegin() const{return m_bBegin;}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Accept(NetworkHandle& h){return GAIA::False;}
			GINL virtual GAIA::GVOID WorkProcedure();
		private:
			GINL GAIA::GVOID init()
			{
				m_desc.Reset();
				m_bBegin = GAIA::False;
				m_bStopCmd = GAIA::False;
				m_nSendBufferSize = 1024 * 128;
				m_nRecvBufferSize = 1024 * 128;
			}
		private:
			ListenDesc m_desc;
			GAIA::U8 m_bBegin : 1;
			GAIA::U8 m_bStopCmd : 1;
			GAIA::N32 m_nSendBufferSize;
			GAIA::N32 m_nRecvBufferSize;
		};
		class NetworkSender : public GAIA::THREAD::Thread
		{
		private:
			friend class NetworkHandle;
		private:
			typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<NetworkHandle>> __HandleSetType;
			typedef GAIA::CONTAINER::Vector<NetworkHandle*> __HandleListType;
		public:
			GINL NetworkSender(){this->init();}
			GINL ~NetworkSender(){if(this->IsBegin()) this->End(); this->RemoveAll();}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Begin();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL End();
			GINL GAIA::BL IsBegin() const{return m_bBegin;}
		private:
			GINL GAIA::BL Add(NetworkHandle& h)
			{
				__HandleSetType::_datatype finder = &h;
				GAIA::SYNC::AutoLock al(m_lock);
				if(m_hs.find(finder) != GNULL)
					return GAIA::False;
				h.Reference();
				m_hs.insert(&h);
				return GAIA::True;
			}
			GINL GAIA::BL Remove(NetworkHandle& h)
			{
				__HandleSetType::_datatype finder = &h;
				GAIA::SYNC::AutoLock al(m_lock);
				if(!m_hs.erase(finder))
					return GAIA::False;
				h.Release();
				return GAIA::True;
			}
			GINL GAIA::GVOID RemoveAll()
			{
				GAIA::SYNC::AutoLock al(m_lock);
				__HandleSetType::it iter = m_hs.front_it();
				while(!iter.empty())
				{
					NetworkHandle* pHandle = *iter;
					GAIA_AST(pHandle != GNULL);
					pHandle->Release();
					++iter;
				}
				m_hs.destroy();
			}
		protected:
			GINL virtual GAIA::GVOID WorkProcedure();
		private:
			GINL GAIA::GVOID init(){m_bBegin = GAIA::False; m_bStopCmd = GAIA::False;}
		private:
			__HandleSetType m_hs;
			GAIA::SYNC::Lock m_lock;
			GAIA::U8 m_bBegin : 1;
			GAIA::U8 m_bStopCmd : 1;
			__HandleListType m_hl;
		};
		class NetworkReceiver : public GAIA::THREAD::Thread
		{
		private:
			friend class NetworkHandle;
		private:
			typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<NetworkHandle>> __HandleSetType;
			typedef GAIA::CONTAINER::Vector<NetworkHandle*> __HandleListType;
			typedef GAIA::CONTAINER::Buffer __BufferType;
		public:
			GINL NetworkReceiver(){this->init();}
			GINL ~NetworkReceiver(){if(this->IsBegin()) this->End(); this->RemoveAll();}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Begin();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL End();
			GINL GAIA::BL IsBegin() const{return m_bBegin;}
		private:
			GINL GAIA::BL Add(NetworkHandle& h)
			{
				__HandleSetType::_datatype finder = &h;
				GAIA::SYNC::AutoLock al(m_lock);
				if(m_hs.find(finder) != GNULL)
					return GAIA::False;
				h.Reference();
				m_hs.insert(&h);
				return GAIA::True;
			}
			GINL GAIA::BL Remove(NetworkHandle& h)
			{
				__HandleSetType::_datatype finder = &h;
				GAIA::SYNC::AutoLock al(m_lock);
				if(!m_hs.erase(finder))
					return GAIA::False;
				h.Release();
				return GAIA::True;
			}
			GINL GAIA::GVOID RemoveAll()
			{
				GAIA::SYNC::AutoLock al(m_lock);
				__HandleSetType::it iter = m_hs.front_it();
				while(!iter.empty())
				{
					NetworkHandle* pHandle = *iter;
					GAIA_AST(pHandle != GNULL);
					pHandle->Release();
					++iter;
				}
				m_hs.destroy();
			}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const NetworkHandle& s, const GAIA::U8* p, GAIA::U32 size){return GAIA::False;}
			GINL virtual GAIA::GVOID WorkProcedure();
		private:
			GINL GAIA::GVOID init(){m_bBegin = GAIA::False; m_bStopCmd = GAIA::False; m_buf.resize(4096);}
		private:
			__HandleSetType m_hs;
			GAIA::SYNC::Lock m_lock;
			GAIA::U8 m_bBegin : 1;
			GAIA::U8 m_bStopCmd : 1;
			__HandleListType m_hl;
			__BufferType m_buf;
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_network_indp.h"
#endif

#endif
