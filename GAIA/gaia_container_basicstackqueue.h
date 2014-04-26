#ifndef		__GAIA_CONTAINER_BASICSTACKQUEUE_H__
#define		__GAIA_CONTAINER_BASICSTACKQUEUE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, _SizeType _Size> class BasicStackQueue : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _size = _Size;
		public:
			typedef BasicStackQueue<_DataType, _SizeType, _Size> __MyType;
		public:
		};
	};
};

#endif