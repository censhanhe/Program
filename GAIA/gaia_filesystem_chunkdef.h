#ifndef		__GAIA_FILESYSTEM_CHUNKDEF_H__
#define		__GAIA_FILESYSTEM_CHUNKDEF_H__

namespace GAIA
{
	namespace FILESYSTEM
	{
		typedef GAIA::U32 CHUNK_TYPE;
		typedef GAIA::U64 CHUNK_SIZE;
		typedef GAIA::U32 SUBCHUNK_TYPE;
		typedef GAIA::U32 SUBCHUNK_SIZE;
		static const CHUNK_TYPE CHUNK_TYPE_START	= 0x00010000;
		static const CHUNK_TYPE CHUNK_TYPE_XML		= 0x00010001;
		static const CHUNK_TYPE CHUNK_TYPE_USER		= 0x10000000;
	};
};

#endif