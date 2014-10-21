#ifndef		__GAIA_TIME_H__
#define		__GAIA_TIME_H__

namespace GAIA
{
	namespace TIME
	{

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
		class Time : public GAIA::Entity
		{
		public:
			GINL Time(){}
			GINL Time(const Time& src){this->operator = (src);}
			GINL Time(const GAIA::U64& src){this->operator = (src);}
			GINL GAIA::BL empty() const{return y == 0 && mo == 0 && d == 0 && h == 0 && mi == 0 && sec == 0 && msec == 0 && usec == 0;}
			GINL GAIA::GVOID clear(){y = mo = d = h = mi = sec = msec = usec = 0;}
			GINL Time& operator = (const Time& src){GAIA_AST(&src != this); y = src.y; mo = src.mo; d = src.d; h = src.h; mi = src.mi; sec = src.sec; msec = src.msec; usec = src.usec; return *this;}
			GINL Time& operator = (const GAIA::U64& src)
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
				return *this;
			}
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
			GINL Time operator + (const Time& src) const
			{
				Time ret;
				return ret;
			}
			GINL Time operator - (const Time& src) const
			{
				Time ret;
				return ret;
			}
			GINL const Time& operator += (const Time& src)
			{
				return *this;
			}
			GINL const Time& operator -= (const Time& src)
			{
				return *this;
			}
			GINL GAIA::GVOID systime();
			GINL operator GAIA::U64() const
			{
				GAIA::U64 ret;
				GAIA::U32* p = (GAIA::U32*)&ret;
				p[0] = (GSCAST(GAIA::U32)(y) << 14) & 0xFFFFC000;
				p[0] |= (GSCAST(GAIA::U32)(mo) << 10) & 0x00003C00;
				p[0] |= (GSCAST(GAIA::U32)(d) << 5) & 0x000003E0;
				p[0] |= (GSCAST(GAIA::U32)(h)) & 0x0000001F;
				p[1] = (GSCAST(GAIA::U32)(mi) << 26) & 0xFC000000;
				p[1] |= (GSCAST(GAIA::U32)(sec) << 20) & 0x03F00000;
				p[1] |= (GSCAST(GAIA::U32)(msec) << 10) & 0x000FFC00;
				p[1] |= (GSCAST(GAIA::U32)(usec)) & 0x000003FF;
				return ret;
			}
			GINL GAIA::U64 toyear() const{return y;}
			GINL GAIA::U64 tomonth() const{return this->toyear() * 12 + mo;}
			GINL GAIA::U64 today() const{return this->tomonth() * 30 + d;}
			GINL GAIA::U64 tohour() const{return this->today() * 24 + h;}
			GINL GAIA::U64 tominute() const{return this->tohour() * 60 + mi;}
			GINL GAIA::U64 tosecond() const{return this->tominute() * 60 + sec;}
			GINL GAIA::U64 tomsecond() const{return this->tosecond() * 1000 + msec;}
			GINL GAIA::U64 tousecond() const{return this->tomsecond() * 1000 + usec;}
		public:
			GAIA::N16 y; 	// Year.
			GAIA::N8 mo; 	// Month.
			GAIA::N8 d; 	// Day.
			GAIA::N8 h; 	// Hour.
			GAIA::N8 mi; 	// Minute.
			GAIA::N8 sec; 	// Second.
			GAIA::N16 msec; // MilliSecond.
			GAIA::N16 usec; // MicroSecond.
		};
		GINL GAIA::N32 yeardays(GAIA::N16 year)
		{
			if(year % 4 == 0 || year % 100 == 0 || year % 400 == 0)
				return 366;
			return 365;
		}
		GINL GAIA::N32 monthdays(GAIA::N32 year, GAIA::N32 month)
		{
			static const GAIA::N32 DAYS[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			if(month == 2)
			{
				if(year % 4 == 0 || year % 100 == 0 || year % 400 == 0)
					return 29;
				else
					return 28;
			}
			else
				return DAYS[month];
		}
		GINL GAIA::U64 clock_time(); // return value is micro second from 1970.1.1.
		GINL GAIA::U64 tick_time(); // return value is micro second from process startuped.
	};
};

#include "gaia_time_indp.h"

#endif
