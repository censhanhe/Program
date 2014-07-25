#ifndef		__GAIA_ALGORITHM_STRING_H__
#define		__GAIA_ALGORITHM_STRING_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType> GINL _DataType tolower(const _DataType& c){if(c >= 'A' && c <= 'Z') return c - 'A' + 'a'; return c;}
		template<typename _DataType> GINL _DataType toupper(const _DataType& c){if(c >= 'a' && c <= 'z') return c - 'a' + 'A'; return c;}
		template<typename _DataType> GINL _DataType tolowers(_DataType p){GAIA_AST(!!p); _DataType ret = p; while(*p != '\0'){*p = GAIA::ALGORITHM::tolower(*p);p++;} return ret;}
		template<typename _DataType> GINL _DataType touppers(_DataType p){GAIA_AST(!!p); _DataType ret = p; while(*p != '\0'){*p = GAIA::ALGORITHM::toupper(*p);p++;} return ret;}
		template<typename _DataType> GINL GAIA::BL islower(const _DataType& c){return c >= 'a' && c <= 'z';}
		template<typename _DataType> GINL GAIA::BL isupper(const _DataType& c){return c >= 'A' && c <= 'Z';}
		template<typename _DataType> GINL GAIA::BL isexistlower(_DataType p){GAIA_AST(!!p); while(*p != '\0'){if(GAIA::ALGORITHM::islower(*p)) return GAIA::True; p++;} return GAIA::False;}
		template<typename _DataType> GINL GAIA::BL isexistupper(_DataType p){GAIA_AST(!!p); while(*p != '\0'){if(GAIA::ALGORITHM::isupper(*p)) return GAIA::True; p++;} return GAIA::False;}
		template<typename _DataType> GINL GAIA::BL isalllower(_DataType p){GAIA_AST(!!p); while(*p != '\0'){if(!GAIA::ALGORITHM::islower(*p)) return GAIA::False; p++;} return GAIA::True;}
		template<typename _DataType> GINL GAIA::BL isallupper(_DataType p){GAIA_AST(!!p); while(*p != '\0'){if(!GAIA::ALGORITHM::isupper(*p)) return GAIA::False; p++;} return GAIA::True;}
		template<typename _DataType> GINL GAIA::BL isdigit(const _DataType& c){return c >= '0' && c <= '9';}
		template<typename _DataType> GINL GAIA::BL isalpha(const _DataType& c){if(c < 'A' || c > 'z') return GAIA::False; return c <= 'Z' || c >= 'a';}
		template<typename _DataType> GINL GAIA::BL ispunctuation(const _DataType& c){return c > ' ' && !GAIA::ALGORITHM::isalpha(c) && !GAIA::ALGORITHM::isdigit(c) && c < 0xFF;}
		template<typename _DataType> GINL GAIA::BL isspecial(const _DataType& c){return c < ' ';}
		template<typename _DataType> GINL GAIA::BL isexistansi(_DataType p)
		{
			while(*p != '\0')
			{
				if(*p < 128)
					return GAIA::True;
				++p;
			}
			return GAIA::False;
		}
		template<typename _DataType> GINL GAIA::BL isallansi(_DataType p)
		{
			while(*p != '\0')
			{
				if(*p >= 128)
					return GAIA::False;
				++p;
			}
			return GAIA::True;
		}
		template<typename _DataType> GINL GAIA::BL stremp(_DataType p)
		{
			if(p == GNULL || *p == '\0')
				return GAIA::True;
			return GAIA::False;
		}
		template<typename _DataType> GINL _DataType strend(_DataType p)
		{
			while(*p != '\0') ++p;
			return p;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strch(_DataType1 p, const _DataType2& c)
		{
			while(*p != '\0')
			{
				if(*p == c)
					return p;
				++p;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strich(_DataType1 p, const _DataType2& c)
		{
			while(*p != '\0')
			{
				if(GAIA::ALGORITHM::tolower(*p) == GAIA::ALGORITHM::tolower(c))
					return p;
				++p;
			}
			return GNULL;
		}
		template<typename _DataType> GINL GAIA::SIZE strlen(_DataType p){GAIA_AST(!!p); GAIA::SIZE ret = 0; while(p[ret] != '\0') ret++; return ret;}
		template<typename _DataType1, typename _DataType2> GINL GAIA::SIZE strcnt(_DataType1 p, const _DataType2& key)
		{
			GAIA::SIZE ret = 0;
			while(*p != '\0')
			{
				if(*p == key)
					++ret;
				++p;
			}
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strcpy(_DataType1 pDst, _DataType2 pSrc)
		{
			GAIA_AST(!!pDst);
			GAIA_AST(!!pSrc);
			_DataType1 ret = pDst;
			while(*pSrc != '\0')
			{
				*pDst = *pSrc;
				++pDst;
				++pSrc;
			}
			*pDst = '\0';
			return ret;
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GINL _DataType1 strcpy(_DataType1 pDst, _DataType2 pSrc, _SizeType size)
		{
			GAIA_AST(!!pDst);
			GAIA_AST(!!pSrc);
			GAIA_AST(size != 0);
			_DataType1 ret = pDst;
			while(size != 0)
			{
				*pDst = *pSrc;
				++pDst;
				++pSrc;
				--size;
			}
			*pDst = '\0';
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strcat(_DataType1 pDst, _DataType2 pSrc)
		{
			GAIA_AST(!!pDst);
			GAIA_AST(!!pSrc);
			_DataType1 ret = pDst;
			pDst = pDst + GAIA::ALGORITHM::strlen(pDst);
			GAIA::ALGORITHM::strcpy(pDst, pSrc);
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 strcmp(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			while(GAIA::ALWAYSTRUE)
			{
				if(*p1 < *p2)
					return -1;
				else if(*p1 > *p2)
					return +1;
				else
				{
					if(*p1 == '\0')
						return 0;
					++p1;
					++p2;
				}
			}
			return 0;
		}
		template<typename _DataType1, typename _DataType2> GINL GAIA::N32 stricmp(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			while(GAIA::ALWAYSTRUE)
			{
				if(GAIA::ALGORITHM::tolower(*p1) < GAIA::ALGORITHM::tolower(*p2))
					return -1;
				else if(GAIA::ALGORITHM::tolower(*p1) > GAIA::ALGORITHM::tolower(*p2))
					return +1;
				else
				{
					if(GAIA::ALGORITHM::tolower(*p1) == '\0')
						return 0;
					++p1;
					++p2;
				}
			}
			return 0;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strstr(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			while(*p1 != '\0')
			{
				_DataType1 po = p1;
				_DataType2 p = p2;
				while(*po != '\0' && *p != '\0')
				{
					if(*p != *po)
						break;
					++po;
					++p;
				}
				if(*p == '\0')
					return p1;
				++p1;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 stristr(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			while(*p1 != '\0')
			{
				_DataType1 po = p1;
				_DataType2 p = p2;
				while(*po != '\0' && *p != '\0')
				{
					if(GAIA::ALGORITHM::tolower(*p) != GAIA::ALGORITHM::tolower(*po))
						break;
					++po;
					++p;
				}
				if(*p == '\0')
					return p1;
				++p1;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1* strwrd(const _DataType1* p1, const _DataType2* p2)
		{
			const _DataType1* p = p1;
			while((p = GAIA::ALGORITHM::strstr(p, p2)) != GNULL)
			{
				if(p != p1)
				{
					_DataType1 t = *(p - 1);
					if(GAIA::ALGORITHM::isalpha(t) || GAIA::ALGORITHM::isdigit(t))
					{
						++p;
						continue;
					}
				}
				_DataType1 t = *(p + GAIA::ALGORITHM::strlen(p2));
				if(GAIA::ALGORITHM::isalpha(t) || GAIA::ALGORITHM::isdigit(t))
				{
					++p;
					continue;
				}
				return const_cast<_DataType1*>(p);
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1* striwrd(const _DataType1* p1, const _DataType2* p2)
		{
			const _DataType1* p = p1;
			while((p = GAIA::ALGORITHM::stristr(p, p2)) != GNULL)
			{
				if(p != p1)
				{
					_DataType1 t = *(p - 1);
					if(GAIA::ALGORITHM::isalpha(t) || GAIA::ALGORITHM::isdigit(t))
					{
						++p;
						continue;
					}
				}
				_DataType1 t = *(p + GAIA::ALGORITHM::strlen(p2));
				if(GAIA::ALGORITHM::isalpha(t) || GAIA::ALGORITHM::isdigit(t))
				{
					++p;
					continue;
				}
				return const_cast<_DataType1*>(p);
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strmch(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);

			_DataType1 p = p1;
			while(*p != '\0' && *p2 != '\0')
			{
				if(*p2 != *p)
					return GNULL;
				++p;
				++p2;
			}
			if(*p2 == '\0')
				return p1;
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strimch(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);

			_DataType1 p = p1;
			while(GAIA::ALGORITHM::tolower(*p) != '\0' && GAIA::ALGORITHM::tolower(*p2) != '\0')
			{
				if(*p2 != *p)
					return GNULL;
				++p;
				++p2;
			}
			if(*p2 == '\0')
				return p1;
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strdrop(_DataType1 p, _DataType2 pKeys)
		{
			_DataType1 p1 = p;
			while(*p1 != '\0')
			{
				_DataType2 p2 = pKeys;
				while(*p2 != '\0')
				{
					if(*p1 == *p2)
						return p1;
					++p2;
				}
				++p1;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 stridrop(_DataType1 p, _DataType2 pKeys)
		{
			_DataType1 p1 = p;
			while(*p1 != '\0')
			{
				_DataType2 p2 = pKeys;
				while(*p2 != '\0')
				{
					if(GAIA::ALGORITHM::tolower(*p1) == GAIA::ALGORITHM::tolower(*p2))
						return p1;
					++p2;
				}
				++p1;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 strdropr(_DataType1 p, _DataType2 pKeys)
		{
			_DataType1 p1 = GAIA::ALGORITHM::strend(p);
			while(p1 > p)
			{
				_DataType2 p2 = pKeys;
				while(*p2 != '\0')
				{
					if(*p1 == *p2)
					{
						*(p1 + 1) = '\0';
						return p1;
					}
					++p2;
				}
				--p1;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1 stridropr(_DataType1 p, _DataType2 pKeys)
		{
			_DataType1 p1 = GAIA::ALGORITHM::strend(p);
			while(p1 > p)
			{
				_DataType2 p2 = pKeys;
				while(*p2 != '\0')
				{
					if(GAIA::ALGORITHM::tolower(*p1) == GAIA::ALGORITHM::tolower(*p2))
					{
						*(p1 + 1) = '\0';
						return p1;
					}
					++p2;
				}
				--p1;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType strext(_DataType p)
		{
			_DataType pEnd = GAIA::ALGORITHM::strend(p);
			--pEnd;
			while(pEnd >= p)
			{
				if(*pEnd == '\\' || *pEnd == '/')
					return GNULL;
				if(*pEnd == '.')
				{
					if(pEnd[1] != '\0')
						return pEnd + 1;
				}
				--pEnd;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType strfilename(_DataType p)
		{
			_DataType pEnd = GAIA::ALGORITHM::strend(p);
			--pEnd;
			while(pEnd >= p)
			{
				if(*pEnd == '\\' || *pEnd == '/')
				{
					if(pEnd[1] != '\0')
						return pEnd + 1;
				}
				--pEnd;
			}
			return GNULL;
		}
		template<typename _SrcDataType, typename _DstDataType> GINL _DstDataType int2str(const _SrcDataType& src, _DstDataType pDst)
		{
			GAIA_AST(!!pDst);
			_SrcDataType tsrc = src;
			_DstDataType p = pDst;
			if(src < (_SrcDataType)0)
			{
				tsrc = -tsrc;
				*p = '-';
				++p;
			}
			while(tsrc > 0)
			{
				*p = (tsrc % 10 + '0');
				tsrc /= 10;
				++p;
			}
			if(p == pDst)
			{
				*p = '0';
				++p;
			}
			else
				GAIA::ALGORITHM::inverse(*pDst == '-' ? pDst + 1 : pDst, p - 1);
			*p = '\0';
			return p + 1;
		}
		template<typename _SrcDataType, typename _DstDataType> GINL _DstDataType real2str(const _SrcDataType& src, _DstDataType pDst)
		{
			GAIA_AST(!!pDst);
			GAIA::N64 left = (GAIA::N64)src;
			_SrcDataType right = src - (_SrcDataType)left;
			right = GAIA::MATH::xabs(right);
			while(right - (_SrcDataType)(GAIA::N64)right != 0)
				right *= 10.0F;
			_DstDataType p = GAIA::ALGORITHM::int2str(left, pDst);
			--p;
			*p = '.';
			++p;
			p = GAIA::ALGORITHM::int2str((GAIA::N64)right, p);
			return p;
		}
		template<typename _DstDataType, typename _SizeType> GINL _DstDataType hex2str(const GAIA::U8* pSrc, const _SizeType& size, _DstDataType pDst)
		{
			GAIA_AST(!!pSrc);
			GAIA_AST(!!pDst);
			GAIA_AST(size > 0);
			_SizeType sizet = size;
			_DstDataType p = pDst;
			while(sizet > 0)
			{
				// Calculate high 4 bit.
				GAIA::U8 u0 = ((*pSrc) >> 4) & 0x0F;
				if(u0 < 10)
					*p = '0' + u0;
				else
					*p = 'A' + u0 - 10;
				++p;

				// Calculate low 4 bit.
				GAIA::U8 u1 = (*pSrc) & 0x0F;
				if(u1 < 10)
					*p = '0' + u1;
				else
					*p = 'A' + u1 - 10;
				++p;

				// Combin.
				++pSrc;
				--sizet;
			}
			*p = '\0';
			return pDst;
		}
		template<typename _SrcDataType, typename _SizeType> GINL GAIA::U8* str2hex(_SrcDataType pSrc, const _SizeType& size, GAIA::U8* pDst)
		{
			GAIA_AST(!!pSrc);
			GAIA_AST(!!pDst);
			GAIA_AST(size > 0);
			GAIA_AST(size % 2 == 0);
			_SizeType sizet = size;
			GAIA::U8* p = pDst;
			while(sizet > 0)
			{
				// Calculate high 4 bit.
				GAIA::U8 u0;
				if(*pSrc >= '0' && *pSrc <= '9')
					u0 = *pSrc - '0';
				else if(*pSrc >= 'a' && *pSrc <= 'f')
					u0 = *pSrc - 'a' + 10;
				else if(*pSrc >= 'A' && *pSrc <= 'F')
					u0 = *pSrc - 'A' + 10;
				else
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					u0 = 0;
				}
				++pSrc;

				// Calculate low 4 bit.
				GAIA::U8 u1;
				if(*pSrc >= '0' && *pSrc <= '9')
					u1 = *pSrc - '0';
				else if(*pSrc >= 'a' && *pSrc <= 'f')
					u1 = *pSrc - 'a' + 10;
				else if(*pSrc >= 'A' && *pSrc <= 'F')
					u1 = *pSrc - 'A' + 10;
				else
				{
					GAIA_AST(GAIA::ALWAYSFALSE);
					u1 = 0;
				}
				++pSrc;

				// Combin.
				*p = (GAIA::U8)(u0 * 16 + u1);
				++p;
				--sizet;
			}
			return pDst;
		}
		template<typename _SrcDataType, typename _DstDataType> GINL _SrcDataType str2int(_SrcDataType pSrc, _DstDataType& dst)
		{
			GAIA_AST(!!pSrc);
			dst = 0;
			GAIA::BL bSign;
			if(*pSrc == '-')
			{
				bSign = GAIA::True;
				++pSrc;
			}
			else
				bSign = GAIA::False;
			while(*pSrc != '\0')
			{
				if(*pSrc < '0' || *pSrc > '9')
					break;
				dst = (_DstDataType)(dst * 10);
				dst = (_DstDataType)(dst + (*pSrc - '0'));
				++pSrc;
			}
			if(bSign)
				dst = 0 - dst;
			return pSrc;
		}
		template<typename _SrcDataType, typename _DstDataType> GINL _SrcDataType str2real(_SrcDataType pDst, _DstDataType& dst)
		{
			GAIA_AST(!!pDst);
			GAIA::BL bSign;
			if(*pDst == '-')
			{
				bSign = GAIA::True;
				++pDst;
			}
			else
				bSign = GAIA::False;
			_DstDataType left = 0;
			_DstDataType right = 0;
			_DstDataType right_dst;
			_DstDataType* pTarget = &left;
			while(*pDst != '\0')
			{
				if(*pDst < '0' || *pDst > '9')
					break;
				*pTarget *= 10;
				*pTarget += (*pDst - '0');
				++pDst;
			}
			if(*pDst == '.')
			{
				++pDst;
				_DstDataType right_div = 1;
				pTarget = &right;
				while(*pDst != '\0')
				{
					if(*pDst < '0' || *pDst > '9')
						break;
					*pTarget *= 10;
					right_div *= 10;
					*pTarget += (*pDst - '0');
					++pDst;
				}
				right_dst = *pTarget / right_div;
			}
			else
				right_dst = 0.0F;
			dst = left + right_dst;
			if(bSign)
				dst = -dst;
			return pDst;
		}
		template<typename _DataType> GINL GAIA::U32 strtype(_DataType p)
		{
			if(GAIA::ALGORITHM::stremp(p))
				return GAIA::STRING_TYPE_INVALID;

			/* Check up the string is RID. */
			GAIA::SIZE len = GAIA::ALGORITHM::strlen(p);
			if(len == sizeof(GAIA::X128) ||
				len == sizeof(GAIA::X128) * 2)
			{
				GAIA::BL bMatch = GAIA::True;
				_DataType pTemp = p;
				while(*pTemp != '\0')
				{
					if(*pTemp >= 'a' && *pTemp <= 'f' ||
						*pTemp >= 'A' && *pTemp <= 'F' ||
						*pTemp >= '0' && *pTemp <= '9'){}
					else
					{
						bMatch = GAIA::False;
						break;
					}
					++pTemp;
				}
				if(bMatch)
				{
					if(len == sizeof(GAIA::X128))
						return GAIA::STRING_TYPE_RID | GAIA::STRING_TYPE_RID64;
					else
						return GAIA::STRING_TYPE_RID | GAIA::STRING_TYPE_RID128;
				}
			}

			/* Check up the string is real. */
			{
				GAIA::BL bMatch = GAIA::True;
				GAIA::BL bExistPoint = GAIA::False;
				_DataType pTemp = p;
				while(*pTemp != '\0')
				{
					if((*pTemp == '.') ||
						(*pTemp >= '0' && *pTemp <= '9') ||
						(pTemp == p && (*pTemp == '-' || *pTemp == '+')) ||
						(pTemp[1] == '\0' && (*pTemp == 'f' || *pTemp == 'F')))
					{
						if(*pTemp == '.')
							bExistPoint = GAIA::True;
					}
					else
					{
						bMatch = GAIA::False;
						break;
					}
					++pTemp;
				}
				if(bMatch)
				{
					if(bExistPoint)
						return GAIA::STRING_TYPE_REAL;
				}
			}

			/* Check up the string is integer. */
			{
				GAIA::BL bMatch = GAIA::True;
				_DataType pTemp = p;
				while(*pTemp != '\0')
				{
					if((*pTemp >= '0' && *pTemp <= '9') ||
						(pTemp == p && (*pTemp == '-' || *pTemp == '+'))){}
					else
					{
						bMatch = GAIA::False;
						break;
					}
					++pTemp;
				}
				if(bMatch)
					return GAIA::STRING_TYPE_INTEGER;
			}

			return GAIA::STRING_TYPE_STRING;
		}
		template<typename _DataType> class string_cast;
		#define GAIA_DECLARATION_STRINGCAST(type, convert_func) \
		template<> class string_cast<type>\
		{\
		public:\
			string_cast(const GAIA::CH* psz){m_pGCH = psz; m_pGWCH = GNULL;}\
			string_cast(const GAIA::WCH* psz){m_pGCH = GNULL; m_pGWCH = psz;}\
			operator type() const\
			{\
				type ret;\
				if(m_pGCH != GNULL)\
					convert_func(m_pGCH, ret);\
				else if(m_pGWCH != GNULL)\
					convert_func(m_pGWCH, ret);\
				else\
				{\
					GAIA_AST(GAIA::False);\
					ret = 0;\
				}\
				return ret;\
			}\
		private:\
			const GAIA::CH* m_pGCH;\
			const GAIA::WCH* m_pGWCH;\
		};
		GAIA_DECLARATION_STRINGCAST(GAIA::NM, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::UM, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::N8, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::N16, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::N32, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::N64, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::U8, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::U16, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::U32, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::U64, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::BL, str2int);
		GAIA_DECLARATION_STRINGCAST(GAIA::F32, str2real);
		GAIA_DECLARATION_STRINGCAST(GAIA::F64, str2real);
		class string_autocast
		{
		public:
			GINL string_autocast(const GAIA::CH* psz){m_pGCH = psz; m_pGWCH = GNULL;}
			GINL string_autocast(const GAIA::WCH* psz){m_pGCH = GNULL; m_pGWCH = psz;}
			#define GAIA_DECLARATION_STRINGAUTOCAST(type) \
			GINL operator type()\
			{\
				type ret;\
				if(m_pGCH != GNULL)\
					return string_cast<type>(m_pGCH);\
				else if(m_pGWCH != GNULL)\
					return string_cast<type>(m_pGWCH);\
				else\
				{\
					GAIA_AST(GAIA::False);\
					ret = 0;\
				}\
				return ret;\
			}
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::NM);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::UM);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::N8);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::N16);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::N32);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::N64);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::U8);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::U16);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::U32);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::U64);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::BL);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::F32);
			GAIA_DECLARATION_STRINGAUTOCAST(GAIA::F64);
		private:
			const GAIA::CH* m_pGCH;
			const GAIA::WCH* m_pGWCH;
		};
	};
};

#endif
