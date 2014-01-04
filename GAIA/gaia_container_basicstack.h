#ifndef		__GAIA_CONTAINER_BASICSTACK_H__
#define		__GAIA_CONTAINER_BASICSTACK_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType> class BasicStack
		{
		public:
			BasicStack(){m_pData = GNULL; m_size = m_cursize = 0;}
			~BasicStack(){delete[] m_pData;}

			GINL GAIA::BL empty() const{if(m_cursize == 0) return GAIA::True; return GAIA::False;}
			GINL _SizeType size() const{return m_cursize;}
			GINL _SizeType capacity() const{return m_size;}
			GINL GAIA::GVOID reserve(const _SizeType& size){this->destroy();if(size > 0){m_pData = new _DataType[size];m_size = size;m_cursize = 0;}}
			GINL GAIA::GVOID destroy(){if(m_pData != GNULL){delete[] m_pData; m_size = m_cursize = 0;}}
			GINL GAIA::GVOID push(const _DataType& t)
			{
				if(m_cursize == m_size)
				{
					_SizeIncreaserType increaser;
					_SizeType newsize = increaser.Increase(m_size);
					_DataType* pTemp = new _DataType[newsize];
					if(m_pData != GNULL)
					{
						for(_SizeType c = 0; c < m_cursize; c++)
							pTemp[c] = m_pData[c];
						delete[] m_pData;
					}
					m_pData = pTemp;
					m_size = newsize;
				}
				m_pData[m_cursize++] = t;
			}
			GINL GAIA::BL pop(){if(m_cursize > 0){m_cursize--; return GAIA::True;} return GAIA::False;}
			GINL const _DataType& top() const{return m_pData[m_cursize];}
			GINL _DataType& top(){return m_pData[m_cursize - 1];}

		private:
			_DataType* m_pData;
			_SizeType m_size;
			_SizeType m_cursize;
		};
	};
};

#endif
