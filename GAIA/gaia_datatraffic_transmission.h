#ifndef		__GAIA_DATATRAFFIC_TRANSMISSION_H__
#define		__GAIA_DATATRAFFIC_TRANSMISSION_H__

namespace GAIA
{
	namespace DATATRAFFIC
	{
		class Transmission : public GAIA::FRAMEWORK::Instance, public GAIA::THREAD::Thread
		{
		public:
			virtual GAIA::BL RegistRoute(GAIA::DATATRAFFIC::Route* pRoute) = 0;
			virtual GAIA::BL UnregistRoute(GAIA::DATATRAFFIC::Route* pRoute) = 0;
			virtual GAIA::BL IsRegistedRoute(GAIA::DATATRAFFIC::Route* pRoute) const = 0;
			virtual GAIA::BL CollectRoutes(GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Route*>& listResult) const = 0;

		protected:
		};

		class BaseTransmission : public Transmission
		{
		private: // Helper type declaration here for internal use.
			typedef GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Route*> LIST_ROUTE;
			typedef GAIA::CONTAINER::BasicQueue<GAIA::U32
		public:
			virtual GAIA::BL RegistRoute(GAIA::DATATRAFFIC::Route* pRoute)
			{
				GAIA_ASSERT(pRoute != NULL);
			}
			virtual GAIA::BL UnregistRoute(GAIA::DATATRAFFIC::Route* pRoute)
			{
				GAIA_ASSERT(pRoute != NULL);
			}
			virtual GAIA::BL IsRegistedRoute(GAIA::DATATRAFFIC::Route* pRoute) const
			{
				GAIA_ASSERT(pRoute != NULL);
			}
			virtual GAIA::BL CollectRoutes(GAIA::CONTAINER::Vector<GAIA::DATATRAFFIC::Route*>& listResult) const
			{
			}
		private:
			LIST_ROUTE m_listRoute;

		};
	};
};

#endif