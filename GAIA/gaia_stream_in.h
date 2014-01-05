#ifndef		__GAIA_STREAM_IN_H__
#define		__GAIA_STREAM_IN_H__

namespace GAIA
{
	namespace STREAM
	{
		class StreamIn
		{
		public:
			GINL StreamIn();
			GINL ~StreamIn();

			GINL GAIA::BL Connect(StreamOut& so);
		};
	}
};

#endif
