#ifndef 	__GAIA_SYNC_ATOMIC_H__
#define 	__GAIA_SYNC_ATOMIC_H__

namespace GAIA
{
	namespace SYNC
	{
		class Atomic : public GAIA::Entity
		{
		public:
			GINL Atomic(){this->init();}
			GINL Atomic(const Atomic& src){this->operator = (src);}
			GINL ~Atomic(){}
			GINL Atomic& operator = (const Atomic& src){GAIA_AST(&src != this); m_n = src.m_n; return *this;}
			GINL Atomic& operator = (const GAIA::N64& src){m_n = src; return *this;}
			GINL operator GAIA::N64() const{return m_n;}
			GINL GAIA::N64 Increase();
			GINL GAIA::N64 Decrease();
			GINL GAIA::N64 Add(const GAIA::N64& src);
			GINL GAIA::N64 Add(const Atomic& src);
		private:
			GINL GAIA::GVOID init(){m_n = 0;}
		private:
			volatile GAIA::N64 m_n;
		};
	};
};

#include "gaia_sync_atomic_indp.h"

#endif
