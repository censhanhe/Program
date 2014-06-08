#ifndef		__GAIA_PROCESS_H__
#define		__GAIA_PROCESS_H__

namespace GAIA
{
	namespace PROCESS
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::UM processid();
		class Process : public GAIA::Base
		{
		public:
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_process_indp.h"
#endif

#endif
