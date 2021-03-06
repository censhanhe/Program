#ifndef 	__GAIA_MATH_RID_H__
#define 	__GAIA_MATH_RID_H__

namespace GAIA
{
	namespace MATH
	{
		/* 128 bit random id. */
		class RID128 : public GAIA::Base
		{
		public:
			GINL GAIA::SIZE size() const{return sizeofarray(u);}
			GINL GAIA::BL empty() const{return u64_0 == 0 && u64_1 == 0;}
			GINL GAIA::GVOID clear(){u64_0 = u64_1 = 0;}
			GINL GAIA::GVOID uuid();
			template<typename _ParamDataType> GAIA::GVOID fromstring(const _ParamDataType* psz){GAIA::ALGO::str2hex(psz, sizeofarray(u), u);}
			template<typename _ParamDataType> GAIA::GVOID tostring(_ParamDataType* psz) const{GAIA::ALGO::hex2str(u, sizeofarray(u), psz);}
			GINL RID128& operator = (const RID128& src){GAIA_AST(&src != this); u64_0 = src.u64_0; u64_1 = src.u64_1; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE2(u64_0, u64_0, u64_1, u64_1, RID128);
		public:
			union
			{
				GAIA::U8 u[16];
				class
				{
				public:
					GAIA::U32 u0;
					GAIA::U32 u1;
					GAIA::U32 u2;
					GAIA::U32 u3;
				};
				class
				{
				public:
					GAIA::U64 u64_0;
					GAIA::U64 u64_1;
				};
			};
		};

		/* 64 bit random id. */
		class RID64 : public GAIA::Base
		{
		public:
			GINL GAIA::SIZE size() const{return sizeofarray(u);}
			GINL GAIA::BL empty() const{return u64_0 == 0;}
			GINL GAIA::GVOID clear(){u64_0 = 0;}
			GINL GAIA::GVOID uuid();
			template<typename _ParamDataType> GAIA::GVOID fromstring(const _ParamDataType* psz){GAIA::ALGO::str2hex(psz, sizeofarray(u), u);}
			template<typename _ParamDataType> GAIA::GVOID tostring(_ParamDataType* psz) const{GAIA::ALGO::hex2str(u, sizeofarray(u), psz);}
			GINL RID64& operator = (const RID64& src){GAIA_AST(&src != this); u64_0 = src.u64_0; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(u64_0, u64_0, RID64);
		public:
			union
			{
				GAIA::U8 u[8];
				class
				{
				public:
					GAIA::U32 u0;
					GAIA::U32 u1;
				};
				class
				{
				public:
					GAIA::U64 u64_0;
				};
			};
		};

		/* 32 bit random id. */
		class RID32 : public GAIA::Base
		{
		public:
			GINL GAIA::SIZE size() const{return sizeofarray(u);}
			GINL GAIA::BL empty() const{return u0 == 0;}
			GINL GAIA::GVOID clear(){u0 = 0;}
			GINL GAIA::GVOID uuid();
			template<typename _ParamDataType> GAIA::GVOID fromstring(const _ParamDataType* psz){GAIA::ALGO::str2hex(psz, sizeofarray(u), u);}
			template<typename _ParamDataType> GAIA::GVOID tostring(_ParamDataType* psz) const{GAIA::ALGO::hex2str(u, sizeofarray(u), psz);}
			GINL RID32& operator = (const RID32& src){GAIA_AST(&src != this); u0 = src.u0; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(u0, u0, RID32);
		public:
			union
			{
				GAIA::U8 u[4];
				class
				{
				public:
					GAIA::U32 u0;
				};
			};
		};
	};
};

#include "gaia_math_rid_indp.h"

#endif
