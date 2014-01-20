#ifndef		__GAIA_CONTAINER_BASICQUEUE_H__
#define		__GAIA_CONTAINER_BASICQUEUE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicQueue
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicQueue<_DataType, _SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicQueue(){this->init();}
			GINL BasicQueue(const __MyType& src){this->init(); this->operator = (src);}
			GINL ~BasicQueue(){if(m_pData != GNULL) delete[] m_pData;}
			GINL _SizeType capacity() const{return m_capacity;}
			GINL GAIA::BL empty() const{if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL _SizeType size() const{return m_size;}
			GINL const _DataType& front() const{return this->operator[](0);}
			GINL _DataType& front(){return this->operator[](0);}
			GINL GAIA::GVOID clear(){m_pBack = m_pFront = m_pData; m_size = 0;}
			GINL GAIA::GVOID destroy(){if(m_pData != GNULL){delete[] m_pData; m_pData = m_pFront = m_pBack = GNULL; m_capacity = m_size = 0;}}
			GINL GAIA::GVOID reserve(const _SizeType& uSize)
			{
				if(m_pData != GNULL)
				{
					delete[] m_pData;
					m_pData = GNULL;
				}
				m_pFront = GNULL;
				m_pBack = GNULL;
				m_capacity = 0;
				m_size = 0;
				if(uSize != 0)
				{
					m_pData = new _DataType[uSize];
					m_pFront = m_pData;
					m_pBack = m_pData;
					m_capacity = uSize;
				}
			}
			GINL GAIA::BL pop()
			{
				if(this->size() != 0)
				{
					if(m_pFront == m_pData + this->capacity())
						m_pFront = m_pData;
					m_pFront++;
					if(m_pFront == m_pData + this->capacity() && m_pBack != m_pFront)
						m_pFront = m_pData;
					--m_size;
					return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::GVOID push(const _DataType& obj)
			{
				if(this->capacity() == 0)
				{
					m_pBack = m_pFront = m_pData = new _DataType[1];
					m_capacity = 1;
				}
				else if(this->size() == this->capacity())
				{
					_SizeIncreaserType increaser;
					_SizeType newsize = increaser.Increase(this->capacity());
					_DataType* pTemp = new _DataType[newsize];
					_SizeType uLenHead = this->capacity() - (m_pFront - m_pData) / sizeof(_DataType);
					for(_SizeType x = 0; x < uLenHead; ++x)
						pTemp[x] = m_pFront[x];
					_SizeType uLenTail = this->capacity() - uLenHead;
					for(_SizeType x = 0; x < uLenTail; ++x)
						pTemp[x + uLenHead] = m_pData[x];
					m_pFront = pTemp;
					m_pBack = &pTemp[this->capacity()];
					delete[] m_pData;
					m_pData = pTemp;
					m_capacity = this->capacity() + GAIA::ALGORITHM::minimize(this->capacity() / 2 + 1, (_SizeType)256);
				}
				if(m_pBack == m_pData + this->capacity())
					m_pBack = m_pData;
				if(m_pFront == m_pData + this->capacity())
					m_pFront = m_pData;
				*m_pBack++ = obj;
				++m_size;
			}
			GINL const __MyType& operator = (const __MyType& src)
			{
				this->clear();
				for(_SizeType x = 0; x < src.size(); ++x)
				{
					const _DataType* pTemp;
					if((_SizeType)src.m_pFront < (_SizeType)src.m_pBack)
						pTemp = &src.m_pFront[x];
					else
					{
						if(src.capacity() - (src.m_pFront - src.m_pData) > x)
							pTemp = &src.m_pFront[x];
						else
							pTemp = &src.m_pData[x - (src.capacity() - (src.m_pFront - src.m_pData))];
					}
					this->push(*pTemp);
				}
				return *this;
			}
			GINL _DataType& operator[](const _SizeType& index)
			{
				GAIA_ASSERT(index < this->size());
				if(m_pFront < m_pBack)
					return m_pFront[index];
				else
				{
					if(this->capacity() - (m_pFront - m_pData) > index)
						return m_pFront[index];
					else
						return m_pData[index - (this->capacity() - (m_pFront - m_pData))];
				}
			}
			GINL const _DataType& operator[](const _SizeType& index) const
			{
				GAIA_ASSERT(index < this->size());
				if((_SizeType)m_pFront < (_SizeType)m_pBack)
					return m_pFront[index];
				else
				{
					if(this->capacity() - (m_pFront - m_pData) > index)
						return m_pFront[index];
					else
						return m_pData[index - (this->capacity() - (m_pFront - m_pData))];
				}
			}
		private:
			GINL GAIA::GVOID init(){m_pData = m_pFront = m_pBack = GNULL; m_capacity = m_size = 0;}

		private:
			_DataType* m_pData;
			_DataType* m_pFront;
			_DataType* m_pBack;
			_SizeType m_capacity;
			_SizeType m_size;
		};
	};
};

#endif
