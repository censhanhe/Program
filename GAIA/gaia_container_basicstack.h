#ifndef		__GAIA_CONTAINER_BASICSTACK_H__
#define		__GAIA_CONTAINER_BASICSTACK_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicStack
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicStack<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicStack(){this->init();}
			GINL BasicStack(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicStack(){if(m_pData != GNULL) delete[] m_pData;}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID clear(){m_size = 0;}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy();if(size > 0){m_pData = new _DataType[size];m_capacity = size;m_size = 0;}}
			GINL GAIA::GVOID destroy(){if(m_pData != GNULL){delete[] m_pData; m_pData = GNULL; m_capacity = m_size = 0;}}
			GINL _DataType* front_ptr(){return m_pData;}
			GINL const _DataType* front_ptr() const{return m_pData;}
			GINL _DataType* back_ptr(){return &m_pData[m_size - 1];}
			GINL const _DataType* back_ptr() const{return &m_pData[m_size - 1];}
			GINL _SizeType count(const _DataType& t) const
			{
				if(this->empty())
					return 0;
				_SizeType ret = 0;
				GAIA::ALGORITHM::count(this->front_ptr(), this->back_ptr(), t, ret);
				return ret;
			}
			GINL GAIA::GVOID push(const _DataType& t)
			{
				if(this->size() == this->capacity())
				{
					_SizeIncreaserType increaser;
					_SizeType newsize = increaser.Increase(this->capacity());
					_DataType* pTemp = new _DataType[newsize];
					if(m_pData != GNULL)
					{
						for(_SizeType c = 0; c < this->size(); ++c)
							pTemp[c] = m_pData[c];
						delete[] m_pData;
					}
					m_pData = pTemp;
					m_capacity = newsize;
				}
				m_pData[m_size++] = t;
			}
			GINL GAIA::BL pop(){if(this->size() > 0){--m_size; return GAIA::True;} return GAIA::False;}
			GINL const _DataType& top() const{return m_pData[this->size() - 1];}
			GINL _DataType& top(){return m_pData[this->size() - 1];}
			GINL __MyType& operator = (const __MyType& src)
			{
				this->reserve(src.size());
				GAIA::ALGORITHM::xcopy(m_pData, src.m_pData, src.size());
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				GAIA_ASSERT(index < m_size);
				return m_pData[index];
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				GAIA_ASSERT(index < m_size);
				return m_pData[index];
			}
		private:
			GINL GAIA::GVOID init(){m_pData = GNULL; m_capacity = m_size = 0;}
		private:
			_DataType* m_pData;
			_SizeType m_capacity;
			_SizeType m_size;
		};
	};
};

#endif
