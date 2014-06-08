#ifndef 	__GAIA_SYNC_AUTOLOCK_H__
#define 	__GAIA_SYNC_AUTOLOCK_H__

namespace GAIA
{
	namespace SYNC
	{
		class AutoLock : public GAIA::Base
		{
		public:
			GINL AutoLock(Lock& l){m_pLock = &l; m_pLock->Enter();}
			GINL ~AutoLock(){m_pLock->Leave();}
		private:
			Lock* m_pLock;
		};
	};
};

#endif
