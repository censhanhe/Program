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
			GINL Atomic(const GAIA::N64& src){this->operator = (src);}
			GINL ~Atomic(){}
			GINL Atomic& operator = (const Atomic& src){GAIA_AST(&src != this); m_n = src.m_n; return *this;}
			GINL Atomic& operator = (const GAIA::N64& src);
			GINL operator GAIA::N64() const;
			GINL GAIA::N64 Increase(); // Return the new value.
			GINL GAIA::N64 Decrease(); // Return the new value.
			GINL GAIA::N64 Add(const GAIA::N64& src); // Return the new value.
			GINL GAIA::N64 Add(const Atomic& src); // Return the new value.
		private:
			GINL GAIA::GVOID init(){m_n = 0;}
		private:
			volatile GAIA::N64 m_n;
		};
	};
};

#include "gaia_sync_atomic_indp.h"

#endif
