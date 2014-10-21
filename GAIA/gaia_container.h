#ifndef		__GAIA_CONTAINER_H__
#define		__GAIA_CONTAINER_H__

#define GAIA_CONTAINER_PROXY \
			GINL GAIA::GVOID proxy(const _DataType* p, const _SizeType& size, const _SizeType& capacity)\
			{\
				m_pFront = GCCAST(const _DataType*)(p);\
				m_size = size;\
				m_capacity = capacity;\
			}

#endif