#ifndef		__GAIA_ALGORITHM_STRING_H__
#define		__GAIA_ALGORITHM_STRING_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType> GINL _DataType tolower(const _DataType& c){if(c >= 'A' && c <= 'Z') return c - 'A' + 'a'; return c;}
		template<typename _DataType> GINL _DataType toupper(const _DataType& c){if(c >= 'a' && c <= 'z') return c - 'a' + 'A'; return c;}
		template<typename _DataType> GINL _DataType* tolower(_DataType* p){GAIA_AST(p != GNULL); _DataType* ret = p; while(*p != 0){*p = GAIA::ALGORITHM::tolower(*p);p++;} return ret;}
		template<typename _DataType> GINL _DataType* toupper(_DataType* p){GAIA_AST(p != GNULL); _DataType* ret = p; while(*p != 0){*p = GAIA::ALGORITHM::toupper(*p);p++;} return ret;}
		template<typename _DataType> GINL GAIA::BL islower(const _DataType& c){return c >= 'a' && c <= 'z';}
		template<typename _DataType> GINL GAIA::BL isupper(const _DataType& c){return c >= 'A' && c <= 'Z';}
		template<typename _DataType> GINL GAIA::BL isexistlower(const _DataType* p){GAIA_AST(p != GNULL); while(*p != 0){if(GAIA::ALGORITHM::islower(*p)) return GAIA::True; p++;} return GAIA::False;}
		template<typename _DataType> GINL GAIA::BL isexistupper(const _DataType* p){GAIA_AST(p != GNULL); while(*p != 0){if(GAIA::ALGORITHM::isupper(*p)) return GAIA::True; p++;} return GAIA::False;}
		template<typename _DataType> GINL GAIA::BL isalllower(const _DataType* p){GAIA_AST(p != GNULL); while(*p != 0){if(!GAIA::ALGORITHM::islower(*p)) return GAIA::False; p++;} return GAIA::True;}
		template<typename _DataType> GINL GAIA::BL isallupper(const _DataType* p){GAIA_AST(p != GNULL); while(*p != 0){if(!GAIA::ALGORITHM::isupper(*p)) return GAIA::False; p++;} return GAIA::True;}
		template<typename _DataType> GINL GAIA::BL isdigit(const _DataType& c){return c >= '0' && c <= '9';}
		template<typename _DataType> GINL GAIA::BL isalpha(const _DataType& c){if(c < 'A' || c > 'z') return GAIA::False; return c <= 'Z' || c >= 'a';}
		template<typename _DataType> GINL GAIA::BL ispunctuation(const _DataType& c){return c > ' ' && !GAIA::ALGORITHM::isalpha(c) && !GAIA::ALGORITHM::isdigit(c) && c < 0xFF;}
		template<typename _DataType> GINL GAIA::BL isspecial(const _DataType& c){return c < ' ';}
		template<typename _DataType> GINL GAIA::BL stremp(const _DataType* p)
		{
			if(p == GNULL || p[0] == 0)
				return GAIA::True;
			return GAIA::False;
		}
		template<typename _DataType> GINL _DataType* strend(const _DataType* p)
		{
			while(*p != 0) ++p;
			return const_cast<_DataType*>(p);
		}
		template<typename _DataType> GINL _DataType* strch(const _DataType* p, const _DataType& c)
		{
			while(*p != 0)
			{
				if(*p == c)
					return const_cast<_DataType*>(p);
				++p;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* strich(const _DataType* p, const _DataType& c)
		{
			while(*p != 0)
			{
				if(GAIA::ALGORITHM::tolower(*p) == GAIA::ALGORITHM::tolower(c))
					return const_cast<_DataType*>(p);
				++p;
			}
			return GNULL;
		}
		template<typename _DataType> GINL GAIA::SIZE strlen(const _DataType* p){GAIA_AST(p != GNULL); GAIA::SIZE ret = 0; while(p[ret] != 0) ret++; return ret;}
		template<typename _DataType1, typename _DataType2> GINL GAIA::SIZE strcnt(const _DataType1* p, const _DataType2& key)
		{
			GAIA::SIZE ret = 0;
			while(*p != 0)
			{
				if(*p == key)
					++ret;
				++p;
			}
			return ret;
		}
		template<typename _DataType> GINL _DataType* strcpy(_DataType* dst, const _DataType* src)
		{
			GAIA_AST(dst != GNULL);
			GAIA_AST(src != GNULL);
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
		template<typename _DataType> GINL _DataType* strcat(_DataType* dst, const _DataType* src)
		{
			GAIA_AST(dst != GNULL);
			GAIA_AST(src != GNULL);
			_DataType* ret = dst;
			dst = dst + GAIA::ALGORITHM::strlen(dst);
			GAIA::ALGORITHM::strcpy(dst, src);
			return ret;
		}
		template<typename _DataType> GINL GAIA::N32 strcmp(const _DataType* p1, const _DataType* p2)
		{
			GAIA_AST(p1 != GNULL);
			GAIA_AST(p2 != GNULL);
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
		template<typename _DataType> GINL GAIA::N32 stricmp(const _DataType* p1, const _DataType* p2)
		{
			GAIA_AST(dst != GNULL);
			GAIA_AST(src != GNULL);
			while(GAIA::ALWAYSTRUE)
			{
				_DataType c1 = GAIA::ALGORITHM::tolower(*p1);
				_DataType c2 = GAIA::ALGORITHM::tolower(*p2);
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
		template<typename _DataType> GINL _DataType* strstr(const _DataType* p1, const _DataType* p2)
		{
			GAIA_AST(p1 != GNULL);
			GAIA_AST(p2 != GNULL);
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
					return const_cast<_DataType*>(p1);
				++p1;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* stristr(const _DataType* p1, const _DataType* p2)
		{
			GAIA_AST(p1 != GNULL);
			GAIA_AST(p2 != GNULL);
			while(*p1 != 0)
			{
				const _DataType* po = p1;
				const _DataType* p = p2;
				while(*po != 0 && *p != 0)
				{
					if(GAIA::ALGORITHM::tolower(*p) != GAIA::ALGORITHM::tolower(*po))
						break;
					++po;
					++p;
				}
				if(*p == 0)
					return const_cast<_DataType*>(p1);
				++p1;
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* strwrd(const _DataType* p1, const _DataType* p2)
		{
			const _DataType* p = p1;
			while((p = GAIA::ALGORITHM::strstr(p, p2)) != GNULL)
			{
				if(p != p1)
				{
					_DataType t = *(p - 1);
					if(GAIA::ALGORITHM::isalpha(t) || GAIA::ALGORITHM::isdigit(t))
					{
						++p;
						continue;
					}
				}
				_DataType t = *(p + GAIA::ALGORITHM::strlen(p2));
				if(GAIA::ALGORITHM::isalpha(t) || GAIA::ALGORITHM::isdigit(t))
				{
					++p;
					continue;
				}
				return const_cast<_DataType*>(p);
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* striwrd(const _DataType* p1, const _DataType* p2)
		{
			const _DataType* p = p1;
			while((p = GAIA::ALGORITHM::stristr(p, p2)) != GNULL)
			{
				if(p != p1)
				{
					_DataType t = *(p - 1);
					if(GAIA::ALGORITHM::isalpha(t) || GAIA::ALGORITHM::isdigit(t))
					{
						++p;
						continue;
					}
				}
				_DataType t = *(p + GAIA::ALGORITHM::strlen(p2));
				if(GAIA::ALGORITHM::isalpha(t) || GAIA::ALGORITHM::isdigit(t))
				{
					++p;
					continue;
				}
				return const_cast<_DataType*>(p);
			}
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* strmch(const _DataType* p1, const _DataType* p2)
		{
			GAIA_AST(p1 != GNULL);
			GAIA_AST(p2 != GNULL);

			const _DataType* p = p1;
			while(*p != 0 && *p2 != 0)
			{
				if(*p2 != *p)
					return GNULL;
				++p;
				++p2;
			}
			if(*p2 == 0)
				return const_cast<_DataType*>(p1);
			return GNULL;
		}
		template<typename _DataType> GINL _DataType* strimch(const _DataType* p1, const _DataType* p2)
		{
			GAIA_AST(p1 != GNULL);
			GAIA_AST(p2 != GNULL);

			const _DataType* p = p1;
			while(GAIA::ALGORITHM::tolower(*p) != 0 && GAIA::ALGORITHM::tolower(*p2) != 0)
			{
				if(*p2 != *p)
					return GNULL;
				++p;
				++p2;
			}
			if(*p2 == 0)
				return const_cast<_DataType*>(p1);
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL const _DataType1* strdrop(const _DataType1* p, const _DataType2* keys)
		{
			const _DataType1* p1 = p;
			while(*p1 != 0)
			{
				const _DataType2* p2 = keys;
				while(*p2 != 0)
				{
					if(*p1 == *p2)
						return p1;
					++p2;
				}
				++p1;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL const _DataType1* stridrop(const _DataType1* p, const _DataType2* keys)
		{
			const _DataType1* p1 = p;
			while(*p1 != 0)
			{
				const _DataType2* p2 = keys;
				while(*p2 != 0)
				{
					if(GAIA::ALGORITHM::tolower(*p1) == GAIA::ALGORITHM::tolower(*p2))
						return p1;
					++p2;
				}
				++p1;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1* strdropr(_DataType1* p, const _DataType2* keys)
		{
			_DataType1* p1 = GAIA::ALGORITHM::strend(p);
			while(p1 > p)
			{
				const _DataType2* p2 = keys;
				while(*p2 != 0)
				{
					if(*p1 == *p2)
					{
						*(p1 + 1) = 0;
						return p1;
					}
					++p2;
				}
				--p1;
			}
			return GNULL;
		}
		template<typename _DataType1, typename _DataType2> GINL _DataType1* stridropr(_DataType1* p, const _DataType2* keys)
		{
			_DataType1* p1 = GAIA::ALGORITHM::strend(p);
			while(p1 > p)
			{
				const _DataType2* p2 = keys;
				while(*p2 != 0)
				{
					if(GAIA::ALGORITHM::tolower(*p1) == GAIA::ALGORITHM::tolower(*p2))
					{
						*(p1 + 1) = 0;
						return p1;
					}
					++p2;
				}
				--p1;
			}
			return GNULL;
		}
		template<typename _DataType> GINL const _DataType* strext(const _DataType* p)
		{
			const _DataType* pEnd = GAIA::ALGORITHM::strend(p);
			--pEnd;
			while(pEnd >= p)
			{
				if(*pEnd == '\\' || *pEnd == '/')
					return GNULL;
				if(*pEnd == '.')
				{
					if(pEnd[1] != 0)
						return &pEnd[1];
				}
				--pEnd;
			}
			return GNULL;
		}
		template<typename _SrcDataType, typename _DstDataType> GINL _DstDataType* int2str(const _SrcDataType& src, _DstDataType* pDst)
		{
			GAIA_AST(pDst != GNULL);
			_SrcDataType tsrc = src;
			_DstDataType* p = pDst;
			if(src < (_SrcDataType)0)
			{
				tsrc = -tsrc;
				*p = '-';
				++p;
			}
			while(tsrc > 0)
			{
				*p = (_DstDataType)(tsrc % 10 + '0');
				tsrc /= 10;
				++p;
			}
			if(p == pDst)
			{
				*p = '0';
				++p;
			}
			else
			{
				GAIA::ALGORITHM::inverse(*pDst == '-' ? pDst + 1 : pDst, p - 1);
			}
			*p = 0;
			return p + 1;
		}
		template<typename _SrcDataType, typename _DstDataType> GINL _DstDataType* real2str(const _SrcDataType& src, _DstDataType* pDst)
		{
			GAIA_AST(pDst != GNULL);
			GAIA::N64 left = (GAIA::N64)src;
			_SrcDataType right = src - (_SrcDataType)left;
			right = GAIA::MATH::abs(right);
			while(right - (_SrcDataType)(GAIA::N64)right != 0)
				right *= 10.0F;
			_DstDataType* p = GAIA::ALGORITHM::int2str(left, pDst);
			--p;
			*p = '.';
			++p;
			p = GAIA::ALGORITHM::int2str((GAIA::N64)right, p);
			return p;
		}
		template<typename _SrcDataType, typename _DstDataType> GINL const _SrcDataType* str2int(const _SrcDataType* p, _DstDataType& dst)
		{
			GAIA_AST(p != GNULL);
			dst = 0;
			GAIA::BL bSign;
			if(*p == '-')
			{
				bSign = GAIA::True;
				++p;
			}
			else
				bSign = GAIA::False;
			while(*p != 0)
			{
				if(*p < '0' || *p > '9')
					break;
				dst = (_DstDataType)(dst * 10);
				dst = (_DstDataType)(dst + (*p - '0'));
				++p;
			}
			if(bSign)
				dst = 0 - dst;
			return p;
		}
		template<typename _SrcDataType, typename _DstDataType> GINL const _SrcDataType* str2real(const _SrcDataType* p, _DstDataType& dst)
		{
			GAIA_AST(p != GNULL);
			GAIA::BL bSign;
			if(*p == '-')
			{
				bSign = GAIA::True;
				++p;
			}
			else
				bSign = GAIA::False;
			_DstDataType left = 0;
			_DstDataType right = 0;
			_DstDataType right_dst;
			_DstDataType* pTarget = &left;
			while(*p != 0)
			{
				if(*p < '0' || *p > '9')
					break;
				*pTarget *= 10;
				*pTarget += (*p - '0');
				++p;
			}
			if(*p == '.')
			{
				++p;
				_DstDataType right_div = 1;
				pTarget = &right;
				while(*p != 0)
				{
					if(*p < '0' || *p > '9')
						break;
					*pTarget *= 10;
					right_div *= 10;
					*pTarget += (*p - '0');
					++p;
				}
				right_dst = *pTarget / right_div;
			}
			else
				right_dst = 0.0F;
			dst = left + right_dst;
			if(bSign)
				dst = -dst;
			return p;
		}
		template<typename _DataType> class string_cast;
		#define GAIA_DECLARATION_STRINGCAST(type, convert_func) \
		template<> class string_cast<type>\
		{\
		public:\
			string_cast(const GAIA::GCH* psz){m_pGCH = psz; m_pGWCH = GNULL;}\
			string_cast(const GAIA::GWCH* psz){m_pGCH = GNULL; m_pGWCH = psz;}\
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
			const GAIA::GCH* m_pGCH;\
			const GAIA::GWCH* m_pGWCH;\
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
			GINL string_autocast(const GAIA::GCH* psz){m_pGCH = psz; m_pGWCH = GNULL;}
			GINL string_autocast(const GAIA::GWCH* psz){m_pGCH = GNULL; m_pGWCH = psz;}
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
			const GAIA::GCH* m_pGCH;
			const GAIA::GWCH* m_pGWCH;
		};
	};
};

#endif
