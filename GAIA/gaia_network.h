#ifndef		__GAIA_NETWORK_H__
#define		__GAIA_NETWORK_H__

namespace GAIA
{
	namespace NETWORK
	{
		class StreamLinkListener
		{
		public:
			GINL StreamLinkListener();
			GINL ~StreamLinkListener();

			GINL GAIA::BL EnableListen();
			GINL GAIA::BL IsEnableListen() const;


		};
	};
};

#endif
