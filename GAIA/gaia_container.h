#ifndef		__GAIA_CONTAINER_H__
#define		__GAIA_CONTAINER_H__

#define GAIA_CONTAINER_PROXY \
			GINL GAIA::GVOID proxy(const _DataType* p)\
			{\
				m_pFront = GCCAST(const _DataType*)(p);\
				if(m_pFront != GNIL)\
					m_capacity = m_size = GAIA::ALGO::strlen(m_pFront);\
				else\
					m_capacity = m_size = 0;\
			}\
			GINL GAIA::GVOID proxy(const _DataType* p, const _SizeType& size, const _SizeType& capacity)\
			{\
				m_pFront = GCCAST(const _DataType*)(p);\
				m_size = size;\
				m_capacity = capacity;\
			}

#endif