#ifndef		__GAIA_STREAM_OUT_H__
#define		__GAIA_STREAM_OUT_H__

namespace GAIA
{
	namespace STREAM
	{
		class StreamOut
		{
		public:
			GINL StreamOut();
			GINL ~StreamOut();

			GINL GAIA::BL Connect(StreamIn& si);
		};
	}
};

#endif