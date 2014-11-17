#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 t_time_time(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::TCH* STRTIMELIST[] = 
		{
			_T("20141001"),
			_T("201410010830"),
			_T("20141001083000"),
			_T("20141001083059999"),
			_T("20141001083059999123"),
		};
		static const GAIA::TCH* STRTIMELISTAUX[] = 
		{
			_T("2014-10-01"),
			_T("2014-10-01_08:30"),
			_T("2014-10-01_08:30:00"),
			_T("2014-10-01_08:30:59_999"),
			_T("2014-10-01_08:30:59_999_123"),
		};

		GAIA::TCH szTemp[32], szTempAux[32];
		for(GAIA::SIZE x = 0; x < sizeofarray(STRTIMELIST); ++x)
		{
			szTemp[0] = '\0';
			szTempAux[0] = '\0';
			GAIA::ALGO::strcpy(szTemp, STRTIMELIST[x]);
			if(!GAIA::TIME::timemkaux(szTemp, szTempAux))
			{
				GTLINE2("Time timemkaux failed!");
				++nRet;
				break;
			}
			if(GAIA::ALGO::strcmp(szTempAux, STRTIMELISTAUX[x]) != 0)
			{
				GTLINE2("Time timemkaux failed!");
				++nRet;
				break;
			}
			szTemp[0] = '\0';
			szTempAux[0] = '\0';
			GAIA::ALGO::strcpy(szTempAux, STRTIMELISTAUX[x]);
			if(!GAIA::TIME::timermaux(szTempAux, szTemp))
			{
				GTLINE2("Time timermaux failed!");
				++nRet;
				break;
			}
			if(GAIA::ALGO::strcmp(szTemp, STRTIMELIST[x]) != 0)
			{
				GTLINE2("Time timermaux failed!");
				++nRet;
				break;
			}
		}

		GAIA::TIME::Time t, t1;
		t.reset();
		if(t.check())
		{
			GTLINE2("Time check failed!");
			++nRet;
		}
		t1 = t;
		if(t1.check())
		{
			GTLINE2("Time check failed!");
			++nRet;
		}
		for(GAIA::SIZE x = 0; x < sizeofarray(STRTIMELIST); ++x)
		{
			t = STRTIMELIST[x];

			t.to(szTemp);
			if(GAIA::ALGO::strcmp(szTemp, STRTIMELIST[x], GAIA::ALGO::strlen(STRTIMELIST[x])) != 0)
			{
				GTLINE2("Time to string error!");
				++nRet;
				break;
			}
			if(!t.isvalid())
			{
				GTLINE2("Time operator = from string failed!");
				++nRet;
				break;
			}

			GAIA::U64 uCompressTime;
			t.to(uCompressTime);
			t.from(uCompressTime);
			if(GAIA::ALGO::strcmp(szTemp, STRTIMELIST[x], GAIA::ALGO::strlen(STRTIMELIST[x])) != 0)
			{
				GTLINE2("Time to compress time error!");
				++nRet;
				break;
			}
			if(!t.isvalid())
			{
				GTLINE2("Time operator = from compress time failed!");
				++nRet;
				break;
			}

			GAIA::N64 usec = t.usecond();
			GAIA::TIME::Time tt;
			tt.usecond(usec);
			if(tt != t)
			{
				GTLINE2("Time usecond convert failed!");
				++nRet;
				break;
			}
			if(!(t == STRTIMELIST[x]))
			{
				GTLINE2("Time operator = from string and compare == failed!");
				++nRet;
				break;
			}
			if(t != STRTIMELIST[x])
			{
				GTLINE2("Time operator = from string and compare != failed!");
				++nRet;
				break;
			}
			if(!(t >= STRTIMELIST[x]))
			{
				GTLINE2("Time operator = from string and compare >= failed!");
				++nRet;
				break;
			}
			if(!(t <= STRTIMELIST[x]))
			{
				GTLINE2("Time operator = from string and compare <= failed!");
				++nRet;
				break;
			}
			if(t > STRTIMELIST[x])
			{
				GTLINE2("Time operator = from string and compare > failed!");
				++nRet;
				break;
			}
			if(t < STRTIMELIST[x])
			{
				GTLINE2("Time operator = from string and compare < failed!");
				++nRet;
				break;
			}
			GAIA::N64 nTime = t;
			if(!(t == nTime))
			{
				GTLINE2("Time operator = from string and compare == failed!");
				++nRet;
				break;
			}
			if(t != nTime)
			{
				GTLINE2("Time operator = from string and compare != failed!");
				++nRet;
				break;
			}
			if(!(t >= nTime))
			{
				GTLINE2("Time operator = from string and compare >= failed!");
				++nRet;
				break;
			}
			if(!(t <= nTime))
			{
				GTLINE2("Time operator = from string and compare <= failed!");
				++nRet;
				break;
			}
			if(t > nTime)
			{
				GTLINE2("Time operator = from string and compare > failed!");
				++nRet;
				break;
			}
			if(t < nTime)
			{
				GTLINE2("Time operator = from string and compare < failed!");
				++nRet;
				break;
			}
			t = nTime;
			if(!t.isvalid())
			{
				GTLINE2("Time operator = from N64 failed!");
				++nRet;
				break;
			}
			if(!(t == STRTIMELIST[x]))
			{
				GTLINE2("Time operator = from string and compare == failed!");
				++nRet;
				break;
			}
			if(t != STRTIMELIST[x])
			{
				GTLINE2("Time operator = from string and compare != failed!");
				++nRet;
				break;
			}
			if(!(t >= STRTIMELIST[x]))
			{
				GTLINE2("Time operator = from string and compare >= failed!");
				++nRet;
				break;
			}
			if(!(t <= STRTIMELIST[x]))
			{
				GTLINE2("Time operator = from string and compare <= failed!");
				++nRet;
				break;
			}
			if(t > STRTIMELIST[x])
			{
				GTLINE2("Time operator = from string and compare > failed!");
				++nRet;
				break;
			}
			if(t < STRTIMELIST[x])
			{
				GTLINE2("Time operator = from string and compare < failed!");
				++nRet;
				break;
			}
		}

		t = _T("20000930083059999123");
		GAIA::N64 usec = t.usecond();
		t.usecond(usec);
		if(t != _T("20000930083059999123"))
		{
			GTLINE2("Time with leapyear convert to N64 failed!");
			++nRet;
		}

		t = _T("20001001083059999123");
		usec = t.usecond();
		t.usecond(usec);
		if(t != _T("20001001083059999123"))
		{
			GTLINE2("Time with leapyear convert to N64 failed!");
			++nRet;
		}

		t = _T("20140930083059999123");
		usec = t.usecond();
		t.usecond(usec);
		if(t != _T("20140930083059999123"))
		{
			GTLINE2("Time with leapyear convert to N64 failed!");
			++nRet;
		}

		t = _T("20141001083059999123");
		usec = t.usecond();
		t.usecond(usec);
		if(t != _T("20141001083059999123"))
		{
			GTLINE2("Time with leapyear convert to N64 failed!");
			++nRet;
		}

		t = _T("20000930083059999123");
		t.dayinc();
		if(!t.isvalid() || t != _T("20001001083059999123"))
		{
			GTLINE2("Time dayinc failed!");
			++nRet;
		}

		t = _T("20001001083059999123");
		t.daydec();
		if(!t.isvalid() || t != _T("20000930083059999123"))
		{
			GTLINE2("Time daydec failed!");
			++nRet;
		}

		t = _T("20000930083059999123");
		t += GSCAST(GAIA::N64)(24) * 60 * 60 * 1000 * 1000;
		if(!t.isvalid() || t != _T("20001001083059999123"))
		{
			GTLINE2("Time operator += Time failed!");
			++nRet;
		}

		t = _T("20001001083059999123");
		t -= GSCAST(GAIA::N64)(24) * 60 * 60 * 1000 * 1000;
		if(!t.isvalid() || t != _T("20000930083059999123"))
		{
			GTLINE2("Time operator -= Time failed!");
			++nRet;
		}

		t = _T("20000930083059999123");
		t = t + GSCAST(GAIA::N64)(24) * 60 * 60 * 1000 * 1000;
		if(!t.isvalid() || t != _T("20001001083059999123"))
		{
			GTLINE2("Time operator + Time failed!");
			++nRet;
		}

		t = _T("20001001083059999123");
		t = t - GSCAST(GAIA::N64)(24) * 60 * 60 * 1000 * 1000;
		if(!t.isvalid() || t != _T("20000930083059999123"))
		{
			GTLINE2("Time operator - Time failed!");
			++nRet;
		}

		return nRet;
	}
};
