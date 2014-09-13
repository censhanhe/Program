#ifndef 	__T_CONTAINER_STATICSTRINGPOOL_H__
#define 	__T_CONTAINER_STATICSTRINGPOOL_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_staticstringpool(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		typedef GAIA::CONTAINER::StaticStringPool<GAIA::TCH> __StaticStringPoolType;
		__StaticStringPoolType sp;
		if(!sp.empty())
		{
		}
		if(sp.size() != 0)
		{
		}
		if(sp.capacity() != 0)
		{
		}
		if(sp.string_size() != 0)
		{
		}
		sp.clear();
		if(!sp.empty())
		{
		}
		if(sp.size() != 0)
		{
		}
		if(sp.capacity() != 0)
		{
		}
		if(sp.string_size() != 0)
		{
		}
		sp.destroy();
		if(!sp.empty())
		{
		}
		if(sp.size() != 0)
		{
		}
		if(sp.capacity() != 0)
		{
		}
		if(sp.string_size() != 0)
		{
		}

		return nRet;
	}
};

#endif
