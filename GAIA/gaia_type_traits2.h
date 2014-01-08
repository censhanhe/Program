#ifndef		__GAIA_TYPE_TRAITS2_H__
#define		__GAIA_TYPE_TRAITS2_H__

namespace GAIA
{
	namespace DATATYPE
	{
		/* Data convert formula declaration. */
		template <typename _DataType1, typename _DataType2> class DataTypeConvertTraits{public:typedef _DataType1 ConvertedType;};

		/* UM second. */ 
		template <> class DataTypeConvertTraits<U8, UM>{public:typedef UM ConvertedType;};
		template <> class DataTypeConvertTraits<U16, UM>{public:typedef UM ConvertedType;};
		template <> class DataTypeConvertTraits<U32, UM>{public:typedef UM ConvertedType;};
#if GAIA_MACHINE == GAIA_MACHINE128
		template <> class DataTypeConvertTraits<U64, UM>{public:typedef UM ConvertedType;};
#else
		template <> class DataTypeConvertTraits<U64, UM>{public:typedef U64 ConvertedType;};
#endif
		template <> class DataTypeConvertTraits<U128, UM>{public:typedef U128 ConvertedType;};

		/* UM first. */
		template <> class DataTypeConvertTraits<UM, N8>{public:typedef UM ConvertedType;};
		template <> class DataTypeConvertTraits<UM, N16>{public:typedef UM ConvertedType;};
		template <> class DataTypeConvertTraits<UM, N32>{public:typedef UM ConvertedType;};
#if GAIA_MACHINE == GAIA_MACHINE64
		template <> class DataTypeConvertTraits<UM, N64>{public:typedef U64 ConvertedType;};
#elif GAIA_MACHINE == GAIA_MACHINE128
		template <> class DataTypeConvertTraits<UM, N64>{public:typedef UM ConvertedType;};
#else
		template <> class DataTypeConvertTraits<UM, N64>{public:typedef N64 ConvertedType;};
#endif
#if GAIA_MACHINE == GAIA_MACHINE128
		template <> class DataTypeConvertTraits<UM, N128>{public:typedef U128 ConvertedType;};
#else
		template <> class DataTypeConvertTraits<UM, N128>{public:typedef N128 ConvertedType;};
#endif

		/* Others */
		template <> class DataTypeConvertTraits<U8, BL>{public:typedef U8 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, BL>{public:typedef U16 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, BL>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, BL>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U128, BL>{public:typedef U128 ConvertedType;};

		template <> class DataTypeConvertTraits<BL, N8>{public:typedef N8 ConvertedType;};
		template <> class DataTypeConvertTraits<BL, N16>{public:typedef N16 ConvertedType;};
		template <> class DataTypeConvertTraits<BL, N32>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<BL, N64>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<BL, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N8, U8>{public:typedef U8 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, U8>{public:typedef N16 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, U8>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, U8>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, U8>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N8, U16>{public:typedef U16 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, U16>{public:typedef U16 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, U16>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, U16>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, U16>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N8, U32>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, U32>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, U32>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, U32>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, U32>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N8, U64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, U64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, U64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, U64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, U64>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N8, U128>{public:typedef U128 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, U128>{public:typedef U128 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, U128>{public:typedef U128 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, U128>{public:typedef U128 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, U128>{public:typedef U128 ConvertedType;};

		template <> class DataTypeConvertTraits<U8, N8>{public:typedef U8 ConvertedType;};
		template <> class DataTypeConvertTraits<U8, N16>{public:typedef N16 ConvertedType;};
		template <> class DataTypeConvertTraits<U8, N32>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<U8, N64>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<U8, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<U16, N8>{public:typedef U16 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, N16>{public:typedef U16 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, N32>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, N64>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<U32, N8>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, N16>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, N32>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, N64>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<U64, N8>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, N16>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, N32>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, N64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<U8, F32>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, F32>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, F32>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, F32>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<U128, F32>{public:typedef F32 ConvertedType;};

		template <> class DataTypeConvertTraits<U8, F64>{public:typedef F64 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, F64>{public:typedef F64 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, F64>{public:typedef F64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, F64>{public:typedef F64 ConvertedType;};
		template <> class DataTypeConvertTraits<U128, F64>{public:typedef F64 ConvertedType;};

		template <> class DataTypeConvertTraits<F32, N8>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<F32, N16>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<F32, N32>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<F32, N64>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<F32, N128>{public:typedef F32 ConvertedType;};

		template <> class DataTypeConvertTraits<F64, N8>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<F64, N16>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<F64, N32>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<F64, N64>{public:typedef F32 ConvertedType;};
		template <> class DataTypeConvertTraits<F64, N128>{public:typedef F32 ConvertedType;};

		template <> class DataTypeConvertTraits<N8, N8>{public:typedef N8 ConvertedType;};
		template <> class DataTypeConvertTraits<N8, N16>{public:typedef N16 ConvertedType;};
		template <> class DataTypeConvertTraits<N8, N32>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<N8, N64>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N8, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N16, N8>{public:typedef N16 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, N16>{public:typedef N16 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, N32>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, N64>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N16, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N32, N8>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, N16>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, N32>{public:typedef N32 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, N64>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N32, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N64, N8>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, N16>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, N32>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, N64>{public:typedef N64 ConvertedType;};
		template <> class DataTypeConvertTraits<N64, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<N128, N8>{public:typedef N128 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, N16>{public:typedef N128 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, N32>{public:typedef N128 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, N64>{public:typedef N128 ConvertedType;};
		template <> class DataTypeConvertTraits<N128, N128>{public:typedef N128 ConvertedType;};

		template <> class DataTypeConvertTraits<U8, U8>{public:typedef U8 ConvertedType;};
		template <> class DataTypeConvertTraits<U8, U16>{public:typedef U16 ConvertedType;};
		template <> class DataTypeConvertTraits<U8, U32>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U8, U64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U8, U128>{public:typedef U128 ConvertedType;};

		template <> class DataTypeConvertTraits<U16, U8>{public:typedef U16 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, U16>{public:typedef U16 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, U32>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, U64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U16, U128>{public:typedef U128 ConvertedType;};

		template <> class DataTypeConvertTraits<U32, U8>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, U16>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, U32>{public:typedef U32 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, U64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U32, U128>{public:typedef U128 ConvertedType;};

		template <> class DataTypeConvertTraits<U64, U8>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, U16>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, U32>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, U64>{public:typedef U64 ConvertedType;};
		template <> class DataTypeConvertTraits<U64, U128>{public:typedef U128 ConvertedType;};

		template <> class DataTypeConvertTraits<U128, U8>{public:typedef U128 ConvertedType;};
		template <> class DataTypeConvertTraits<U128, U16>{public:typedef U128 ConvertedType;};
		template <> class DataTypeConvertTraits<U128, U32>{public:typedef U128 ConvertedType;};
		template <> class DataTypeConvertTraits<U128, U64>{public:typedef U128 ConvertedType;};
		template <> class DataTypeConvertTraits<U128, U128>{public:typedef U128 ConvertedType;};
	};
};

#endif
