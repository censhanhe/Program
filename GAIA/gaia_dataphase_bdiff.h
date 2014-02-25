#ifndef 	__GAIA_DATAPHASE_BDIFF_H__
#define 	__GAIA_DATAPHASE_BDIFF_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _SizeType> class BDiff
		{
		public:
			typedef _SizeType _sizetype;
		public:
			typedef BDiff<_SizeType> __MyType;
		public:
			GINL BDiff(){}
			GINL BDiff(const __MyType& src){this->operator = (src);}
			GINL ~BDiff(){}
			GINL GAIA::BL empty() const{}
			GINL _SizeType size() const{}
			GINL _SizeType capacity() const{}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL GAIA::GVOID clear(){}
			GINL GAIA::GVOID destroy(){}
			GINL GAIA::BL Generate(
					const GAIA::GVOID* p1, 
					const _SizeType& size1, 
					const GAIA::GVOID* p2, 
					const _SizeType& size2)
			{
			}
			GINL GAIA::BL Patch(
					const GAIA::GVOID* pSrc, 
					const _SizeType& srcsize, 
					const GAIA::GVOID* pDst, 
					const _SizeType& dstsize,
					GAIA::GVOID* pResult,
					const _SizeType& resbufsize,
					_SizeType& ressize)
			{
			}
			GINL __MyType& operator = (const __MyType& src){return *this;}
		};
	};
};

#endif