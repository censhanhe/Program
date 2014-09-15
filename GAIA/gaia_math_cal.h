#ifndef 	__GAIA_MATH_CAL_H__
#define 	__GAIA_MATH_CAL_H__

namespace GAIA
{
	namespace MATH
	{
		GAIA_ENUM_BEGIN(OPERATOR)
			OPERATOR_ADD,
			OPERATOR_SUB,
			OPERATOR_MUL,
			OPERATOR_DIV,
			OPERATOR_MOD,
			OPERATOR_SQRT,
			OPERATOR_POW,
			OPERATOR_LOG,
			OPERATOR_LN,
			OPERATOR_SIN,
			OPERATOR_COS,
			OPERATOR_TAN,
			OPERATOR_ATAN2,
			OPERATOR_ASIN,
			OPERATOR_ACOS,
			OPERATOR_RANDOM,
			OPERATOR_RANDOMF,
			OPERATOR_ABS,
			OPERATOR_CLAMP,
			OPERATOR_MAX,
			OPERATOR_MIN,
			OPERATOR_SIGN,
		GAIA_ENUM_END(OPERATOR)

		static const GAIA::CH* OPERATOR_STRINGA[] = 
		{
			"OPERATOR_INVALID",
			"OPERATOR_ADD",
			"OPERATOR_SUB",
			"OPERATOR_MUL",
			"OPERATOR_DIV",
			"OPERATOR_MOD",
			"OPERATOR_SQRT",
			"OPERATOR_POW",
			"OPERATOR_LOG",
			"OPERATOR_LN",
			"OPERATOR_SIN",
			"OPERATOR_COS",
			"OPERATOR_TAN",
			"OPERATOR_ATAN2",
			"OPERATOR_ASIN",
			"OPERATOR_ACOS",
			"OPERATOR_RANDOM",
			"OPERATOR_RANDOMF",
			"OPERATOR_ABS",
			"OPERATOR_CLAMP",
			"OPERATOR_MAX",
			"OPERATOR_MIN",
			"OPERATOR_SIGN",
		};
	};
};

#endif
