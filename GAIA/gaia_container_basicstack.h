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
			BasicStack(){m_pData = GNULL; m_capacity = m_size = 0;}
			~BasicStack(){delete[] m_pData;}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID clear(){m_size = 0;}
			GINL _SizeType size() const{return m_size;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy();if(size > 0){m_pData = new _DataType[size];m_capacity = size;m_size = 0;}}
			GINL GAIA::GVOID destroy(){if(m_pData != GNULL){delete[] m_pData; m_capacity = m_size = 0;}}
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
			GINL const _DataType& top() const{return m_pData[this->size()];}
			GINL _DataType& top(){return m_pData[this->size() - 1];}

		private:
			_DataType* m_pData;
			_SizeType m_capacity;
			_SizeType m_size;
		};
	};
};

#endif
