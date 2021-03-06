#ifndef		__GAIA_TYPE_IMPL_H__
#define		__GAIA_TYPE_IMPL_H__

namespace GAIA
{
#ifndef GAIA_DEBUG_MEMORYLEAK
#	if GAIA_MACHINE == GAIA_MACHINE32
		GINL GAIA::GVOID* Base::operator new(GAIA::U32 size){return g_gaia_globalallocator.memory_alloc((GAIA::UM)size);}
			GINL GAIA::GVOID* Base::operator new[](GAIA::U32 size){return g_gaia_globalallocator.memory_alloc((GAIA::UM)size);}
#	elif GAIA_MACHINE == GAIA_MACHINE64
		GINL GAIA::GVOID* Base::operator new(GAIA::U64 size){return g_gaia_globalallocator.memory_alloc((GAIA::UM)size);}
		GINL GAIA::GVOID* Base::operator new[](GAIA::U64 size){return g_gaia_globalallocator.memory_alloc((GAIA::UM)size);}
#	endif
	GINL GAIA::GVOID Base::operator delete(GAIA::GVOID* p){return g_gaia_globalallocator.memory_release(p);}
	GINL GAIA::GVOID Base::operator delete[](GAIA::GVOID* p){return g_gaia_globalallocator.memory_release(p);}
#endif

	template<typename _ParamDataType> GAIA::GVOID X128::fromstring(const _ParamDataType* psz)
	{
		GAIA_INTERNAL_NAMESPACE::str2hex(psz, sizeofarray(u8), u8);
	}
	template<typename _ParamDataType> GAIA::GVOID X128::tostring(_ParamDataType* psz) const
	{
		GAIA_INTERNAL_NAMESPACE::hex2str(u8, sizeofarray(u8), psz);
	}

	GINL TYPEID nametotype(const GAIA::CH* psz)
	{
		for(GAIA::N32 x = 0; x < sizeofarray(TYPEID_ANAME); ++x)
		{
			if(GAIA_INTERNAL_NAMESPACE::strcmp(TYPEID_ANAME[x], psz) == 0)
				return GSCAST(TYPEID)(x);
		}
		return TYPEID_INVALID;
	}
	GINL TYPEID nametotype(const GAIA::WCH* psz)
	{
		for(GAIA::N32 x = 0; x < sizeofarray(TYPEID_WNAME); ++x)
		{
			if(GAIA_INTERNAL_NAMESPACE::strcmp(TYPEID_WNAME[x], psz) == 0)
				return GSCAST(TYPEID)(x);
		}
		return TYPEID_INVALID;
	}
};

#endif
