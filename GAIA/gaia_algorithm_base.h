#ifndef		__GAIA_ALGORITHM_BASE_H__
#define		__GAIA_ALGORITHM_BASE_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _DataType1, typename _DataType2> GAIA::GVOID move(_DataType1& dst, const _DataType2& src){dst = src;}
		template <typename _DataType1, typename _DataType2, typename _SizeType> GAIA::GVOID move_prev(_DataType1* dst, const _DataType2* src, const _SizeType& size)
		{
			_SizeType sizetemp = size;
			while(sizetemp > 0)
			{
				*dst = *src;
				++dst;
				++src;
				--sizetemp;
			}
		}
		template <typename _DataType1, typename _DataType2, typename _SizeType> GAIA::GVOID move_next(_DataType1* dst, const _DataType2* src, const _SizeType& size)
		{
			_SizeType sizetemp = size;
			while(sizetemp > 0)
			{
				*dst = *src;
				--dst;
				--src;
				--sizetemp;
			}
		}
		template <typename _DataType1, typename _DataType2> GAIA::GVOID swap(_DataType1& t1, _DataType2& t2)
		{
			typename DATATYPE::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType t = t2;
			t2 = t1;
			t1 = t;
		}
		template <typename _DataType> GAIA::GVOID inverse(_DataType* pBegin, _DataType* pEnd)
		{
			if(pBegin >= pEnd)
				return;
			while(pBegin < pEnd)
			{
				GAIA::ALGORITHM::swap(*pBegin, *pEnd);
				++pBegin;
				--pEnd;
			}
		}
	};
};

#endif