#ifndef		__GAIA_FRAMEWORK_INSTANCE_CREATOR_H__
#define		__GAIA_FRAMEWORK_INSTANCE_CREATOR_H__

namespace GAIA
{
	namespace FWORK
	{
		namespace INSTCREATOR
		{
			typedef GAIA::FWORK::Instance* (*CREATE_INSTANCE_PROC)();
		};
	};
};

#endif