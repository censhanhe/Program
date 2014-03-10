#ifndef		__GAIA_CONTAINER_BASICHEAP_H__
#define		__GAIA_CONTAINER_BASICHEAP_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, _SizeType _PieceSize> class BasicHeap
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _piecesize = _PieceSize;
		public:
			typedef BasicHeap<_DataType, _SizeType, _PieceSize> __MyType;
		public:
			GINL BasicHeap(){}
			GINL BasicHeap(const __MyType& src){}
			GINL ~BasicHeap(){}
			GINL GAIA::BL empty() const{return GAIA::False;}
			GINL _SizeType size() const{return 0;}
			GINL _SizeType capacity() const{return 0;}
			GINL GAIA::GVOID clear(){}
			GINL GAIA::GVOID destroy(){}
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
			GINL GAIA::GVOID init(){}
		private:
		};
	};
};

#endif