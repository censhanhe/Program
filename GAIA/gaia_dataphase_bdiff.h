#ifndef 	__GAIA_DATAPHASE_BDIFF_H__
#define 	__GAIA_DATAPHASE_BDIFF_H__

namespace GAIA
{
	namespace DATAPHASE
	{
		template<typename _SizeType> class BDiff : public GAIA::Entity
		{
		public:
			typedef _SizeType _sizetype;
		public:
			typedef BDiff<_SizeType> __MyType;
		public:
			GINL BDiff(){}
			GINL BDiff(const __MyType& src){this->operator = (src);}
			GINL ~BDiff(){}
			GINL GAIA::BL empty() const{return GAIA::False;}
			GINL const _SizeType& size() const{}
			GINL const _SizeType& capacity() const{}
			GINL GAIA::GVOID reserve(const _SizeType& size){}
			GINL GAIA::GVOID clear(){}
			GINL GAIA::GVOID destroy(){}
			GINL GAIA::BL Generate(
					const GAIA::GVOID* p1,
					const _SizeType& size1,
					const GAIA::GVOID* p2,
					const _SizeType& size2)
			{
				return GAIA::False;
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
				return GAIA::False;
			}
			GINL __MyType& operator = (const __MyType& src){GAIA_AST(&src != this); return *this;}
		};
	};
};

#endif
