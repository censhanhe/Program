#ifndef		__GAIA_ALGORITHM_UNIQUE_H__
#define		__GAIA_ALGORITHM_UNIQUE_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template <typename _DataType> _DataType* unique_order(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_ASSERT(pBegin <= pEnd);
			_DataType* pLast = pBegin;
			++pBegin;
			while(pBegin <= pEnd)
			{
				if(*pBegin != *pLast)
				{
					++pLast;
					if(pLast != pBegin) // OPT for large object copy.
						*pLast = *pBegin;
				}
				++pBegin;
			}
			return pLast;
		}
		template <typename _DataType> _DataType* unique_noorder(_DataType* pBegin, _DataType* pEnd)
		{
			GAIA_ASSERT(pBegin <= pEnd);

		}
	};
};

#endif