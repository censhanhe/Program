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
			union
			{
				GAIA::U8 u[6];
				struct
				{
					GAIA::U8 u0;
					GAIA::U8 u1;
					GAIA::U8 u2;
					GAIA::U8 u3;
					GAIA::U8 u4;
					GAIA::U8 u5;
				};
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
			IP ip;
			GAIA::U16 uPort;
		};
		class NetworkSender;
		class NetworkReceiver;
		class NetworkHandle : public RefObject
		{
		public:
			GINL NetworkHandle(){}
			GINL ~NetworkHandle(){}
			GINL GAIA::BL Connect(const NetworkAddress& addr);
			GINL GAIA::BL IsConnected() const;
			GINL GAIA::BL SetSelfAddress(const NetworkAddress& addr);
			GINL const NetworkAddress& GetSelfNetAddress() const;
			GINL const NetworkAddress* GetRemoteAddress() const;
			GINL GAIA::GVOID SetSender(NetworkSender* pSender);
			GINL NetworkSender* GetSender() const;
			GINL GAIA::GVOID SetReceiver(NetworkReceiver* pReceiver);
			GINL NetworkReceiver* GetReceiver() const;
			template <typename _SizeType> GINL BL Send(const GAIA::U8* p, const _SizeType& t);
			template <typename _DataType> GINL GAIA::BL Send(const _DataType& t);
			template <typename _DataType> GINL GAIA::BL operator << (const _DataType& t);
		private:
			GAIA::N32 m_h;
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
			GINL NetworkListener();
			GINL ~NetworkListener();
			GINL GAIA::GVOID SetDesc(const ListenDesc& desc);
			GINL const ListenDesc& GetDesc() const;
			GINL GAIA::BL Begin();
			GINL GAIA::BL End();
			GINL GAIA::BL IsBegin() const;
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
			GINL NetworkSender();
			GINL ~NetworkSender();
			GINL GAIA::BL Begin();
			GINL GAIA::BL End();
			GINL GAIA::BL IsBegin() const;
		private:
			GINL GAIA::BL Add(NetworkHandle& h);
			GINL GAIA::BL Remove(NetworkHandle& h);
			GINL GAIA::GVOID RemoveAll();
		private:
		};
		class NetworkReceiver : public GAIA::THREAD::Thread
		{
		private:
			friend class NetworkHandle;
		public:
			GINL NetworkReceiver(){}
			GINL ~NetworkReceiver(){}
			GINL GAIA::BL Begin();
			GINL GAIA::BL End();
			GINL GAIA::BL IsBegin() const;
		private:
			GINL GAIA::BL Add(NetworkHandle& h);
			GINL GAIA::BL Remove(NetworkHandle& h);
			GINL GAIA::GVOID RemoveAll();
		protected: // Interface for derived class callback.
			virtual GAIA::BL Receive(const NetworkSender& s, const GAIA::U8* p, GAIA::U32 size) const = 0;
			virtual GAIA::GVOID WorkProcedule();
		private:
		};
	};
};

#endif
