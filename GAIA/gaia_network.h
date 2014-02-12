#ifndef		__GAIA_NETWORK_H__
#define		__GAIA_NETWORK_H__

namespace GAIA
{
	namespace NETWORK
	{
		class IP
		{
		public:
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
		public:
			class ConnectDesc
			{
			public:
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
			template <typename _SizeType> GINL BL Send(const GAIA::U8* p, const _SizeType& t);
			template <typename _DataType> GINL GAIA::BL Send(const _DataType& t);
			template <typename _DataType> GINL GAIA::BL operator << (const _DataType& t);
		private:
			GINL GAIA::GVOID init()
			{
				m_h = GINVALID;
				m_addr_self.Invalid();
				m_conndesc.addr.Invalid();
				m_conndesc.bStabilityLink = GAIA::True;
				m_pSender = GNULL;
				m_pReceiver = GNULL;
			}
		private:
			GAIA::N32 m_h;
			NetworkAddress m_addr_self;
			ConnectDesc m_conndesc;
			NetworkSender* m_pSender;
			NetworkReceiver* m_pReceiver;
		};
		class NetworkListener : public GAIA::THREAD::Thread
		{
		public:
			class ListenDesc
			{
			public:
				NetworkAddress addr;
			};
		public:
			GINL NetworkListener(){}
			GINL ~NetworkListener(){}
			GINL GAIA::GVOID SetDesc(const ListenDesc& desc){}
			GINL const ListenDesc& GetDesc() const{}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Begin();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL End();
			GINL GAIA::BL IsBegin() const{}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Accept(const NetworkHandle& h) const = 0;
			virtual GAIA::GVOID WorkProcedule();
		private:
		};
		class NetworkSender : public GAIA::THREAD::Thread
		{
		private:
			friend class NetworkHandle;
		public:
			GINL NetworkSender(){}
			GINL ~NetworkSender(){}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Begin();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL End();
			GINL GAIA::BL IsBegin() const{}
		private:
			GINL GAIA::BL Add(NetworkHandle& h){}
			GINL GAIA::BL Remove(NetworkHandle& h){}
			GINL GAIA::GVOID RemoveAll(){}
		protected:
			virtual GAIA::GVOID WorkProcedule();
		private:
		};
		class NetworkReceiver : public GAIA::THREAD::Thread
		{
		private:
			friend class NetworkHandle;
		public:
			GINL NetworkReceiver(){}
			GINL ~NetworkReceiver(){}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Begin();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL End();
			GINL GAIA::BL IsBegin() const{}
		private:
			GINL GAIA::BL Add(NetworkHandle& h){}
			GINL GAIA::BL Remove(NetworkHandle& h){}
			GINL GAIA::GVOID RemoveAll(){}
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const NetworkSender& s, const GAIA::U8* p, GAIA::U32 size) const = 0;
			virtual GAIA::GVOID WorkProcedule();
		private:
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_network_indp.h"
#endif

#endif
