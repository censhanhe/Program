#ifndef		__GAIA_MACROHELPER_H__
#define		__GAIA_MACROHELPER_H__

/* Class helper. */
#define GAIA_CLASS_OPERATOR_COMPARE(self, another, anothertype) \
			GINL GAIA::BL operator == (const anothertype& src) const{return (self) == (src.another);}\
			GINL GAIA::BL operator != (const anothertype& src) const{return (self) != (src.another);}\
			GINL GAIA::BL operator >= (const anothertype& src) const{return (self) >= (src.another);}\
			GINL GAIA::BL operator <= (const anothertype& src) const{return (self) <= (src.another);}\
			GINL GAIA::BL operator > (const anothertype& src) const{return (self) > (src.another);}\
			GINL GAIA::BL operator < (const anothertype& src) const{return (self) < (src.another);}

#define GAIA_CLASS_OPERATOR_COMPARE2(self1, another1, self2, another2, anothertype) \
			GINL GAIA::BL operator == (const anothertype& src) const\
			{\
				if(self1 == src.another1 && self2 == src.another2)\
					return GAIA::True;\
				return GAIA::False;\
			}\
			GINL GAIA::BL operator != (const anothertype& src) const\
			{\
				if(self1 != src.another1 || self2 != src.another2)\
					return GAIA::True;\
				return GAIA::False;\
			}\
			GINL GAIA::BL operator >= (const anothertype& src) const\
			{\
				if(self1 > src.another1)\
					return GAIA::True;\
				else if(self1 < src.another1)\
					return GAIA::False;\
				else\
				{\
					if(self2 >= src.another2)\
						return GAIA::True;\
					else\
						return GAIA::False;\
				}\
			}\
			GINL GAIA::BL operator <= (const anothertype& src) const\
			{\
				if(self1 < src.another1)\
					return GAIA::True;\
				else if(self1 > src.another1)\
					return GAIA::False;\
				else\
				{\
					if(self2 <= src.another2)\
						return GAIA::True;\
					else\
						return GAIA::False;\
				}\
			}\
			GINL GAIA::BL operator > (const anothertype& src) const{return !(*this <= src);}\
			GINL GAIA::BL operator < (const anothertype& src) const{return !(*this >= src);}

#define GAIA_CLASS_OPERATOR_COMPARE3(self1, another1, self2, another2, self3, another3, anothertype) \
			GINL GAIA::BL operator == (const anothertype& src) const\
			{\
				if(self1 == src.another1 && self2 == src.another2 && self3 == src.another3)\
					return GAIA::True;\
				return GAIA::False;\
			}\
			GINL GAIA::BL operator != (const anothertype& src) const\
			{\
				if(self1 != src.another1 || self2 != src.another2 || self3 != src.another3)\
					return GAIA::True;\
				return GAIA::False;\
			}\
			GINL GAIA::BL operator >= (const anothertype& src) const\
			{\
				if(self1 > src.another1)\
					return GAIA::True;\
				else if(self1 < src.another1)\
					return GAIA::False;\
				else\
				{\
					if(self2 > src.another2)\
						return GAIA::True;\
					else if(self2 < src.another2)\
						return GAIA::False;\
					else\
					{\
						if(self3 >= src.another3)\
							return GAIA::True;\
						else\
							return GAIA::False;\
					}\
				}\
			}\
			GINL GAIA::BL operator <= (const anothertype& src) const\
			{\
				if(self1 < src.another1)\
					return GAIA::True;\
				else if(self1 > src.another1)\
					return GAIA::False;\
				else\
				{\
					if(self2 < src.another2)\
						return GAIA::True;\
					else if(self2 > src.another2)\
						return GAIA::False;\
					else\
					{\
						if(self3 <= src.another3)\
							return GAIA::True;\
						else\
							return GAIA::False;\
					}\
				}\
			}\
			GINL GAIA::BL operator > (const anothertype& src) const{return !(*this <= src);}\
			GINL GAIA::BL operator < (const anothertype& src) const{return !(*this >= src);}

/* GPCHR(GAIA parameter checkup helper) */
#define GPCHR_NULL(p) do{\
			GAIA_AST(!!(p));\
			if(!(p))\
				return;}while(0)

#define GPCHR_NULL_RET(p, ret) do{\
			GAIA_AST(!!(p));\
			if(!(p))\
				return ret;}while(0)

#define GPCHR_NULLSTRPTR(p) do{\
			GAIA_AST(!GAIA::ALGO::stremp(p));\
			if(GAIA::ALGO::stremp(p))\
				return;}while(0)

#define GPCHR_NULLSTRPTR_RET(p, ret) do{\
			GAIA_AST(!GAIA::ALGO::stremp(p));\
			if(GAIA::ALGO::stremp(p))\
				return ret;}while(0)

#define GPCHR_ZERO(p) do{\
			GAIA_AST((p) != 0);\
			if((p) == 0)\
				return;}while(0)

#define GPCHR_ZERO_RET(p, ret) do{\
			GAIA_AST((p) != 0);\
			if((p) == 0)\
				return ret;}while(0)

#endif
