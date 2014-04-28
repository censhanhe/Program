#ifndef		__GAIA_ALGORITHM_SIZE_INCREASER_H__
#define		__GAIA_ALGORITHM_SIZE_INCREASER_H__

namespace GAIA
{
	namespace ALGORITHM
	{
		template<typename _SizeType> class SingleSizeIncreaser
		{
		public:
			typedef _SizeType _sizetype;
		public:
			typedef SingleSizeIncreaser<_SizeType> __MyType;
		public:
			GINL _SizeType Increase(const _SizeType& size) const{return size + 1;}
		};
		template<typename _SizeType> class TwiceSizeIncreaser
		{
		public:
			typedef _SizeType _sizetype;
		public:
			typedef SingleSizeIncreaser<_SizeType> __MyType;
		public:
			GINL _SizeType Increase(const _SizeType& size) const{GAIA_AST(size >= 0); return GAIA::ALGORITHM::minimize((GAIA::UM)(size * 2 + 1), (GAIA::UM)(1024 * 1024 * 10));}
		};
	};
}

#endif
