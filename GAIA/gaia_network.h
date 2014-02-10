#ifndef		__GAIA_NETWORK_H__
#define		__GAIA_NETWORK_H__

namespace GAIA
{
	namespace NETWORK
	{
		class NetworkAddress
		{
		public:
			GINL GAIA::GVOID FromString(const GAIA::GCH* psz);
			GINL GAIA::GVOID ToString(GAIA::GCH* psz);
			GAIA::U64 uIP;
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
			GINL virtual GAIA::BL Accept(const NetworkHandle& h) const = 0;
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
		protected:
		private:
		};
		class NetworkReceiver
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
			GINL virtual GAIA::BL Receive(const NetworkSender& s, const GAIA::U8* p, GAIA::U32 size) const = 0;
		private:
		};
	};
};

#endif
