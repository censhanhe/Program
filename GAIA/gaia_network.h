#ifndef		__GAIA_NETWORK_H__
#define		__GAIA_NETWORK_H__

namespace GAIA
{
	namespace NETWORK
	{
		class NetworkHandle
		{
		public:
		};

		class NetworkListener
		{
		public:
			struct LISTEN_DESC
			{
				GAIA::U64 uIP;
				GAIA::U64 uPort;
			};
		public:
			GINL NetworkListener();
			GINL ~NetworkListener();
			GINL GAIA::GVOID SetListenDesc(const LISTEN_DESC& desc);
			GINL const LISTEN_DESC& GetListenDesc() const;
			GINL GAIA::BL BeginListen();
			GINL GAIA::BL EndListen();
			GINL GAIA::BL IsBeginListen() const;
		protected: // Interface for derived class callback.
			GINL virtual GAIA::BL Accept(const NetworkHandle& nh) = 0;
		};
	};
};

#endif
