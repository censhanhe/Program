#ifndef		__GAIA_ALGORITHM_STRING_H__
#define		__GAIA_ALGORITHM_STRING_H__

namespace GAIA
{
	namespace ALGO
	{
		template<typename _DataType> _DataType tolower(const _DataType& c){if(c >= 'A' && c <= 'Z') return c - 'A' + 'a'; return c;}
		template<typename _DataType> _DataType toupper(const _DataType& c){if(c >= 'a' && c <= 'z') return c - 'a' + 'A'; return c;}
		template<typename _DataType> _DataType tolowers(_DataType p){GAIA_AST(!!p); _DataType ret = p; while(*p != '\0'){*p = GAIA::ALGO::tolower(*p);p++;} return ret;}
		template<typename _DataType> _DataType touppers(_DataType p){GAIA_AST(!!p); _DataType ret = p; while(*p != '\0'){*p = GAIA::ALGO::toupper(*p);p++;} return ret;}
		template<typename _DataType> GAIA::BL islower(const _DataType& c){return c >= 'a' && c <= 'z';}
		template<typename _DataType> GAIA::BL isupper(const _DataType& c){return c >= 'A' && c <= 'Z';}
		template<typename _DataType> GAIA::BL isexistlower(_DataType p){GAIA_AST(!!p); while(*p != '\0'){if(GAIA::ALGO::islower(*p)) return GAIA::True; p++;} return GAIA::False;}
		template<typename _DataType> GAIA::BL isexistupper(_DataType p){GAIA_AST(!!p); while(*p != '\0'){if(GAIA::ALGO::isupper(*p)) return GAIA::True; p++;} return GAIA::False;}
		template<typename _DataType> GAIA::BL isalllower(_DataType p){GAIA_AST(!!p); while(*p != '\0'){if(!GAIA::ALGO::islower(*p)) return GAIA::False; p++;} return GAIA::True;}
		template<typename _DataType> GAIA::BL isallupper(_DataType p){GAIA_AST(!!p); while(*p != '\0'){if(!GAIA::ALGO::isupper(*p)) return GAIA::False; p++;} return GAIA::True;}
		template<typename _DataType> GAIA::BL isdigit(const _DataType& c){return c >= '0' && c <= '9';}
		template<typename _DataType> GAIA::BL isalpha(const _DataType& c){if(c < 'A' || c > 'z') return GAIA::False; return c <= 'Z' || c >= 'a';}
		template<typename _DataType> GAIA::BL ispunctuation(const _DataType& c){return c > ' ' && !GAIA::ALGO::isalpha(c) && !GAIA::ALGO::isdigit(c) && c < 0xFF;}
		template<typename _DataType> GAIA::BL isspecial(const _DataType& c){return c < ' ';}
		template<typename _DataType> GAIA::BL isansi(_DataType c)
		{
			if(c >= 0 && c < 128)
				return GAIA::True;
			return GAIA::False;
		}
		template<typename _DataType> GAIA::BL isexistansi(_DataType p)
		{
			while(*p != '\0')
			{
				if(*p >= 0 && *p < 128)
					return GAIA::True;
				++p;
			}
			return GAIA::False;
		}
		template<typename _DataType> GAIA::BL isallansi(_DataType p)
		{
			while(*p != '\0')
			{
				if(*p < 0 || *p >= 128)
					return GAIA::False;
				++p;
			}
			return GAIA::True;
		}
		template<typename _DataType> GAIA::BL stremp(_DataType p)
		{
			if(p == GNIL || *p == '\0')
				return GAIA::True;
			return GAIA::False;
		}
		template<typename _DataType> _DataType strend(_DataType p)
		{
			while(*p != '\0') ++p;
			return p;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strch(_DataType1 p, const _DataType2& c)
		{
			while(*p != '\0')
			{
				if(*p == c)
					return p;
				++p;
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strich(_DataType1 p, const _DataType2& c)
		{
			while(*p != '\0')
			{
				if(GAIA::ALGO::tolower(*p) == GAIA::ALGO::tolower(c))
					return p;
				++p;
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strchs(_DataType1 p, _DataType2 key)
		{
			while(*p != '\0')
			{
				_DataType2 pTemp = key;
				while(*pTemp != '\0')
				{
					if(*p == *pTemp)
						return p;
					++pTemp;
				}
				++p;
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strichs(_DataType1 p, _DataType2 key)
		{
			while(*p != '\0')
			{
				_DataType2 pTemp = key;
				while(*pTemp != '\0')
				{
					if(GAIA::ALGO::tolower(*p) == GAIA::ALGO::tolower(*pTemp))
						return p;
					++pTemp;
				}
				++p;
			}
			return GNIL;
		}
		template<typename _DataType> GAIA::SIZE strlen(_DataType p){GAIA_AST(!!p); GAIA::SIZE ret = 0; while(p[ret] != '\0') ret++; return ret;}
		template<typename _DataType1, typename _DataType2> GAIA::SIZE strcnt(_DataType1 p, const _DataType2& key)
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
		template<typename _DataType1, typename _DataType2> GAIA::SIZE strcnts(_DataType1 p, _DataType2 keys)
		{
			GAIA::SIZE ret = 0;
			while(*keys != '\0')
			{
				ret += GAIA::ALGO::strcnt(p, *keys);
				++keys;
			}
			return ret;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strcpy(_DataType1 pDst, _DataType2 pSrc)
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
		template<typename _DataType1, typename _DataType2, typename _SizeType> _DataType1 strcpy(_DataType1 pDst, _DataType2 pSrc, _SizeType size)
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
		template<typename _DataType1, typename _DataType2> _DataType1 stradd(_DataType1 pDst, _DataType2 pSrc)
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
			return pDst;
		}
		template<typename _DataType> _DataType* strnew(const _DataType* p)
		{
			_DataType* ret = (_DataType*)GAIA_MALLOC(_DataType, GAIA::ALGO::strlen(p) + 1);
			GAIA::ALGO::strcpy(ret, p);
			return ret;
		}
		template<typename _DataTypeDst, typename _DataTypeSrc> _DataTypeDst* strnewex(const _DataTypeSrc* p)
		{
			_DataTypeDst* ret = (_DataTypeDst*)GAIA_MALLOC(_DataTypeDst, GAIA::ALGO::strlen(p) + 1);
			GAIA::ALGO::strcpy(ret, p);
			return ret;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strcat(_DataType1 pDst, _DataType2 pSrc)
		{
			GAIA_AST(!!pDst);
			GAIA_AST(!!pSrc);
			_DataType1 ret = pDst;
			pDst = pDst + GAIA::ALGO::strlen(pDst);
			GAIA::ALGO::strcpy(pDst, pSrc);
			return ret;
		}
		template<typename _DataType1, typename _DataType2> GAIA::N32 strcmp(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			for(;;)
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
		#if GAIA_COMPILER != GAIA_COMPILER_CL // For CL C4702 Warning.
			return 0;
		#endif
		}
		template<typename _DataType1, typename _DataType2> GAIA::N32 stricmp(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			for(;;)
			{
				if(GAIA::ALGO::tolower(*p1) < GAIA::ALGO::tolower(*p2))
					return -1;
				else if(GAIA::ALGO::tolower(*p1) > GAIA::ALGO::tolower(*p2))
					return +1;
				else
				{
					if(*p1 == '\0')
						return 0;
					++p1;
					++p2;
				}
			}
		#if GAIA_COMPILER != GAIA_COMPILER_CL // For CL C4702 Warning.
			return 0;
		#endif
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::N32 strcmp(_DataType1 p1, _DataType2 p2, _SizeType size)
		{
			for(; size != 0; --size)
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
		template<typename _DataType1, typename _DataType2, typename _SizeType> GAIA::N32 stricmp(_DataType1 p1, _DataType2 p2, _SizeType size)
		{
			for(; size != 0; --size)
			{
				if(GAIA::ALGO::tolower(*p1) < GAIA::ALGO::tolower(*p2))
					return -1;
				else if(GAIA::ALGO::tolower(*p1) > GAIA::ALGO::tolower(*p2))
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
		template<typename _DataType1, typename _DataType2> GAIA::N32 strcmpnil(_DataType1 p1, _DataType2 p2)
		{
			if(p1 == GNIL && p2 == GNIL)
				return 0;
			else if(p1 != GNIL && p2 == GNIL)
				return +1;
			else if(p1 == GNIL && p1 != GNIL)
				return -1;
			else
				return GAIA::ALGO::strcmp(p1, p2);
		}
		template<typename _DataType1, typename _DataType2> GAIA::N32 stricmpnil(_DataType1 p1, _DataType2 p2)
		{
			if(p1 == GNIL && p2 == GNIL)
				return 0;
			if(p1 == GNIL && p2 == GNIL)
				return 0;
			else if(p1 != GNIL && p2 == GNIL)
				return +1;
			else if(p1 == GNIL && p1 != GNIL)
				return -1;
			else
				return GAIA::ALGO::stricmp(p1, p2);
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strstr(_DataType1 p1, _DataType2 p2)
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
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 stristr(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);
			while(*p1 != '\0')
			{
				_DataType1 po = p1;
				_DataType2 p = p2;
				while(*po != '\0' && *p != '\0')
				{
					if(GAIA::ALGO::tolower(*p) != GAIA::ALGO::tolower(*po))
						break;
					++po;
					++p;
				}
				if(*p == '\0')
					return p1;
				++p1;
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1* strwrd(const _DataType1* p1, const _DataType2* p2)
		{
			const _DataType1* p = p1;
			while((p = GAIA::ALGO::strstr(p, p2)) != GNIL)
			{
				if(p != p1)
				{
					_DataType1 t = *(p - 1);
					if(GAIA::ALGO::isalpha(t) || GAIA::ALGO::isdigit(t))
					{
						++p;
						continue;
					}
				}
				_DataType1 t = *(p + GAIA::ALGO::strlen(p2));
				if(GAIA::ALGO::isalpha(t) || GAIA::ALGO::isdigit(t))
				{
					++p;
					continue;
				}
				return const_cast<_DataType1*>(p);
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1* striwrd(const _DataType1* p1, const _DataType2* p2)
		{
			const _DataType1* p = p1;
			while((p = GAIA::ALGO::stristr(p, p2)) != GNIL)
			{
				if(p != p1)
				{
					_DataType1 t = *(p - 1);
					if(GAIA::ALGO::isalpha(t) || GAIA::ALGO::isdigit(t))
					{
						++p;
						continue;
					}
				}
				_DataType1 t = *(p + GAIA::ALGO::strlen(p2));
				if(GAIA::ALGO::isalpha(t) || GAIA::ALGO::isdigit(t))
				{
					++p;
					continue;
				}
				return const_cast<_DataType1*>(p);
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strmch(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);

			_DataType1 p = p1;
			while(*p != '\0' && *p2 != '\0')
			{
				if(*p2 != *p)
					return GNIL;
				++p;
				++p2;
			}
			if(*p2 == '\0')
				return p1;
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strimch(_DataType1 p1, _DataType2 p2)
		{
			GAIA_AST(!!p1);
			GAIA_AST(!!p2);

			_DataType1 p = p1;
			while(GAIA::ALGO::tolower(*p) != '\0' && GAIA::ALGO::tolower(*p2) != '\0')
			{
				if(GAIA::ALGO::tolower(*p2) != GAIA::ALGO::tolower(*p))
					return GNIL;
				++p;
				++p2;
			}
			if(*p2 == '\0')
				return p1;
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strdrop(_DataType1 p, _DataType2 pKeys)
		{
			while(*p != '\0')
			{
				_DataType2 p2 = pKeys;
				while(*p2 != '\0')
				{
					if(*p == *p2)
						return p;
					++p2;
				}
				++p;
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 stridrop(_DataType1 p, _DataType2 pKeys)
		{
			while(*p != '\0')
			{
				_DataType2 p2 = pKeys;
				while(*p2 != '\0')
				{
					if(GAIA::ALGO::tolower(*p) == GAIA::ALGO::tolower(*p2))
						return p;
					++p2;
				}
				++p;
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 strdropr(_DataType1 p, _DataType2 pKeys)
		{
			_DataType1 p1 = GAIA::ALGO::strend(p);
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
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2> _DataType1 stridropr(_DataType1 p, _DataType2 pKeys)
		{
			_DataType1 p1 = GAIA::ALGO::strend(p);
			while(p1 > p)
			{
				_DataType2 p2 = pKeys;
				while(*p2 != '\0')
				{
					if(GAIA::ALGO::tolower(*p1) == GAIA::ALGO::tolower(*p2))
					{
						*(p1 + 1) = '\0';
						return p1;
					}
					++p2;
				}
				--p1;
			}
			return GNIL;
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> _SizeType strleftfill(_DataType1 p, _DataType2 fill, const _SizeType& size)
		{
			GPCHR_NULL_RET(p, 0);
			GPCHR_BELOWEQUALZERO_RET(size, 0);
			_SizeType l = GSCAST(_SizeType)(GAIA::ALGO::strlen(p));
			if(l >= size)
				return 0;
			GAIA::ALGO::move_next(p + size, p + l, l + 1);
			_SizeType fsize = size - l;
			for(_SizeType x = 0; x < fsize; ++x)
				p[x] = fill;
			GAIA::ALGO::strlen(p);
			return fsize;
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> _SizeType strrightfill(_DataType1 p, _DataType2 fill, const _SizeType& size)
		{
			GPCHR_NULL_RET(p, 0);
			GPCHR_BELOWEQUALZERO_RET(size, 0);
			_SizeType l = GSCAST(_SizeType)(GAIA::ALGO::strlen(p));
			if(l >= size)
				return 0;
			for(_SizeType x = l; x < size; ++x)
				p[x] = fill;
			p[size] = '\0';
			return size - l;
		}
		template<typename _DataType> _DataType strext(_DataType p)
		{
			_DataType pEnd = GAIA::ALGO::strend(p);
			--pEnd;
			while(pEnd >= p)
			{
				if(*pEnd == '\\' || *pEnd == '/')
					return GNIL;
				if(*pEnd == '.')
				{
					if(pEnd[1] != '\0')
						return pEnd + 1;
				}
				--pEnd;
			}
			return GNIL;
		}
		template<typename _DataType> _DataType strfilename(_DataType p)
		{
			_DataType pEnd = GAIA::ALGO::strend(p);
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
			return GNIL;
		}
		template<typename _DataType> _DataType strpath(_DataType p)
		{
			_DataType pTemp = GAIA::ALGO::strfilename(p);
			if(pTemp == GNIL)
				return GNIL;
			*pTemp = '\0';
			return p;
		}
		template<typename _SrcDataType, typename _DstDataType> _DstDataType int2str(const _SrcDataType& src, _DstDataType pDst)
		{
			GAIA_AST(!!pDst);
			_SrcDataType tsrc = src;
			_DstDataType p = pDst;
			if(src < (_SrcDataType)0)
			{
			#ifdef GAIA_DEBUG_WARNING
			#	if GAIA_COMPILER == GAIA_COMPILER_CL
			#		pragma warning(disable : 4146)
			#	endif
			#endif
				tsrc = -tsrc;
			#ifdef GAIA_DEBUG_WARNING
			#	if GAIA_COMPILER == GAIA_COMPILER_CL
			#		pragma warning(default : 4146)
			#	endif
			#endif
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
				GAIA::ALGO::inverse(*pDst == '-' ? pDst + 1 : pDst, p - 1);
			*p = '\0';
			return p + 1;
		}
		template<typename _SrcDataType, typename _DstDataType> _DstDataType real2str(const _SrcDataType& src, _DstDataType pDst)
		{
			GAIA_AST(!!pDst);
			GAIA::N64 left = (GAIA::N64)src;
			_SrcDataType right = src - (_SrcDataType)left;
			right = GAIA::MATH::xabs(right);
			while(right - GSCAST(_SrcDataType)(GSCAST(GAIA::N64)(right)) != 0)
				right *= R(10.0);
			_DstDataType p = GAIA::ALGO::int2str(left, pDst);
			--p;
			*p = '.';
			++p;
			p = GAIA::ALGO::int2str((GAIA::N64)right, p);
			return p;
		}
		template<typename _DstDataType, typename _SizeType> _DstDataType hex2str(const GAIA::U8* pSrc, const _SizeType& size, _DstDataType pDst)
		{
			GAIA_AST(!!pSrc);
			GAIA_AST(!!pDst);
			GAIA_AST(size > 0);
			_SizeType sizet = size;
			_DstDataType p = pDst;
			pSrc = pSrc + size - 1;
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
				--pSrc;
				--sizet;
			}
			*p = '\0';
			return pDst;
		}
		template<typename _SrcDataType, typename _SizeType> GAIA::U8* str2hex(_SrcDataType pSrc, const _SizeType& size, GAIA::U8* pDst)
		{
			GAIA_AST(!!pSrc);
			GAIA_AST(!!pDst);
			GAIA_AST(size > 0);
			GAIA_AST(size % 2 == 0);
			_SizeType sizet = size;
			GAIA::U8* p = pDst + size - 1;
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
				*p = GSCAST(GAIA::U8)((u0 << 4) + u1);
				--p;
				--sizet;
			}
			return pDst;
		}
		template<typename _SrcDataType, typename _DstDataType> _SrcDataType str2int(_SrcDataType pSrc, _DstDataType& dst)
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
				dst = GSCAST(_DstDataType)(dst * 10);
				dst = GSCAST(_DstDataType)(dst + (*pSrc - '0'));
				++pSrc;
			}
			if(bSign)
				dst = 0 - dst;
			return pSrc;
		}
		template<typename _SrcDataType, typename _DstDataType> _SrcDataType str2real(_SrcDataType pDst, _DstDataType& dst)
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
				right_dst = R(0.0);
			dst = left + right_dst;
			if(bSign)
				dst = -dst;
			return pDst;
		}
		template<typename _DataType> GAIA::U32 strtype(_DataType p)
		{
			if(GAIA::ALGO::stremp(p))
				return GAIA::STRING_TYPE_INVALID;

			/* Check up the string is RID. */
			GAIA::SIZE len = GAIA::ALGO::strlen(p);
			if(len == sizeof(GAIA::X128) ||
				len == sizeof(GAIA::X128) * 2)
			{
				GAIA::BL bMatch = GAIA::True;
				_DataType pTemp = p;
				while(*pTemp != '\0')
				{
					if(	(*pTemp >= 'a' && *pTemp <= 'f') ||
						(*pTemp >= 'A' && *pTemp <= 'F') ||
						(*pTemp >= '0' && *pTemp <= '9')){}
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
			string_cast(const GAIA::CH* psz){m_pCH = psz; m_pWCH = GNIL;}\
			string_cast(const GAIA::WCH* psz){m_pCH = GNIL; m_pWCH = psz;}\
			operator type() const\
			{\
				type ret;\
				if(m_pCH != GNIL)\
					GAIA::ALGO::convert_func(m_pCH, ret);\
				else if(m_pWCH != GNIL)\
					GAIA::ALGO::convert_func(m_pWCH, ret);\
				else\
				{\
					GAIA_AST(GAIA::ALWAYSFALSE);\
					ret = 0;\
				}\
				return ret;\
			}\
		private:\
			const GAIA::CH* m_pCH;\
			const GAIA::WCH* m_pWCH;\
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
		template<typename _ValueType, typename _CharType, typename _SizeType> GAIA::BL value_cast(const _ValueType& v, _CharType* p, const _SizeType& size);
		template<typename _CharType, typename _SizeType> GAIA::BL value_cast(const GAIA::F32& v, _CharType* p, const _SizeType& size)
		{
			GAIA::ALGO::real2str(v, p);
			GAIA_AST(GAIA::ALGO::strlen(p) < size);
			return GAIA::True;
		}
		template<typename _CharType, typename _SizeType> GAIA::BL value_cast(const GAIA::F64& v, _CharType* p, const _SizeType& size)
		{
			GAIA::ALGO::real2str(v, p);
			GAIA_AST(GAIA::ALGO::strlen(p) < size);
			return GAIA::True;
		}
		template<typename _ValueType, typename _CharType, typename _SizeType> GAIA::BL value_cast(const _ValueType& v, _CharType* p, const _SizeType& size)
		{
			GAIA::ALGO::int2str(v, p);
			GAIA_AST(GAIA::ALGO::strlen(p) < size);
			return GAIA::True;
		}
		class string_autocast
		{
		public:
			GINL string_autocast(const GAIA::CH* psz){m_pCH = psz; m_pWCH = GNIL;}
			GINL string_autocast(const GAIA::WCH* psz){m_pCH = GNIL; m_pWCH = psz;}
			#define GAIA_DECLARATION_STRINGAUTOCAST(type) \
			GINL operator type()\
			{\
				type ret;\
				if(m_pCH != GNIL)\
					return string_cast<type>(m_pCH);\
				else if(m_pWCH != GNIL)\
					return string_cast<type>(m_pWCH);\
				else\
				{\
					GAIA_AST(GAIA::ALWAYSFALSE);\
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
			const GAIA::CH* m_pCH;
			const GAIA::WCH* m_pWCH;
		};
	};
};

#endif
