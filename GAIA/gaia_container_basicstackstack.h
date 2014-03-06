#ifndef		__GAIA_CONTAINER_BASICSTACKSTACK_H__
#define		__GAIA_CONTAINER_BASICSTACKSTACK_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, _SizeType _Size> class BasicStackStack
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			static const _SizeType _size = _Size;
		public:
			typedef BasicStackStack<_DataType, _SizeType, _Size> __MyType;
		public:
			GINL BasicStackStack(){this->init();}
			GINL BasicStackStack(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicStackStack(){}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return _Size;}
			GINL _SizeType resize(const _SizeType& size){GAIA_AST(size <= this->capacity()); m_size = size;}
			GINL GAIA::GVOID clear(){m_size = 0;}
			GINL _DataType* front_ptr(){return m_data;}
			GINL const _DataType* front_ptr() const{return m_data;}
			GINL _DataType* back_ptr(){return &m_data[m_size - 1];}
			GINL const _DataType* back_ptr() const{return &m_data[m_size - 1];}
			GINL _SizeType count(const _DataType& t) const{_SizeType result; GAIA::ALGORITHM::count(this->front_ptr(), this->back_ptr(), t, result); return result;}
			GINL GAIA::BL push(const _DataType& t)
			{
				if(this->size() < this->capacity()) 
				{
					m_data[m_size] = t; 
					++m_size;
					return GAIA::True;
				}
				else
					return GAIA::False;
			}
			GINL GAIA::BL pop()
			{
				if(m_size > 0)
				{
					--m_size;
					return GAIA::True;
				}
				else
					return GAIA::False;
			}
			GINL const _DataType& top() const{return m_data[m_size];}
			GINL _DataType& top(){return m_data[m_size];}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->clear();
				if(!src.empty())
				{
					GAIA::ALGORITHM::copy(m_data, src.m_data, src.size);
					m_size = src.size;
				}
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index){return m_data[index];}
			GINL const _DataType& operator[](const _SizeType& index) const{return m_data[index];}
		private:
			GINL GAIA::GVOID init(){m_size = 0;}
		private:
			_DataType m_data[_Size];
			_SizeType m_size;
		};
	};
};

#endif