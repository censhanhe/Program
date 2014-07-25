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
			template<typename _ParamDataType> GINL IP(const _ParamDataType* psz){this->operator = (psz);}
			GINL ~IP(){}
			GINL GAIA::GVOID Invalid(){GAIA::ALGORITHM::set(us, 0, 4);}
			GINL GAIA::BL IsInvalid() const{return GAIA::ALGORITHM::cmpk(us, 0, 4) == 0;}
			template<typename _ParamDataType> GINL GAIA::BL FromString(const _ParamDataType* psz)
			{
				const _ParamDataType* p = psz;
				GAIA::U32 uDotCnt = GAIA::ALGORITHM::strcnt(psz, '.');
				if(uDotCnt == 3)
				{
					for(GAIA::N32 x = 0; x < 3; ++x)
					{
						p = GAIA::ALGORITHM::str2int(p, us[3 - x]);
						++p;
					}
					GAIA::ALGORITHM::str2int(p, us[0]);
					return GAIA::True;
				}
				return GAIA::False;
			}
			template<typename _ParamDataType> GINL GAIA::GVOID ToString(_ParamDataType* psz) const
			{
				_ParamDataType* p = psz;
				for(GAIA::N32 x = 0; x < 4; ++x)
				{
					p = GAIA::ALGORITHM::int2str((GAIA::N32)us[3 - x], p);
					*(p - 1) = '.';
				}
				*(p - 1) = 0;
			}
			GINL IP& operator = (const IP& src){GAIA_AST(&src != this); u = src.u; return *this;}
			template<typename _ParamDataType> GINL IP& operator = (const _ParamDataType* psz){this->FromString(psz); return *this;}
			GINL IP operator + (const IP& src) const{IP ret; ret.u = u + src.u; return ret;}
			GINL IP operator - (const IP& src) const{IP ret; ret.u = u - src.u; return ret;}
			template<typename _ParamDataType> GINL IP operator + (const _ParamDataType& t) const{IP ret; ret.u = u + t; return ret;}
			template<typename _ParamDataType> GINL IP operator - (const _ParamDataType& t) const{IP ret; ret.u = u - t; return ret;}
			GINL IP& operator += (const IP& src){u += src.u; return *this;}
			GINL IP& operator -= (const IP& src){u -= src.u; return *this;}
			template<typename _ParamDataType> GINL IP& operator += (const _ParamDataType& t){u += t; return *this;}
			template<typename _ParamDataType> GINL IP& operator -= (const _ParamDataType& t){u -= t; return *this;}
			GINL IP& operator ++ (){(*this) += 1; return *this;}
			GINL IP& operator -- (){(*this) -= 1; return *this;}
			GINL IP operator ++ (GAIA::N32){IP ret = *this; ++(*this); return ret;}
			GINL IP operator -- (GAIA::N32){IP ret = *this; --(*this); return ret;}
			GAIA_CLASS_OPERATOR_COMPARE(u, u, IP);
		public:
			union
			{
				GAIA::U32 u;
				GAIA::U8 us[4];
				class{public:GAIA::U8 u3, u2, u1, u0;};
				GAIA::U32 uIPv4;
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
			template<typename _ParamDataType> GINL GAIA::BL FromString(const _ParamDataType* psz)
			{
				if(!ip.FromString(psz))
					return GAIA::False;
				const _ParamDataType* p = GAIA::ALGORITHM::strch(psz, ':');
				if(p == GNULL)
					return GAIA::False;
				++p;
				GAIA::ALGORITHM::str2int(p, uPort);
				return GAIA::True;
			}
			template<typename _ParamDataType> GINL GAIA::GVOID ToString(_ParamDataType* psz) const
			{
				ip.ToString(psz);
				GAIA::TCH* p = GAIA::ALGORITHM::strend(psz);
				*p = ':';
				++p;
				p = GAIA::ALGORITHM::int2str((GAIA::N32)uPort, p);
				*(p - 1) = 0;
			}
			GINL NetworkAddress& operator = (const NetworkAddress& src){GAIA_AST(&src != this); ip = src.ip; uPort = src.uPort; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE2(ip, ip, uPort, uPort, NetworkAddress);
		public:
			IP ip;
			GAIA::U16 uPort;
		};
		GAIA_DEBUG_CODEPURE_FUNC GAIA::BL GetHostName(GAIA::CH* pszResult, const GAIA::N32& size);
		GAIA_DEBUG_CODEPURE_FUNC GAIA::GVOID GetHostIPList(const GAIA::CH* pszHostName, GAIA::CONTAINER::Vector<IP>& listResult);
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
				GAIA::U32 uSize;
			};
		private:
			typedef GAIA::CONTAINER::Queue<SendRec> __SendQueueType;
			typedef GAIA::CONTAINER::Vector<SendRec> __SendListType;
		public:
			static const GAIA::U32 MAX_NOSTABILITY_SENDSIZE = 840;
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
			GINL GAIA::BL SetSendBufSize(GAIA::N32 nSize){if(this->IsConnected()) return GAIA::False; m_nSendBufferSize = nSize; return GAIA::True;}
			GINL GAIA::N32 GetSendBufSize() const{return m_nSendBufferSize;}
			GINL GAIA::BL SetRecvBufSize(GAIA::N32 nSize){if(this->IsConnected()) return GAIA::False; m_nRecvBufferSize = nSize; return GAIA::True;}
			GINL GAIA::N32 GetRecvBufSize() const{return m_nRecvBufferSize;}
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
			GAIA_DEBUG_CODEPURE_MEMFUNC BL Send(const GAIA::U8* p, GAIA::U32 uSize);
			GAIA_CLASS_OPERATOR_COMPARE(m_h, m_h, NetworkHandle);
		private:
			GINL GAIA::GVOID init()
			{
				m_h = GINVALID;
				m_addr_self.Invalid();
				m_conndesc.Reset();
				m_pSender = GNULL;
				m_pReceiver = GNULL;
				m_nSendBufferSize = 1024;
				m_nRecvBufferSize = 1024;
				while(!m_sendque.empty())
				{
					SendRec& r = m_sendque.front();
					GAIA_MFREE(r.p);
					m_sendque.pop_front();
				}
			}
			GINL virtual GAIA::GVOID LostConnection(const GAIA::NETWORK::NetworkAddress& na, GAIA::BL bRecvTrueSendFalse){}
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
				GINL GAIA::GVOID Reset()
				{
					addr.Invalid();
					nListenSendBufSize = 1024;
					nListenRecvBufSize = 1024;
					nAcceptSendBufSize = 1024;
					nAcceptRecvBufSize = 1024;
				}
				NetworkAddress addr;
				GAIA::N32 nListenSendBufSize;
				GAIA::N32 nListenRecvBufSize;
				GAIA::N32 nAcceptSendBufSize;
				GAIA::N32 nAcceptRecvBufSize;
			};
			class AcceptCallBack
			{
			public:
				virtual NetworkHandle* CreateNetworkHandle() = 0;
			};
		public:
			GINL NetworkListener(){this->init();}
			GINL ~NetworkListener(){if(this->IsBegin()) this->End();}
			GINL GAIA::GVOID SetDesc(const ListenDesc& desc){m_desc = desc;}
			GINL const ListenDesc& GetDesc() const{return m_desc;}
			GINL GAIA::GVOID SetAcceptCallBack(AcceptCallBack* pAcceptCallBack){m_pAcceptCallBack = pAcceptCallBack;}
			GINL AcceptCallBack* GetAcceptCallBack() const{return m_pAcceptCallBack;}
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
				m_pAcceptCallBack = GNULL;
			}
		private:
			ListenDesc m_desc;
			GAIA::U8 m_bBegin : 1;
			GAIA::U8 m_bStopCmd : 1;
			AcceptCallBack* m_pAcceptCallBack;
		};
		class NetworkSender : public GAIA::THREAD::Thread
		{
		private:
			friend class NetworkHandle;
		private:
			typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<NetworkHandle> > __HandleSetType;
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
					GAIA_AST(!!pHandle);
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
			typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<NetworkHandle> > __HandleSetType;
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
					GAIA_AST(!!pHandle);
					pHandle->Release();
					++iter;
				}
				m_hs.destroy();
			}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(NetworkHandle& s, const GAIA::U8* p, GAIA::U32 size){return GAIA::False;}
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
