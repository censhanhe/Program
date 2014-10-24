#ifndef		__GAIA_TIME_H__
#define		__GAIA_TIME_H__

namespace GAIA
{
	namespace TIME
	{
		GINL GAIA::N32 leapyear(GAIA::N32 year){return year % 4 == 0;}
		GINL GAIA::N32 yeardays(GAIA::N32 year)
		{
			if(GAIA::TIME::leapyear(year))
				return 366;
			return 365;
		}
		GINL GAIA::N32 monthdays(GAIA::N32 year, GAIA::N32 month)
		{
			static const GAIA::N32 DAYS[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			if(month == 2)
			{
				if(GAIA::TIME::leapyear(year))
					return DAYS[month] + 1;
			}
			return DAYS[month];
		}
		GINL GAIA::N32 monthdaysall(GAIA::N32 year, GAIA::N32 month)
		{
			static const GAIA::N32 DAYSALL[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
			if(month > 2)
			{
				if(GAIA::TIME::leapyear(year))
					return DAYSALL[month] + 1;
			}
			return DAYSALL[month];
		}
		GINL GAIA::U64 clock_time(); // return value is micro second from 1970.1.1.
		GINL GAIA::U64 tick_time(); // return value is micro second from process startuped.
		/*
		 *	64-bit time compressed object as follow:
		 *
		 *	year 			: 18 bit.
		 *	month			: 4 bit.
		 *	day				: 5 bit.
		 *	hour			: 5 bit.
		 * 	minute			: 6 bit.
		 *	second			: 6 bit.
		 *	million second	: 10 bit.
		 *	micro second	: 10 bit.
		 */
		template<typename _DataType1, typename _DataType2> GAIA::BL timemkaux(const _DataType1* pSrc, _DataType2* pDst)
		{
			/*
			*  convert "00010203" to "0001-02-03";
			*  convert "000102030405" to "0001-02-03_04:05";
			*  convert "00010203040506" to "0001-02-03_04:05:06";
			*  convert "00010203040506007" to "0001-02-03_04:05:06_007";
			*  convert "00010203040506007008" to "0001-02-03_04:05:06_007:008";
			*/
			GPCHR_NULLSTRPTR_RET(pSrc, GAIA::False);
			GPCHR_NULL_RET(pDst, GAIA::False);
			GAIA::SIZE sLen = GAIA::ALGO::strlen(pSrc);
			if(sLen != 8 && sLen != 12 && sLen != 14 && sLen != 17 && sLen != 20 && sLen < 20)
			{
				GAIA_AST(GAIA::ALWAYSFALSE);
				return GAIA::False;
			}
			if(sLen >= 8)
			{
				GAIA::ALGO::strcpy(pDst, pSrc, 4);
				pDst += 4;
				pSrc += 4;
				*pDst++ = '-';
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
				*pDst++ = '-';
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
			}
			if(sLen >= 12)
			{
				*pDst++ = '_';
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
				*pDst++ = ':';
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
			}
			if(sLen >= 14)
			{
				*pDst++ = ':';
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
			}
			if(sLen >= 17)
			{
				*pDst++ = '_';
				GAIA::ALGO::strcpy(pDst, pSrc, 3);
				pDst += 3;
				pSrc += 3;
			}
			if(sLen >= 20)
			{
				*pDst++ = '_';
				GAIA::ALGO::strcpy(pDst, pSrc, 3);
				pDst += 3;
				pSrc += 3;
			}
			*pDst = '\0';
			return GAIA::True;
		}
		template<typename _DataType1, typename _DataType2> GAIA::BL timermaux(const _DataType1* pSrc, _DataType2* pDst)
		{
			/*
			*  convert "00010203" from "0001-02-03";
			*  convert "000102030405" from "0001-02-03_04:05";
			*  convert "00010203040506" from "0001-02-03_04:05:06";
			*  convert "00010203040506007" from "0001-02-03_04:05:06_007";
			*  convert "00010203040506007008" from "0001-02-03_04:05:06_007:008";
			*/
			GPCHR_NULLSTRPTR_RET(pSrc, GAIA::False);
			GPCHR_NULL_RET(pDst, GAIA::False);
			GAIA::SIZE sLen = GAIA::ALGO::strlen(pSrc);
			if(sLen != 10 && sLen != 16 && sLen != 19 && sLen != 23 && sLen != 27 && sLen < 27)
			{
				GAIA_AST(GAIA::ALWAYSFALSE);
				return GAIA::False;
			}
			if(sLen >= 10)
			{
				GAIA::ALGO::strcpy(pDst, pSrc, 4);
				pDst += 4;
				pSrc += 4;
				++pSrc;
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
				++pSrc;
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
			}
			if(sLen >= 16)
			{
				++pSrc;
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
				++pSrc;
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
			}
			if(sLen >= 19)
			{
				++pSrc;
				GAIA::ALGO::strcpy(pDst, pSrc, 2);
				pDst += 2;
				pSrc += 2;
			}
			if(sLen >= 23)
			{
				++pSrc;
				GAIA::ALGO::strcpy(pDst, pSrc, 3);
				pDst += 3;
				pSrc += 3;
			}
			if(sLen >= 27)
			{
				++pSrc;
				GAIA::ALGO::strcpy(pDst, pSrc, 3);
				pDst += 3;
				pSrc += 3;
			}
			*pDst = '\0';
			return GAIA::True;
		}
		class Time : public GAIA::Entity
		{
		public:
			GINL Time(){}
			GINL Time(const Time& src){this->operator = (src);}
			GINL Time(const GAIA::N64& src){this->operator = (src);}
			template<typename _ParamDataType> Time(const _ParamDataType* psz){this->operator = (psz);}
			GINL GAIA::BL check() const{return !(y == 0 && mo == 0 && d == 0 && h == 0 && mi == 0 && sec == 0 && msec == 0 && usec == 0);}
			GINL GAIA::GVOID reset(){y = mo = d = h = mi = sec = msec = usec = 0;}
			GINL GAIA::BL isvalid() const
			{
				if(y < 0)
					return GAIA::False;
				if(mo < 1 || mo > 12)
					return GAIA::False;
				if(d < 1 || d > GAIA::TIME::monthdays(y, mo))
					return GAIA::False;
				if(h < 0 || h > 23)
					return GAIA::False;
				if(mi < 0 || mi > 59)
					return GAIA::False;
				if(sec < 0 || sec > 59)
					return GAIA::False;
				if(msec < 0 || msec > 999)
					return GAIA::False;
				if(usec < 0 || usec > 999)
					return GAIA::False;
				return GAIA::True;
			}
			GINL Time& operator = (const Time& src){GAIA_AST(&src != this); y = src.y; mo = src.mo; d = src.d; h = src.h; mi = src.mi; sec = src.sec; msec = src.msec; usec = src.usec; return *this;}
			GINL Time& operator = (const GAIA::N64& src){this->usecond(src); return *this;}
			template<typename _ParamDataType> Time& operator = (const _ParamDataType* psz){this->from(psz); return *this;}
			GINL GAIA::BL operator == (const Time& src) const{return y == src.y && mo == src.mo && d == src.d && h == src.h && mi == src.mi && sec == src.sec && msec == src.msec && usec == src.usec;}
			GINL GAIA::BL operator != (const Time& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const Time& src) const
			{
				if(y > src.y)
					return GAIA::True;
				else if(y < src.y)
					return GAIA::False;
				if(mo > src.mo)
					return GAIA::True;
				else if(mo < src.mo)
					return GAIA::False;
				if(d > src.d)
					return GAIA::True;
				else if(d < src.d)
					return GAIA::False;
				if(h > src.h)
					return GAIA::True;
				else if(h < src.h)
					return GAIA::False;
				if(mi > src.mi)
					return GAIA::True;
				else if(mi < src.mi)
					return GAIA::False;
				if(sec > src.sec)
					return GAIA::True;
				else if(sec < src.sec)
					return GAIA::False;
				if(msec > src.msec)
					return GAIA::True;
				else if(msec < src.msec)
					return GAIA::False;
				if(usec >= src.usec)
					return GAIA::True;
				else
					return GAIA::False;
			}
			GINL GAIA::BL operator <= (const Time& src) const
			{
				if(y < src.y)
					return GAIA::True;
				else if(y > src.y)
					return GAIA::False;
				if(mo < src.mo)
					return GAIA::True;
				else if(mo > src.mo)
					return GAIA::False;
				if(d < src.d)
					return GAIA::True;
				else if(d > src.d)
					return GAIA::False;
				if(h < src.h)
					return GAIA::True;
				else if(h > src.h)
					return GAIA::False;
				if(mi < src.mi)
					return GAIA::True;
				else if(mi > src.mi)
					return GAIA::False;
				if(sec < src.sec)
					return GAIA::True;
				else if(sec > src.sec)
					return GAIA::False;
				if(msec < src.msec)
					return GAIA::True;
				else if(msec > src.msec)
					return GAIA::False;
				if(usec <= src.usec)
					return GAIA::True;
				else
					return GAIA::False;
			}
			GINL GAIA::BL operator > (const Time& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const Time& src) const{return !this->operator >= (src);}
			template<typename _ParamDataType> GAIA::BL operator == (const _ParamDataType* psz) const{GAIA::TIME::Time t; t.from(psz); return (*this) == t;}
			template<typename _ParamDataType> GAIA::BL operator != (const _ParamDataType* psz) const{GAIA::TIME::Time t; t.from(psz); return (*this) != t;}
			template<typename _ParamDataType> GAIA::BL operator >= (const _ParamDataType* psz) const{GAIA::TIME::Time t; t.from(psz); return (*this) >= t;}
			template<typename _ParamDataType> GAIA::BL operator <= (const _ParamDataType* psz) const{GAIA::TIME::Time t; t.from(psz); return (*this) <= t;}
			template<typename _ParamDataType> GAIA::BL operator > (const _ParamDataType* psz) const{GAIA::TIME::Time t; t.from(psz); return (*this) > t;}
			template<typename _ParamDataType> GAIA::BL operator < (const _ParamDataType* psz) const{GAIA::TIME::Time t; t.from(psz); return (*this) < t;}
			GINL GAIA::BL operator == (const GAIA::N64& src) const{GAIA::TIME::Time t = src; return (*this) == t;}
			GINL GAIA::BL operator != (const GAIA::N64& src) const{GAIA::TIME::Time t = src; return (*this) != t;}
			GINL GAIA::BL operator >= (const GAIA::N64& src) const{GAIA::TIME::Time t = src; return (*this) >= t;}
			GINL GAIA::BL operator <= (const GAIA::N64& src) const{GAIA::TIME::Time t = src; return (*this) <= t;}
			GINL GAIA::BL operator > (const GAIA::N64& src) const{GAIA::TIME::Time t = src; return (*this) > t;}
			GINL GAIA::BL operator < (const GAIA::N64& src) const{GAIA::TIME::Time t = src; return (*this) < t;}
			GINL Time operator + (const GAIA::N64& src) const
			{
				Time ret = *this;
				ret += src;
				return ret;
			}
			GINL Time operator - (const GAIA::N64& src) const
			{
				Time ret = *this;
				ret -= src;
				return ret;
			}
			GINL Time& operator += (const GAIA::N64& src)
			{
				GAIA::N64 n = this->usecond();
				n += src;
				this->usecond(n);
				return *this;
			}
			GINL Time& operator -= (const GAIA::N64& src)
			{
				GAIA::N64 n = this->usecond();
				n -= src;
				this->usecond(n);
				return *this;
			}
			GINL GAIA::GVOID systime();
			GINL operator GAIA::N64() const{return this->usecond();}
			GINL GAIA::N64 year() const{return y;}
			GINL GAIA::N64 month() const{return this->year() * 12 + mo - 1;}
			GINL GAIA::N64 day() const{return y * 365 + y / 4 + ((y % 4 == 0) ? 0 : 1) + GAIA::TIME::monthdaysall(y, mo) + d - 1;}
			GINL GAIA::N64 hour() const{return this->day() * 24 + h;}
			GINL GAIA::N64 minute() const{return this->hour() * 60 + mi;}
			GINL GAIA::N64 second() const{return this->minute() * 60 + sec;}
			GINL GAIA::N64 msecond() const{return this->second() * 1000 + msec;}
			GINL GAIA::N64 usecond() const{return this->msecond() * 1000 + usec;}
			GINL GAIA::GVOID year(GAIA::N64 year){y = year; mo = d = 1; h = mi = sec = msec = usec = 0;}
			GINL GAIA::GVOID month(GAIA::N64 month){y = month / 12; mo = month % 12 + 1; d = 1; h = mi = sec = msec = usec = 0;}
			GINL GAIA::GVOID day(GAIA::N64 day)
			{
				static const GAIA::N64 DAYS4YEAR = 4 * 365 + 1;
				static const GAIA::N64 ONEYEARDAYS = 366;
				static const GAIA::N64 TWOYEARDAYS = ONEYEARDAYS + 365;
				static const GAIA::N64 THREEYEARDAYS = TWOYEARDAYS + 365;
				static const GAIA::N64 FOURYEARDAYS = THREEYEARDAYS + 365;
				y = day / DAYS4YEAR * 4;
				day %= DAYS4YEAR;
				if(day < ONEYEARDAYS){}
				else if(day < TWOYEARDAYS)
				{
					day -= ONEYEARDAYS;
					y += 1;
				}
				else if(day < THREEYEARDAYS)
				{
					day -= TWOYEARDAYS;
					y += 2;
				}
				else
				{
					day -= THREEYEARDAYS;
					y += 3;
				}
				for(GAIA::SIZE x = 1; x <= 12; ++x)
				{
					if(day < GAIA::TIME::monthdaysall(y, x + 1))
					{
						day -= GAIA::TIME::monthdaysall(y, x);
						mo = x;
						break;
					}
					GAIA_AST(x != 12);
				}
				d = day + 1;
				h = mi = sec = msec = usec = 0;
			}
			GINL GAIA::GVOID hour(GAIA::N64 hour)
			{
				this->day(hour / 24);
				h = hour % 24;
				mi = sec = msec = usec = 0;
			}
			GINL GAIA::GVOID minute(GAIA::N64 minute)
			{
				this->hour(minute / 60);
				mi = minute % 60;
				sec = msec = usec = 0;
			}
			GINL GAIA::GVOID second(GAIA::N64 second)
			{
				this->minute(second / 60);
				sec = second % 60;
				msec = usec = 0;
			}
			GINL GAIA::GVOID msecond(GAIA::N64 msecond)
			{
				this->second(msecond / 1000);
				msec = msecond % 1000;
				usec = 0;
			}
			GINL GAIA::GVOID usecond(GAIA::N64 usecond)
			{
				this->msecond(usecond / 1000);
				usec = usecond % 1000;
			}
			GINL GAIA::GVOID dayinc(){(*this) += GSCAST(GAIA::N64)(24) * 60 * 60 * 1000 * 1000;}
			GINL GAIA::GVOID daydec(){(*this) -= GSCAST(GAIA::N64)(24) * 60 * 60 * 1000 * 1000;}
			template<typename _ParamDataType> GAIA::GVOID from(const _ParamDataType* psz)
			{
				GPCHR_NULLSTRPTR(psz);
				GAIA::SIZE sLen = GAIA::ALGO::strlen(psz);
				if(sLen != 8 && sLen != 12 && sLen != 14 && sLen != 17 && sLen != 20 && sLen < 20)
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					return;
				}
				this->reset();
				_ParamDataType temp[5];
				if(sLen >= 8)
				{
					GAIA::ALGO::strcpy(temp, psz + 0, 4);
					y = GAIA::ALGO::string_autocast(temp);
					GAIA::ALGO::strcpy(temp, psz + 4, 2);
					mo = GAIA::ALGO::string_autocast(temp);
					GAIA::ALGO::strcpy(temp, psz + 6, 2);
					d = GAIA::ALGO::string_autocast(temp);
				}
				if(sLen >= 12)
				{
					GAIA::ALGO::strcpy(temp, psz + 8, 2);
					h = GAIA::ALGO::string_autocast(temp);
					GAIA::ALGO::strcpy(temp, psz + 10, 2);
					mi = GAIA::ALGO::string_autocast(temp);
				}
				if(sLen >= 14)
				{
					GAIA::ALGO::strcpy(temp, psz + 12, 2);
					sec = GAIA::ALGO::string_autocast(temp);
				}
				if(sLen >= 17)
				{
					GAIA::ALGO::strcpy(temp, psz + 14, 3);
					msec = GAIA::ALGO::string_autocast(temp);
				}
				if(sLen >= 20)
				{
					GAIA::ALGO::strcpy(temp, psz + 17, 3);
					usec = GAIA::ALGO::string_autocast(temp);
				}
			}
			template<typename _ParamDataType> GAIA::GVOID to(_ParamDataType* psz) const
			{
				_ParamDataType temp[32];

				GAIA::ALGO::value_cast(y, temp, 32);
				GAIA::ALGO::strleftfill(temp, '0', 4);
				GAIA::ALGO::strcpy(psz, temp);
				psz += 4;

				GAIA::ALGO::value_cast(mo, temp, 32);
				GAIA::ALGO::strleftfill(temp, '0', 2);
				GAIA::ALGO::strcpy(psz, temp);
				psz += 2;

				GAIA::ALGO::value_cast(d, temp, 32);
				GAIA::ALGO::strleftfill(temp, '0', 2);
				GAIA::ALGO::strcpy(psz, temp);
				psz += 2;

				GAIA::ALGO::value_cast(h, temp, 32);
				GAIA::ALGO::strleftfill(temp, '0', 2);
				GAIA::ALGO::strcpy(psz, temp);
				psz += 2;

				GAIA::ALGO::value_cast(mi, temp, 32);
				GAIA::ALGO::strleftfill(temp, '0', 2);
				GAIA::ALGO::strcpy(psz, temp);
				psz += 2;

				GAIA::ALGO::value_cast(sec, temp, 32);
				GAIA::ALGO::strleftfill(temp, '0', 2);
				GAIA::ALGO::strcpy(psz, temp);
				psz += 2;

				GAIA::ALGO::value_cast(msec, temp, 32);
				GAIA::ALGO::strleftfill(temp, '0', 3);
				GAIA::ALGO::strcpy(psz, temp);
				psz += 3;

				GAIA::ALGO::value_cast(usec, temp, 32);
				GAIA::ALGO::strleftfill(temp, '0', 3);
				GAIA::ALGO::strcpy(psz, temp);
				psz += 3;

				*psz = '\0';
			}

			GINL GAIA::GVOID from(const GAIA::U64& src)
			{
				const GAIA::U32* p = (const GAIA::U32*)&src;
				y = (p[0] >> 14) & 0x00003FFF;
				mo = (p[0] >> 10) & 0x0000000F;
				d = (p[0] >> 5) & 0x0000001F;
				h = p[0] & 0x0000001F;
				mi = (p[1] >> 26) & 0x0000003F;
				sec = (p[1] >> 20) & 0x0000003F;
				msec = (p[1] >> 10) & 0x000003FF;
				usec = p[1] & 0x000003FF;
			}
			GINL GAIA::GVOID to(GAIA::U64& u) const
			{
				GAIA::U32* p = (GAIA::U32*)&u;
				p[0] = (GSCAST(GAIA::U32)(y) << 14) & 0xFFFFC000;
				p[0] |= (GSCAST(GAIA::U32)(mo) << 10) & 0x00003C00;
				p[0] |= (GSCAST(GAIA::U32)(d) << 5) & 0x000003E0;
				p[0] |= (GSCAST(GAIA::U32)(h)) & 0x0000001F;
				p[1] = (GSCAST(GAIA::U32)(mi) << 26) & 0xFC000000;
				p[1] |= (GSCAST(GAIA::U32)(sec) << 20) & 0x03F00000;
				p[1] |= (GSCAST(GAIA::U32)(msec) << 10) & 0x000FFC00;
				p[1] |= (GSCAST(GAIA::U32)(usec)) & 0x000003FF;
			}
		public:
			GAIA::N16 y; 	// Year.4
			GAIA::N8 mo; 	// Month.2
			GAIA::N8 d; 	// Day.2
			GAIA::N8 h; 	// Hour.2
			GAIA::N8 mi; 	// Minute.2
			GAIA::N8 sec; 	// Second.2
			GAIA::N16 msec; // MilliSecond.3
			GAIA::N16 usec; // MicroSecond.3
		};
	};
};

#include "gaia_time_indp.h"

#endif
