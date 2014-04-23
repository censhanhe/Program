#ifndef		__GAIA_ALGORITHM_BASE_H__
#define		__GAIA_ALGORITHM_BASE_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _DataType1, typename _DataType2> GINL GAIA::GVOID move(_DataType1& dst, const _DataType2& src){dst = src;}
		template<typename _DataType, typename _SizeType> GINL GAIA::GVOID move_prev(_DataType* p, const _SizeType& size)
		{
			for(_SizeType x = 0; x < size; ++x)
			{
				*p = *(p + 1);
				++p;
			}
		}
		template<typename _DataType, typename _SizeType> GINL GAIA::GVOID move_next(_DataType* p, const _SizeType& size)
		{
			for(_SizeType x = 0; x < size; ++x)
			{
				*p = *(p - 1);
				--p;
			}
		}
		template<typename _DataType1, typename _DataType2, typename _SizeType> GINL GAIA::GVOID move_prev(_DataType1* dst, const _DataType2* src, const _SizeType& size)
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
		template<typename _DataType1, typename _DataType2, typename _SizeType> GINL GAIA::GVOID move_next(_DataType1* dst, const _DataType2* src, const _SizeType& size)
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
		template<typename _DataType1, typename _DataType2> GINL GAIA::GVOID swap(_DataType1& t1, _DataType2& t2)
		{
			typename GAIA::DATATYPE::TRAITS::DataTypeConvertTraits<_DataType1, _DataType2>::ConvertedType t = t2;
			t2 = t1;
			t1 = t;
		}
		template<typename _DataType> GINL GAIA::GVOID swap(GAIA::ITERATOR::Iterator<_DataType>& t1, GAIA::ITERATOR::Iterator<_DataType>& t2)
		{
			_DataType t = *t1;
			*t1 = *t2;
			*t2 = t;
		}
		template<typename _DataType> GINL GAIA::GVOID inverse(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_AST(pBegin != GNULL);
			GAIA_AST(pEnd != GNULL);
			if(pBegin >= pEnd)
				return;
			while(pBegin < pEnd)
			{
				GAIA::ALGORITHM::swap(*pBegin, *pEnd);
				++pBegin;
				--pEnd;
			}
		}
		template<typename _DataType> GINL GAIA::GVOID inverse(GAIA::ITERATOR::Iterator<_DataType>& begin_it, GAIA::ITERATOR::Iterator<_DataType>& end_it)
		{
			GAIA_AST(!begin_it.empty());
			GAIA_AST(!end_it.empty());
			while(begin_it != end_it)
			{
				GAIA::ALGORITHM::swap(begin_it, end_it);
				++begin_it;
				--end_it;
			}
		}
	};
};

#endif
