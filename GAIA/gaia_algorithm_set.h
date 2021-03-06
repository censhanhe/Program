#ifndef		__GAIA_ALGORITHM_SET_H__
#define		__GAIA_ALGORITHM_SET_H__

namespace GAIA
{
	namespace ALGO
	{
		template<typename _DataType> GAIA::SIZE set_and_count(_DataType pDstBegin, _DataType pDstEnd, _DataType pSrcBegin, _DataType pSrcEnd) // If return value is GINVALID, the call failed!
		{
			GAIA_AST(pDstBegin != GNIL);
			GAIA_AST(pDstEnd != GNIL);
			GAIA_AST(pSrcBegin != GNIL);
			GAIA_AST(pSrcEnd != GNIL);
			if(!GAIA::ALGO::isunique(pSrcBegin, pSrcEnd))
				return GINVALID;
			GAIA::SIZE ret = 0;
			while(pSrcBegin <= pSrcEnd)
			{
				_DataType pTemp = pDstBegin;
				while(pTemp <= pDstEnd)
				{
					if(*pTemp == *pSrcBegin)
						++ret;
					++pTemp;
				}
				++pSrcBegin;
			}
			return ret;
		}
		template<typename _DataType, typename _SizeType> GAIA::SIZE set_or_count(_DataType pDstBegin, _DataType pDstEnd, _DataType pSrcBegin, _DataType pSrcEnd) // If return value is GINVALID, the call failed!
		{
			GAIA_AST(pDstBegin != GNIL);
			GAIA_AST(pDstEnd != GNIL);
			GAIA_AST(pSrcBegin != GNIL);
			GAIA_AST(pSrcEnd != GNIL);
			if(!GAIA::ALGO::isunique(pSrcBegin, pSrcEnd))
				return GINVALID;
			GAIA::SIZE ret = pDstEnd - pDstBegin + 1;
			while(pSrcBegin <= pSrcEnd)
			{
				GAIA::BL bExist = GAIA::False;
				_DataType pTemp = pDstBegin;
				while(pTemp <= pDstEnd)
				{
					if(*pTemp == *pSrcBegin)
					{
						bExist = GAIA::True;
						break;
					}
					++pTemp;
				}
				if(!bExist)
					++ret;
				++pSrcBegin;
			}
			return ret;
		}
		template<typename _DataType> GAIA::SIZE set_sub_count(_DataType pDstBegin, _DataType pDstEnd, _DataType pSrcBegin, _DataType pSrcEnd) // If return value is GINVALID, the call failed!
		{
			GAIA_AST(pDstBegin != GNIL);
			GAIA_AST(pDstEnd != GNIL);
			GAIA_AST(pSrcBegin != GNIL);
			GAIA_AST(pSrcEnd != GNIL);
			if(!GAIA::ALGO::isunique(pSrcBegin, pSrcEnd))
				return GINVALID;
			GAIA::SIZE ret = pDstEnd - pDstBegin + 1;
			while(pSrcBegin <= pSrcEnd)
			{
				_DataType pTemp = pDstBegin;
				while(pTemp <= pDstEnd)
				{
					if(*pTemp == *pSrcBegin)
					{
						GAIA_AST(ret > 0);
						--ret;
					}
					++pTemp;
				}
				++pSrcBegin;
			}
			return ret;
		}
		template<typename _DataType> GAIA::SIZE set_and(_DataType pDstBegin, _DataType pDstEnd, _DataType pSrcBegin, _DataType pSrcEnd) // If return value is GINVALID, the call failed!
		{
			GAIA_AST(pDstBegin != GNIL);
			GAIA_AST(pDstEnd != GNIL);
			GAIA_AST(pSrcBegin != GNIL);
			GAIA_AST(pSrcEnd != GNIL);
			if(!GAIA::ALGO::isunique(pSrcBegin, pSrcEnd))
				return GINVALID;
			_DataType pNew = GAIA::ALGO::swapleft(pDstBegin, pDstEnd, pSrcBegin, pSrcEnd);
			return GSCAST(GAIA::SIZE)(pNew - pDstBegin);
		}
		template<typename _DataType, typename _SizeType> GAIA::SIZE set_or(_DataType pDstBegin, _DataType pDstEnd, _SizeType dst_max_size, _DataType pSrcBegin, _DataType pSrcEnd) // If return value is GINVALID, the call failed! If the dst_max_size <= 0, it means the buffer is must enough.
		{
			GAIA_AST(pDstBegin != GNIL);
			GAIA_AST(pDstEnd != GNIL);
			GAIA_AST(pSrcBegin != GNIL);
			GAIA_AST(pSrcEnd != GNIL);
			if(!GAIA::ALGO::isunique(pSrcBegin, pSrcEnd))
				return GINVALID;
			_DataType pWrite = pDstEnd;
			while(pSrcBegin <= pSrcEnd)
			{
				GAIA::BL bExist = GAIA::False;
				_DataType pTemp = pDstBegin;
				while(pTemp <= pDstEnd)
				{
					if(*pTemp == *pSrcBegin)
					{
						bExist = GAIA::True;
						break;
					}
					++pTemp;
				}
				if(!bExist)
					*(++pWrite) = *pSrcBegin;
				++pSrcBegin;
			}
			return GSCAST(GAIA::SIZE)(pWrite - pDstBegin);
		}
		template<typename _DataType> GAIA::SIZE set_sub(_DataType pDstBegin, _DataType pDstEnd, _DataType pSrcBegin, _DataType pSrcEnd) // If return value is GINVALID, the call failed!
		{
			GAIA_AST(pDstBegin != GNIL);
			GAIA_AST(pDstEnd != GNIL);
			GAIA_AST(pSrcBegin != GNIL);
			GAIA_AST(pSrcEnd != GNIL);
			if(!GAIA::ALGO::isunique(pSrcBegin, pSrcEnd))
				return GINVALID;
			_DataType pNew = GAIA::ALGO::swapleft_inversekey(pDstBegin, pDstEnd, pSrcBegin, pSrcEnd);
			return GSCAST(GAIA::SIZE)(pNew - pDstBegin);
		}
	};
};

#endif
