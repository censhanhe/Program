#ifndef		__VENUS_H__
#define		__VENUS_H__

#include "../GAIA/gaia.h"
#include "venus_render.h"

namespace VENUS
{
	static const GAIA::FWORK::ClsID CLSID_VENUS_RENDERGL = GAIA::FWORK::ClsID(0x80, 0x01, 0x0000, 0x0000, GAIA::FWORK::ClsID::FLAG_USERDEFINE);

	extern GAIA::BL Initialize(GAIA::FWORK::Factory& fac);
	extern GAIA::BL Release(GAIA::FWORK::Factory& fac);
};

#endif