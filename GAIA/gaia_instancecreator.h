#ifndef		__GAIA_INSTANCE_CREATOR_H__
#define		__GAIA_INSTANCE_CREATOR_H__

namespace GAIA
{
	namespace FWORK
	{
		namespace INSTCREATOR
		{
			class InstanceCreator : public GAIA::Base
			{
			public:
				virtual GAIA::FWORK::Instance* Create() = 0;
			};
		};
	};
};

#endif