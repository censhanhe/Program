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
			template<typename _ParamDataType> IP(const _ParamDataType* psz){this->operator = (psz);}
			GINL ~IP(){}
			GINL GAIA::GVOID Invalid(){GAIA::ALGO::set(us, 0, 4);}
			GINL GAIA::BL IsInvalid() const{return GAIA::ALGO::cmpk(us, 0, 4) == 0;}
			template<typename _ParamDataType> GAIA::BL FromString(const _ParamDataType* psz)
			{
				const _ParamDataType* p = psz;
				GAIA::U32 uDotCnt = GAIA::ALGO::strcnt(psz, '.');
				if(uDotCnt == 3)
				{
					for(GAIA::N32 x = 0; x < 3; ++x)
					{
						p = GAIA::ALGO::str2int(p, us[3 - x]);
						++p;
					}
					GAIA::ALGO::str2int(p, us[0]);
					return GAIA::True;
				}
				return GAIA::False;
			}
			template<typename _ParamDataType> GAIA::GVOID ToString(_ParamDataType* psz) const
			{
				_ParamDataType* p = psz;
				for(GAIA::N32 x = 0; x < 4; ++x)
				{
					p = GAIA::ALGO::int2str((GAIA::N32)us[3 - x], p);
					*(p - 1) = '.';
				}
				*(p - 1) = 0;
			}
			GINL IP& operator = (const IP& src){GAIA_AST(&src != this); u = src.u; return *this;}
			template<typename _ParamDataType> IP& operator = (const _ParamDataType* psz){this->FromString(psz); return *this;}
			GINL IP operator + (const IP& src) const{IP ret; ret.u = u + src.u; return ret;}
			GINL IP operator - (const IP& src) const{IP ret; ret.u = u - src.u; return ret;}
			template<typename _ParamDataType> IP operator + (const _ParamDataType& t) const{IP ret; ret.u = u + t; return ret;}
			template<typename _ParamDataType> IP operator - (const _ParamDataType& t) const{IP ret; ret.u = u - t; return ret;}
			GINL IP& operator += (const IP& src){u += src.u; return *this;}
			GINL IP& operator -= (const IP& src){u -= src.u; return *this;}
			template<typename _ParamDataType> IP& operator += (const _ParamDataType& t){u += t; return *this;}
			template<typename _ParamDataType> IP& operator -= (const _ParamDataType& t){u -= t; return *this;}
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
		class Addr
		{
		public:
			GINL Addr(){}
			GINL Addr(const Addr& src){this->operator = (src);}
			GINL Addr(const GAIA::NETWORK::IP& ip, GAIA::U16 uPort){this->ip = ip; this->uPort = uPort;}
			GINL ~Addr(){}
			GINL GAIA::GVOID Invalid(){ip.Invalid(); uPort = 0;}
			GINL GAIA::BL IsInvalid() const{return ip.IsInvalid() || uPort == 0;}
			template<typename _ParamDataType> GAIA::BL FromString(const _ParamDataType* psz)
			{
				if(!ip.FromString(psz))
					return GAIA::False;
				const _ParamDataType* p = GAIA::ALGO::strch(psz, ':');
				if(p == GNIL)
					return GAIA::False;
				++p;
				GAIA::ALGO::str2int(p, uPort);
				return GAIA::True;
			}
			template<typename _ParamDataType> GAIA::GVOID ToString(_ParamDataType* psz) const
			{
				ip.ToString(psz);
				GAIA::TCH* p = GAIA::ALGO::strend(psz);
				*p = ':';
				++p;
				p = GAIA::ALGO::int2str((GAIA::N32)uPort, p);
				*(p - 1) = 0;
			}
			GINL Addr& operator = (const Addr& src){GAIA_AST(&src != this); ip = src.ip; uPort = src.uPort; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE2(ip, ip, uPort, uPort, Addr);
		public:
			GAIA::NETWORK::IP ip;
			GAIA::U16 uPort;
		};
		GINL GAIA::BL GetHostName(GAIA::CH* pszResult, const GAIA::N32& size);
		GINL GAIA::GVOID GetHostIPList(const GAIA::CH* pszHostName, GAIA::CTN::Vector<GAIA::NETWORK::IP>& listResult);
		class Handle : public GAIA::RefObject
		{
		private:
			friend class Listener;
			friend class Sender;
			friend class Receiver;
		private:
			class SendRec
			{
			public:
				GAIA::U8* p;
				GAIA::U32 uSize;
			};
		private:
			typedef GAIA::CTN::Queue<SendRec> __SendQueueType;
			typedef GAIA::CTN::Vector<SendRec> __SendListType;
		public:
			static const GAIA::U32 MAX_NOSTABILITY_SENDSIZE = 840;
			class ConnectDesc : public GAIA::Base
			{
			public:
				GINL GAIA::GVOID reset()
				{
					addr.Invalid();
					bStabilityLink = GAIA::True;
					bSync = GAIA::False;
				}
				GAIA::NETWORK::Addr addr;
				GAIA::U8 bStabilityLink : 1;
				GAIA::U8 bSync : 1;
			};
		public:
			GINL Handle(){this->init();}
			GINL ~Handle(){if(this->IsConnected()) this->Disconnect(); this->init();}
			GINL GAIA::BL SetSendBufSize(GAIA::N32 nSize){if(this->IsConnected()) return GAIA::False; m_nSendBufferSize = nSize; return GAIA::True;}
			GINL GAIA::N32 GetSendBufSize() const{return m_nSendBufferSize;}
			GINL GAIA::BL SetRecvBufSize(GAIA::N32 nSize){if(this->IsConnected()) return GAIA::False; m_nRecvBufferSize = nSize; return GAIA::True;}
			GINL GAIA::N32 GetRecvBufSize() const{return m_nRecvBufferSize;}
			GINL GAIA::BL Connect(const ConnectDesc& desc);
			GINL GAIA::BL Disconnect();
			GINL GAIA::BL IsConnected() const{return m_bConnected;}
			GINL GAIA::GVOID SetSelfAddress(const GAIA::NETWORK::Addr& addr){m_addr_self = addr;}
			GINL const GAIA::NETWORK::Addr& GetSelfNetAddress() const{return m_addr_self;}
			GINL const GAIA::NETWORK::Addr& GetRemoteAddress() const{return m_conndesc.addr;}
			GINL GAIA::BL IsStabilityLink() const{return m_conndesc.bStabilityLink;}
			GINL GAIA::GVOID SetSender(Sender* pSender);
			GINL Sender* GetSender() const{return m_pSender;}
			GINL GAIA::GVOID SetReceiver(Receiver* pReceiver);
			GINL Receiver* GetReceiver() const{return m_pReceiver;}
			GINL BL Send(const GAIA::U8* p, GAIA::U32 uSize);
			GINL BL Recv(GAIA::U8* p, GAIA::U32 uSize, GAIA::U32& uResultSize);
			GAIA_CLASS_OPERATOR_COMPARE(m_h, m_h, Handle);
		private:
			GINL GAIA::GVOID init()
			{
				m_h = GINVALID;
				m_addr_self.Invalid();
				m_conndesc.reset();
				m_pSender = GNIL;
				m_pReceiver = GNIL;
				m_nSendBufferSize = 1024;
				m_nRecvBufferSize = 1024;
				while(!m_sendque.empty())
				{
					SendRec& r = m_sendque.front();
					GAIA_MFREE(r.p);
					m_sendque.pop_front();
				}
				m_bConnected = GAIA::False;
			}
			GINL virtual GAIA::GVOID LostConnection(const GAIA::NETWORK::Addr& na, GAIA::BL bRecvTrueSendFalse){}
			GINL GAIA::BL FlushSendQueue();
		private:
			GAIA::N32 m_h;
			GAIA::NETWORK::Addr m_addr_self;
			ConnectDesc m_conndesc;
			Sender* m_pSender;
			Receiver* m_pReceiver;
			GAIA::SYNC::Lock m_lock;
			__SendQueueType m_sendque;
			__SendListType m_tempsendlist;
			GAIA::N32 m_nSendBufferSize;
			GAIA::N32 m_nRecvBufferSize;
			GAIA::U8 m_bConnected : 1;
		};
		class Listener : public GAIA::THREAD::Thread
		{
		public:
			class ListenDesc : public GAIA::Base
			{
			public:
				GINL GAIA::GVOID reset()
				{
					addr.Invalid();
					nListenSendBufSize = 1024;
					nListenRecvBufSize = 1024;
					nAcceptSendBufSize = 1024;
					nAcceptRecvBufSize = 1024;
					bSync = GAIA::False;
				}
				GAIA::NETWORK::Addr addr;
				GAIA::N32 nListenSendBufSize;
				GAIA::N32 nListenRecvBufSize;
				GAIA::N32 nAcceptSendBufSize;
				GAIA::N32 nAcceptRecvBufSize;
				GAIA::U8 bSync : 1;
			};
			class AcceptCallBack
			{
			public:
				virtual GAIA::NETWORK::Handle* CreateNetworkHandle() = 0;
			};
		public:
			GINL Listener(){this->init();}
			GINL ~Listener(){if(this->IsBegin()) this->End();}
			GINL GAIA::GVOID SetDesc(const ListenDesc& desc){m_desc = desc;}
			GINL const ListenDesc& GetDesc() const{return m_desc;}
			GINL GAIA::GVOID SetAcceptCallBack(AcceptCallBack* pAcceptCallBack){m_pAcceptCallBack = pAcceptCallBack;}
			GINL AcceptCallBack* GetAcceptCallBack() const{return m_pAcceptCallBack;}
			GINL GAIA::BL Begin();
			GINL GAIA::BL End();
			GINL GAIA::BL IsBegin() const{return m_bBegin;}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Accept(GAIA::NETWORK::Handle& h){return GAIA::False;}
			GINL virtual GAIA::GVOID WorkProcedure();
		private:
			GINL GAIA::GVOID init()
			{
				m_desc.reset();
				m_bBegin = GAIA::False;
				m_bStopCmd = GAIA::False;
				m_pAcceptCallBack = GNIL;
			}
		private:
			ListenDesc m_desc;
			GAIA::U8 m_bBegin : 1;
			GAIA::U8 m_bStopCmd : 1;
			AcceptCallBack* m_pAcceptCallBack;
		};
		class Sender : public GAIA::THREAD::Thread
		{
		private:
			friend class Handle;
		private:
			typedef GAIA::CTN::Set<GAIA::CTN::Ref<Handle> > __HandleSetType;
			typedef GAIA::CTN::Vector<Handle*> __HandleListType;
		public:
			GINL Sender(){this->init();}
			GINL ~Sender(){if(this->IsBegin()) this->End(); this->RemoveAll();}
			GINL GAIA::BL Begin();
			GINL GAIA::BL End();
			GINL GAIA::BL IsBegin() const{return m_bBegin;}
		private:
			GINL GAIA::BL Add(Handle& h)
			{
				__HandleSetType::_datatype finder = &h;
				GAIA::SYNC::AutoLock al(m_lock);
				if(m_hs.find(finder) != GNIL)
					return GAIA::False;
				h.Reference();
				m_hs.insert(&h);
				return GAIA::True;
			}
			GINL GAIA::BL Remove(Handle& h)
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
				for(; !iter.empty(); ++iter)
				{
					Handle* pHandle = *iter;
					GAIA_AST(!!pHandle);
					pHandle->Release();
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
		class Receiver : public GAIA::THREAD::Thread
		{
		private:
			friend class Handle;
		private:
			typedef GAIA::CTN::Set<GAIA::CTN::Ref<Handle> > __HandleSetType;
			typedef GAIA::CTN::Vector<Handle*> __HandleListType;
			typedef GAIA::CTN::Buffer __BufferType;
		public:
			GINL Receiver(){this->init();}
			GINL ~Receiver(){if(this->IsBegin()) this->End(); this->RemoveAll();}
			GINL GAIA::BL Begin();
			GINL GAIA::BL End();
			GINL GAIA::BL IsBegin() const{return m_bBegin;}
		private:
			GINL GAIA::BL Add(Handle& h)
			{
				__HandleSetType::_datatype finder = &h;
				GAIA::SYNC::AutoLock al(m_lock);
				if(m_hs.find(finder) != GNIL)
					return GAIA::False;
				h.Reference();
				m_hs.insert(&h);
				return GAIA::True;
			}
			GINL GAIA::BL Remove(Handle& h)
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
				for(; !iter.empty(); ++iter)
				{
					Handle* pHandle = *iter;
					GAIA_AST(!!pHandle);
					pHandle->Release();
				}
				m_hs.destroy();
			}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(GAIA::NETWORK::Handle& h, const GAIA::U8* p, GAIA::U32 size){return GAIA::False;}
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

#include "gaia_network_indp.h"

#endif
