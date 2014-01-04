#ifndef		__GAIA_CONTAINER_BASICQUEUE_H__
#define		__GAIA_CONTAINER_BASICQUEUE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType> class BasicQueue
		{
		public:
			GINL BasicQueue(){m_pData = m_pFront = m_pBack = GNULL;m_size = m_cursize = 0;}
			GINL BasicQueue(const BasicQueue<_DataType, _SizeType>& src){this->operator = (src);}
			GINL ~BasicQueue(){if(m_pData != GNULL) delete[] m_pData;}
			GINL _SizeType capacity() const{return m_size;}
			GINL GAIA::BL empty() const{if(m_cursize == 0) return GAIA::True; return GAIA::False;}
			GINL _SizeType size() const{return m_cursize;}
			GINL const _DataType& front() const{return *m_pFront;}
			GINL _DataType& front(){return *m_pFront;}
			GINL GAIA::GVOID clear(){m_pBack = m_pFront = m_pData;m_cursize = 0;}
			GINL GAIA::GVOID destroy(){if(m_pData != GNULL){delete[] m_pData; m_pData = m_pFront = m_pBack = GNULL; m_size = m_cursize = 0;}}
			GINL GAIA::GVOID reserve(_SizeType uSize)
			{
				if(m_pData != GNULL)
				{
					delete[] m_pData;
					m_pData = GNULL;
				}
				m_pFront = GNULL;
				m_pBack = GNULL;
				m_size = 0;
				m_cursize = 0;
				if(uSize != 0)
				{
					m_pData = new _DataType[uSize];
					m_pFront = m_pData;
					m_pBack = m_pData;
					m_size = uSize;
				}
			}
			GINL GAIA::BL pop()
			{
				if(m_cursize != 0)
				{
					if(m_pFront == m_pData + m_size)
						m_pFront = m_pData;
					m_pFront++;
					if(m_pFront == m_pData + m_size && m_pBack != m_pFront)
						m_pFront = m_pData;
					m_cursize--;
					return GAIA::True;
				}
				return GAIA::False;
			}
			GINL GAIA::GVOID push(const _DataType& obj)
			{
				if(m_size == 0)
				{
					m_pBack = m_pFront = m_pData = new _DataType[1];
					m_size = 1;
				}
				else if(m_cursize == m_size)
				{
					_DataType* pTemp = new _DataType[m_size + GAIA::ALGORITHM::min(m_size / 2 + 1, 256)];
					_SizeType uLenHead = m_size - (m_pFront - m_pData) / sizeof(_DataType);
					for(_SizeType x = 0; x < uLenHead; x++)
						pTemp[x] = m_pFront[x];
					_SizeType uLenTail = m_size - uLenHead;
					for(_SizeType x = 0; x < uLenTail; x++)
						pTemp[x + uLenHead] = m_pData[x];
					m_pFront = pTemp;
					m_pBack = &pTemp[m_size];
					delete[] m_pData;
					m_pData = pTemp;
					m_size = m_size + GAIA::ALGORITHM::min(m_size / 2 + 1, 256);
				}
				if(m_pBack == m_pData + m_size)
					m_pBack = m_pData;
				if(m_pFront == m_pData + m_size)
					m_pFront = m_pData;
				*m_pBack++ = obj;
				m_cursize++;
			}
			GINL const BasicQueue<_DataType, _SizeType>& operator = (const BasicQueue<_DataType, _SizeType>& src)
			{
				this->clear();
				for(_SizeType x = 0; x < src.size(); x++)
				{
					const _DataType* pTemp;
					if((_SizeType)src.m_pFront < (_SizeType)src.m_pBack)
						pTemp = &src.m_pFront[x];
					else
					{
						if(src.m_size - (src.m_pFront - src.m_pData) > x)
							pTemp = &src.m_pFront[x];
						else
							pTemp = &src.m_pData[x - (src.m_size - (src.m_pFront - src.m_pData))];
					}
					this->push(*pTemp);
				}
				return *this;
			}
			GINL _DataType& operator[](_SizeType index)
			{
				GAIA_ASSERT(index < m_cursize);
				if((_SizeType)m_pFront < (_SizeType)m_pBack)
					return m_pFront[index];
				else
				{
					if(m_size - (m_pFront - m_pData) > index)
						return m_pFront[index];
					else
						return m_pData[index - (m_size - (m_pFront - m_pData))];
				}
			}
			GINL const _DataType& operator[](_SizeType index) const
			{
				GAIA_ASSERT(index < m_cursize);
				if((_SizeType)m_pFront < (_SizeType)m_pBack)
					return m_pFront[index];
				else
				{
					if(m_size - (m_pFront - m_pData) > index)
						return m_pFront[index];
					else
						return m_pData[index - (m_size - (m_pFront - m_pData))];
				}
			}
		private:
			_DataType* m_pData;
			_DataType* m_pFront;
			_DataType* m_pBack;
			_SizeType m_size;
			_SizeType m_cursize;
		};
	};
};

#endif