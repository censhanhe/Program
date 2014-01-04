#ifndef		__GAIA_CONTAINER_BASICARRAY_H__
#define		__GAIA_CONTAINER_BASICARRAY_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, _SizeType _Size> class BasicArray
		{
		public:
			BasicArray(){m_size = 0;}
			GINL _SizeType size(){return m_size;}
			GINL GAIA::BL push_back(const _DataType& t){if(m_size < _Size){m_data[m_size++] = t; return GAIA::True;} else return GAIA::False;}
			GINL GAIA::BL pop_back(){if(m_size > 0){m_size--; return GAIA::True;} else return GAIA::False;}
			GINL const _DataType& back(){return m_data[m_size - 1];}
			GINL GAIA::GVOID resize(_SizeType size){m_size = size;}
			GINL GAIA::GVOID reset(const _DataType& t);
			GINL GAIA::GVOID sort();
			GINL GAIA::GVOID reverse();
			GINL _SizeType find(_SizeType index) const;
			GINL _SizeType rfind(_SizeType index) const;
			GINL GAIA::BL replace(const _DataType& t, _SizeType index);
			GINL GAIA::BL replace_all(const _DataType& t, _SizeType index);
			GINL GAIA::BL erase(_SizeType index);
			GINL const _DataType& operator [] (_SizeType index) const{return m_data[index];}
			GINL _DataType& operator [] (_SizeType index){return m_data[index];}
			GINL BasicArray& operator << (const _DataType& t){this->push_back(t); return *this;}
			GINL BasicArray& operator >> (const _DataType& t){this->push_back(t); return *this;}
		private:
			_DataType m_data[_Size];
			_SizeType m_size;
		};
	};
};

#endif
