#ifndef		__GAIA_ALGORITHM_STRING_H__
#define		__GAIA_ALGORITHM_STRING_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _DataType> _DataType tolower(const _DataType& c){if(c >= 'A' && c <= 'Z') return c - 'A' + 'a'; return c;}
		template <typename _DataType> _DataType toupper(const _DataType& c){if(c >= 'a' && c <= 'z') return c - 'a' + 'A'; return c;}
		template <typename _DataType> _DataType* tolower(_DataType* p){GAIA_ASSERT(p != GNULL); _DataType* ret = p; while(*p != 0){*p = GAIA::ALGORITHM::tolower(*p);p++;} return ret;}
		template <typename _DataType> _DataType* toupper(_DataType* p){GAIA_ASSERT(p != GNULL); _DataType* ret = p; while(*p != 0){*p = GAIA::ALGORITHM::toupper(*p);p++;} return ret;}
		template <typename _DataType> GAIA::BL islower(const _DataType& c){if(c >= 'a' && c <= 'z') return GAIA::True; return GAIA::False;}
		template <typename _DataType> GAIA::BL isupper(const _DataType& c){if(c >= 'A' && c <= 'Z') return GAIA::True; return GAIA::False;}
		template <typename _DataType> GAIA::BL isexistlower(const _DataType* p){GAIA_ASSERT(p != GNULL); while(*p != 0){if(islower(*p)) return GAIA::True; p++;} return GAIA::False;}
		template <typename _DataType> GAIA::BL isexistupper(const _DataType* p){GAIA_ASSERT(p != GNULL); while(*p != 0){if(isupper(*p)) return GAIA::True; p++;} return GAIA::False;}
		template <typename _DataType> GAIA::BL isalllower(const _DataType* p){GAIA_ASSERT(p != GNULL); while(*p != 0){if(!islower(*p)) return GAIA::False; p++;} return GAIA::True;}
		template <typename _DataType> GAIA::BL isallupper(const _DataType* p){GAIA_ASSERT(p != GNULL); while(*p != 0){if(!isupper(*p)) return GAIA::False; p++;} return GAIA::True;}
		template <typename _DataType> GAIA::BL isdigit(const _DataType& c){if(c >= '0' && c <= '9') return GAIA::True; return GAIA::False;}
		template <typename _DataType> GAIA::BL isalpha(const _DataType& c){if(c < 'A' || c > 'z') return GAIA::False; if(c <= 'Z' || c >= 'a') return GAIA::True; return GAIA::False;}
		template <typename _DataType> GAIA::BL ispunctuation(const _DataType& c){if(c > ' ' && !GAIA::ALGORITHM::isalpha(c) && !GAIA::ALGORITHM::isdigit(c) && c < 0xFF) return GAIA::True; return GAIA::False;}
		template <typename _DataType> GAIA::BL isspecial(const _DataType& c){if(c < ' ') return GAIA::True; return GAIA::False;}
		template <typename _DataType> GAIA::UM strlen(const _DataType* p){GAIA_ASSERT(p != GNULL); GAIA::UM ret = 0; while(p[ret] != 0) ret++; return ret;}
		template <typename _DataType> _DataType* strcpy(_DataType* dst, const _DataType* src)
		{
			GAIA_ASSERT(dst != GNULL);
			GAIA_ASSERT(src != GNULL);
			_DataType* ret = dst;
			while(*src != 0)
			{
				*dst = *src;
				++dst;
				++src;
			}
			*dst = 0;
			return ret;
		}
		template <typename _DataType> _DataType* strcat(_DataType* dst, const _DataType* src)
		{
			GAIA_ASSERT(dst != GNULL);
			GAIA_ASSERT(src != GNULL);
			_DataType* ret = dst;
			dst = dst + GAIA::ALGORITHM::strlen(dst);
			GAIA::ALGORITHM::strcpy(dst, src);
			return ret;
		}
		template <typename _DataType> GAIA::N32 strcmp(const _DataType* p1, const _DataType* p2)
		{
			GAIA_ASSERT(dst != GNULL);
			GAIA_ASSERT(src != GNULL);
			while(GAIA::ALWAYSTRUE)
			{
				if(*p1 < *p2)
					return -1;
				else if(*p1 > *p2)
					return +1;
				else
				{
					if(*p1 == 0)
						return 0;
					++p1;
					++p2;
				}
			}
			return 0;
		}
		template <typename _DataType> GAIA::N32 stricmp(const _DataType* p1, const _DataType* p2)
		{
			GAIA_ASSERT(dst != GNULL);
			GAIA_ASSERT(src != GNULL);
			while(GAIA::ALWAYSTRUE)
			{
				_DataType c1 = tolower(*p1);
				_DataType c2 = tolower(*p2);
				if(c1 < c2)
					return -1;
				else if(c1 > c2)
					return +1;
				else
				{
					if(c1 == 0)
						return 0;
					++p1;
					++p2;
				}
			}
			return 0;
		}
		template <typename _DataType> _DataType* strstr(const _DataType* p1, const _DataType* p2)
		{
			GAIA_ASSERT(p1 != GNULL);
			GAIA_ASSERT(p2 != GNULL);
			while(*p1 != 0)
			{
				const _DataType* po = p1;
				const _DataType* p = p2;
				while(*po != 0 && *p != 0)
				{
					if(*p != *po)
						break;
					++po;
					++p;
				}
				if(*p == 0)
					return (_DataType*)p1;
				++p1;
			}
			return GNULL;
		}
		template <typename _DataType> _DataType* stristr(const _DataType* p1, const _DataType* p2)
		{
			GAIA_ASSERT(p1 != GNULL);
			GAIA_ASSERT(p2 != GNULL);
			while(*p1 != 0)
			{
				const _DataType* po = p1;
				const _DataType* p = p2;
				while(*po != 0 && *p != 0)
				{
					if(tolower(*p) != tolower(*po))
						break;
					++po;
					++p;
				}
				if(*p == 0)
					return (_DataType*)p1;
				++p1;
			}
			return GNULL;
		}
		template <typename _DataType> _DataType* strmch(const _DataType* p1, const _DataType* p2)
		{
			GAIA_ASSERT(p1 != GNULL);
			GAIA_ASSERT(p2 != GNULL);

			const _DataType* p = p1;
			while(*p != 0 && *p2 != 0)
			{
				if(*p2 != *p)
					return GNULL;
				++p;
				++p2;
			}
			if(*p2 == 0)
				return (_DataType*)p1;
			return GNULL;
		}
		template <typename _DataType> _DataType* strimch(const _DataType* p1, const _DataType* p2)
		{
			GAIA_ASSERT(p1 != GNULL);
			GAIA_ASSERT(p2 != GNULL);

			const _DataType* p = p1;
			while(tolower(*p) != 0 && tolower(*p2) != 0)
			{
				if(*p2 != *p)
					return GNULL;
				++p;
				++p2;
			}
			if(*p2 == 0)
				return (_DataType*)p1;
			return GNULL;
		}
	};
};

#endif
