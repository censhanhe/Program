#ifndef 	__PROMETHEUS_H__
#define 	__PROMETHEUS_H__

#include "../GAIA/gaia.h"
#include "../DWARFS/MISC/cmdparam.h"
#include "../DWARFS/MISC/textlines.h"

namespace PROM
{
	class Prom
	{
	public:
		GINL Prom()
		{
		}
		GINL ~Prom()
		{
		}
		GINL GAIA::BL command(const GAIA::GCH* psz)
		{
			GAIA_AST(psz != GNULL);
			if(psz == GNULL)
				return GAIA::False;
			if(*psz == 0)
				return GAIA::False;
			return GAIA::True;
		}
	private:
	};
};

#endif
