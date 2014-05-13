#ifndef 	__GAIA_SYNC_ATOMIC_H__
#define 	__GAIA_SYNC_ATOMIC_H__

namespace GAIA
{
	namespace SYNC
	{
		class Atomic : public GAIA::Base
		{
		public:
			GINL Atomic(){}
			GINL Atomic(const Atomic& src){this->operator = (src);}
			GINL ~Atomic(){}
			GINL Atomic& operator = (const Atomic& src){GAIA_AST(&src != this); m_n = src.m_n; return *this;}
			GINL Atomic& operator = (const GAIA::N64& src){m_n = src; return *this;}
			GINL operator GAIA::N64() const{return m_n;}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 Increase();
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::N64 Decrease();
		private:
			volatile GAIA::N64 m_n;
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_sync_atomic_indp.h"
#endif

#endif
