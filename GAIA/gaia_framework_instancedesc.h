#ifndef		__GAIA_FRAMEWORK_INSTANCE_DESC_H__
#define		__GAIA_FRAMEWORK_INSTANCE_DESC_H__

namespace GAIA
{
	namespace FWORK
	{
		class InstanceDesc : public virtual GAIA::Base
		{
		public:
			virtual GAIA::GVOID reset() = 0;
			virtual GAIA::BL check() const = 0;
		};
	};
};

#endif