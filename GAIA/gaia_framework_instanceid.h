#ifndef		__GAIA_FRAMEWORK_INSTANCE_ID_H__
#define		__GAIA_FRAMEWORK_INSTANCE_ID_H__

namespace GAIA
{
	namespace FWORK
	{
		class InstanceId : public virtual GAIA::Base
		{
		public:
			GINL InstanceId(){m_rid.uuid();}
			GINL const GAIA::MATH::RID128& GetInstanceID() const{return m_rid;}
		private:
			GAIA::MATH::RID128 m_rid;
		};
	};
};

#endif