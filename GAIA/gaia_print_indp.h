#ifndef		__GAIA_PRINT_INDP_H__
#define		__GAIA_PRINT_INDP_H__

#include <stdlib.h>
#include <iostream>
#include <iomanip>

namespace GAIA
{
	namespace PRINT
	{
		GINL GAIA::GVOID Print::clear_screen()
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			system("cls");
		#else
			system("clear");
		#endif
		}
		GINL Print& Print::operator << (GAIA::BL t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::NM t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::UM t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::N8 t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::N16 t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::N32 t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (const GAIA::N64& t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::U8 t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::U16 t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::U32 t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (const GAIA::U64& t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (GAIA::F32 t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (const GAIA::F64& t)
		{
			if(!this->enable_write())
				return *this;
			std::cout << t;
			return *this;
		}
		GINL Print& Print::operator << (const GAIA::WCH& t)
		{
			if(!this->enable_write())
				return *this;
			std::wcout << t;
			return *this;
		}
		GINL Print& Print::operator << (const GAIA::CH* p)
		{
			if(p == GNIL)
				return *this;
			if(!this->enable_write())
				return *this;
			std::cout << p;
			return *this;
		}
		GINL Print& Print::operator << (const GAIA::WCH* p)
		{
			if(p == GNIL)
				return *this;
			if(!this->enable_write())
				return *this;
			std::wcout << p;
			return *this;
		}
		GINL Print& Print::operator << (const GAIA::X128& t)
		{
			if(!this->enable_write())
				return *this;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::BL& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::NM& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::UM& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::N8& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::N16& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::N32& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::N64& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::U8& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::U16& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::U32& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::U64& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::F32& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::F64& t)
		{
			if(!this->enable_read())
				return *this;
			std::cin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::WCH& t)
		{
			if(!this->enable_read())
				return *this;
			std::wcin >> t;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::CH* p)
		{
			if(p == GNIL)
				return *this;
			if(!this->enable_read())
				return *this;
			std::cin >> p;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::WCH* p)
		{
			if(p == GNIL)
				return *this;
			if(!this->enable_read())
				return *this;
			std::wcin >> p;
			return *this;
		}
		GINL Print& Print::operator >> (GAIA::X128& t)
		{
			if(!this->enable_read())
				return *this;
			GAIA::CH sz[128];
			std::cin >> sz;
			t = sz;
			return *this;
		}
		GINL Print& Print::operator >> (PrintFormat& pf)
		{
			pf = m_pf;
			return *this;
		}
		GINL Print& Print::operator << (const PrintFormat& pf)
		{
			if(pf.align() != m_pf.align() || pf.align() != 0)
			{
				std::cout << std::setw(pf.align());
				std::wcout << std::setw(pf.align());
				m_pf.align(pf.align());
			}
			if(pf.precision() != m_pf.precision())
			{
				std::cout << std::setprecision(pf.precision());
				std::wcout << std::setprecision(pf.precision());
				m_pf.precision(pf.precision());
			}
			if(pf.radix() != m_pf.radix())
			{
				std::cout << std::setbase(pf.radix());
				std::wcout << std::setbase(pf.radix());
				m_pf.radix(pf.radix());
			}
			if(pf.showpoint() != m_pf.showpoint())
			{
				if(pf.showpoint())
				{
					std::cout << std::showpoint;
					std::wcout << std::showpoint;
				}
				else
				{
					std::cout << std::noshowpoint;
					std::wcout << std::noshowpoint;
				}
				m_pf.showpoint(pf.showpoint());
			}
			if(pf.showbase() != m_pf.showbase())
			{
				if(pf.showbase())
				{
					std::cout << std::showbase;
					std::wcout << std::showbase;
				}
				else
				{
					std::cout << std::noshowbase;
					std::wcout << std::noshowbase;
				}
				m_pf.showbase(pf.showbase());
			}
			if(pf.showsign() != m_pf.showsign())
			{
				if(pf.showsign())
				{
					std::cout << std::showpos;
					std::wcout << std::showpos;
				}
				else
				{
					std::cout << std::noshowpos;
					std::wcout << std::noshowpos;
				}
				m_pf.showsign(pf.showsign());
			}
			if(pf.scientific() != m_pf.scientific())
			{
				if(pf.scientific())
				{
					std::cout << std::scientific;
					std::wcout << std::scientific;
				}
				else
				{
					std::cout << std::fixed;
					std::wcout << std::fixed;
				}
				m_pf.scientific(pf.scientific());
			}
			if(pf.left() != m_pf.left())
			{
				if(pf.left())
				{
					std::cout << std::left;
					std::wcout << std::left;
				}
				else
				{
					std::cout << std::right;
					std::wcout << std::right;
				}
				m_pf.left(pf.left());
			}
			if(pf.uppercase() != m_pf.uppercase())
			{
				if(pf.uppercase())
				{
					std::cout << std::uppercase;
					std::wcout << std::uppercase;
				}
				else
				{
					std::cout << std::nouppercase;
					std::wcout << std::nouppercase;
				}
				m_pf.uppercase(pf.uppercase());
			}
			m_pf = pf;
			return *this;
		}
		GINL GAIA::GVOID Print::flush()
		{
			std::cout << std::flush;
		}
	};
};

#endif
