#ifndef		__GAIA_CONTAINER_BASICSTACKSTRING_H__
#define		__GAIA_CONTAINER_BASICSTACKSTRING_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType, _SizeType _Size> class BasicStackString
		{
		public:
			GINL BasicStackString(){}
			GINL BasicStackString(const _DataType* p){this->operator = (p);}
			template <_SizeType _ParamSize> GINL BasicStackString(const BasicStackString<_DataType, _SizeType, _ParamSize>& src){this->operator = (src);}
			GINL ~BasicStackString(){}
			GINL const _SizeType& size() const{return m_size;}
			GINL const _SizeType& capacity() const{return _Size;}
			GINL GAIA::BL empty() const{if(m_size) == 0) return GAIA::True; return GAIA::False;}
			GINL GAIA::GVOID clear() const{m_str[0] = m_size = 0;}
			GINL GAIA::GVOID destroy() const{this->clear();}
			GINL BasicStackString<_DataType, _SizeType, _Size>& operator = (const _DataType* p){}
			template <_SizeType _ParamSize> GINL BasicStackString<_DataType, _SizeType, _Size>& operator = (const BasicStackString<_DataType, _SizeType, _ParamSize>& src){return *this;}
			template <_SizeType _ParamSize> GINL BasicStackString<_DataType, _SizeType, _Size>& operator += (const BasicStackString<_DataType, _SizeType, _ParamSize>& src){return *this;}
			template <_SizeType _ParamSize> GINL GAIA::BL operator == (const _DataType* p) const{}
			GINL GAIA::BL operator != (const _DataType* p) const{}
			GINL GAIA::BL operator >= (const _DataType* p) const{}
			GINL GAIA::BL operator <= (const _DataType* p) const{}
			GINL GAIA::BL operator > (const _DataType* p) const{}
			GINL GAIA::BL operator < (const _DataType* p) const{}
			template <_SizeType _ParamSize> GINL GAIA::BL operator == (const BasicStackString<_DataType, _SizeType, _ParamSize>& src) const{}
			template <_SizeType _ParamSize> GINL GAIA::BL operator != (const BasicStackString<_DataType, _SizeType, _ParamSize>& src) const{}
			template <_SizeType _ParamSize> GINL GAIA::BL operator >= (const BasicStackString<_DataType, _SizeType, _ParamSize>& src) const{}
			template <_SizeType _ParamSize> GINL GAIA::BL operator <= (const BasicStackString<_DataType, _SizeType, _ParamSize>& src) const{}
			template <_SizeType _ParamSize> GINL GAIA::BL operator > (const BasicStackString<_DataType, _SizeType, _ParamSize>& srcp) const{}
			template <_SizeType _ParamSize> GINL GAIA::BL operator < (const BasicStackString<_DataType, _SizeType, _ParamSize>& src) const{}
			GINL operator _DataType*(){return m_str;}

		private:
			_DataType m_str[_Size];
			_SizeType m_size;
		};
	};
};

#endif