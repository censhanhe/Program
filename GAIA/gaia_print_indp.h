#ifndef		__GAIA_PRINT_INDP_H__
#define		__GAIA_PRINT_INDP_H__

#include	<iostream>

namespace GAIA
{
	namespace PRINT
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::BL t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::NM t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::UM t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::N8 t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::N16 t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::N32 t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (const GAIA::N64& t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::U8 t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::U16 t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::U32 t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (const GAIA::U64& t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (GAIA::F32 t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (const GAIA::F64& t)
		{
			std::cout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (const GAIA::GWCH& t)
		{
			std::wcout << t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (const GAIA::GCH* p)
		{
			if(p == GNULL)
				return *this;
			std::cout << p;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (const GAIA::GWCH* p)
		{
			if(p == GNULL)
				return *this;
			std::wcout << p;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator << (const GAIA::X128& t)
		{
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::BL& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::NM& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::UM& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::N8& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::N16& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::N32& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::N64& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::U8& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::U16& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::U32& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::U64& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::F32& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::F64& t)
		{
			std::cin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::GWCH& t)
		{
			std::wcin >> t;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::GCH* p)
		{
			if(p == GNULL)
				return *this;
			std::cin >> p;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::GWCH* p)
		{
			if(p == GNULL)
				return *this;
			std::wcin >> p;
			return *this;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC Print& Print::operator >> (GAIA::X128& t)
		{
			return *this;
		}
	};
};

#endif