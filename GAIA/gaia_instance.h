#ifndef		__GAIA_FRAMEWORK_INSTANCE_H__
#define		__GAIA_FRAMEWORK_INSTANCE_H__

namespace GAIA
{
	namespace FRAMEWORK
	{
		class Instance : public RefObject
		{
		private:
			friend class Factory;
		public:
			GINL Instance(){}
			GINL ~Instance(){}
			virtual ClsID GetClassID() const = 0;
		protected:
			virtual GAIA::GVOID Destruct(){if(this->IsBegin()) this->End();}
		protected:
			virtual GAIA::BL Begin(GAIA::GVOID* pParameter) = 0;
			virtual GAIA::BL End() = 0;
			virtual GAIA::BL IsBegin() const = 0;
		};
	};
};

#endif
