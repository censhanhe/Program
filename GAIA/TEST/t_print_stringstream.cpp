#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_stream_stringstream(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& prt)
	{
		GAIA::N32 nRet = 0;

		GAIA::STREAM::StringStream sprt;
		sprt << (GAIA::U8)1 << " ";
		sprt << (GAIA::U16)2 << " ";
		sprt << (GAIA::U32)3 << " ";
		sprt << (GAIA::U64)4 << " ";
		sprt << (GAIA::N8)-5 << " ";
		sprt << (GAIA::N16)+6 << " ";
		sprt << (GAIA::N32)-7 << " ";
		sprt << (GAIA::N64)+8 << " ";
		sprt << (GAIA::UM)9 << " ";
		sprt << (GAIA::NM)-10 << " ";
		sprt << (GAIA::BL)GAIA::True << " ";
		sprt << (GAIA::F32)11.123456 << " ";
		sprt << (GAIA::F64)12.654321 << " ";
		sprt << (GAIA::CH*)"ansi string" << " ";
		sprt << (GAIA::WCH*)L"unicode string" << " ";

		const GAIA::STREAM::StringStream::__CharType* p = sprt.GetString();

		return nRet;
	}
};