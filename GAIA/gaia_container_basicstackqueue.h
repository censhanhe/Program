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
			class it
			{
			};
			class const_it
			{
			};
		public:
			GINL BasicStackQueue(){this->init();}
			GINL BasicStackQueue(const __MyType& src){this->operator = (src);}
			GINL ~BasicStackQueue(){}
			GINL _SizeType capacity() const{return _Size;}
			GINL GAIA::BL empty() const{return this->size() == 0;}
			GINL const _SizeType& size() const{return m_size;}
			GINL _SizeType count() const;
		private:
			GINL GVOID init(){}
		private:
			_SizeType m_size;
		};
	};
};

#endif