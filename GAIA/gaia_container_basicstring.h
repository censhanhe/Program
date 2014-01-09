#ifndef		__GAIA_CONTAINER_BASICSTRING_H__
#define		__GAIA_CONTAINER_BASICSTRING_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType> class BasicString
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			GINL BasicString(){}
			GINL BasicString(const _DataType& t){}
			GINL BasicString(const _DataType* pSource){}
			GINL BasicString(const BasicString<_DataType, _SizeType>& src){}
			GINL BasicString(const GAIA::N8& t);
			GINL BasicString(const GAIA::N16& t);
			GINL BasicString(const GAIA::N32& t);
			GINL BasicString(const GAIA::N64& t);
			GINL BasicString(const GAIA::N128& t);
			GINL BasicString(const GAIA::U8& t);
			GINL BasicString(const GAIA::U16& t);
			GINL BasicString(const GAIA::U32& t);
			GINL BasicString(const GAIA::U64& t);
			GINL BasicString(const GAIA::U128& t);
			GINL BasicString(const GAIA::F32& t);
			GINL BasicString(const GAIA::F64& t);
			GINL BasicString(const GAIA::BL& t);
			GINL ~BasicString(){}
			GINL GAIA::BL empty() const;
			GINL GAIA::GVOID clear();
			GINL _SizeType size() const;
			GINL _SizeType capacity() const;
			GINL GAIA::GVOID destory();
			GINL _DataType* front();
			GINL const _DataType* front() const;
			GINL GAIA::GVOID inverse();
			GINL GAIA::BL insert(const _DataType& t, const _SizeType& index);
			GINL GAIA::BL insert(const _DataType* p, const _SizeType& index);
			GINL GAIA::BL insert(const BasicString<_DataType, _SizeType>& src);
			GINL GAIA::BL erase(const _SizeType& index);
			GINL GAIA::BL erase(const _SizeType& index_start, const _SizeType& index_end);
			GINL GAIA::BL erase(const _DataType& t, const _SizeType& index);
			GINL GAIA::BL erase(const _DataType* p, const _SizeType& index);
			GINL GAIA::BL erase(const BasicString<_DataType, _SizeType>& src);
			GINL _SizeType find(const _DataType& f, const _SizeType& index) const;
			GINL _SizeType find(const _DataType* pSource, const _SizeType& index) const;
			GINL _SizeType find(const BasicString<_DataType, _SizeType>& src) const;
			GINL _SizeType rfind(const _DataType& f, const _SizeType& index) const;
			GINL _SizeType rfind(const _DataType* pSource, const _SizeType& index) const;
			GINL _SizeType rfind(const BasicString<_DataType, _SizeType>& src) const;
			GINL _SizeType replace(const _DataType& src, const _DataType& dst);
			GINL _SizeType replace(const _DataType* pSrc, const _DataType* pDst);
			GINL _SizeType replace(const BasicString<_DataType, _SizeType>& src, const BasicString<_DataType, _SizeType>& dst);
			GINL BasicString<_DataType, _SizeType>& left(const _SizeType& index) const;
			GINL BasicString<_DataType, _SizeType>& right(const _SizeType& index) const;
			GINL BasicString<_DataType, _SizeType>& mid(const _SizeType& index_start, const _SizeType& index_end) const;
			GINL BasicString<_DataType, _SizeType>& trim_left(const _DataType& t);
			GINL BasicString<_DataType, _SizeType>& trim_left(const _DataType* p);
			GINL BasicString<_DataType, _SizeType>& trim_left(const BasicString<_DataType, _SizeType>& src);
			GINL BasicString<_DataType, _SizeType>& trim_right(const _DataType& t);
			GINL BasicString<_DataType, _SizeType>& trim_right(const _DataType* p);
			GINL BasicString<_DataType, _SizeType>& trim_right(const BasicString<_DataType, _SizeType>& src);			
			GINL BasicString<_DataType, _SizeType>& operator = (const BasicString<_DataType, _SizeType>& src);
			GINL BasicString<_DataType, _SizeType>& operator = (const _DataType& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const _DataType* p);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N8& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N16& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N32& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N64& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::N128& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U8& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U16& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U32& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U64& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::U128& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::F32& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::F64& t);
			GINL BasicString<_DataType, _SizeType>& operator = (const GAIA::BL& t);
			GINL BasicString<_DataType, _SizeType>& operator += (const BasicString<_DataType, _SizeType>& src);
			GINL BasicString<_DataType, _SizeType>& operator += (const _DataType& t);
			GINL BasicString<_DataType, _SizeType>& operator += (const _DataType* p);
			GINL BasicString<_DataType, _SizeType> operator + (const BasicString<_DataType, _SizeType>& src) const;
			GINL BasicString<_DataType, _SizeType> operator + (const _DataType& t) const;
			GINL BasicString<_DataType, _SizeType> operator + (const _DataType* p) const;
			GINL GAIA::BL operator == (const BasicString<_DataType, _SizeType>& src) const;
			GINL GAIA::BL operator == (const _DataType& t) const;
			GINL GAIA::BL operator == (const _DataType* p) const;
			GINL GAIA::BL operator != (const BasicString<_DataType, _SizeType>& src) const;
			GINL GAIA::BL operator != (const _DataType& t) const;
			GINL GAIA::BL operator != (const _DataType* p) const;
			GINL GAIA::BL operator >= (const BasicString<_DataType, _SizeType>& src) const;
			GINL GAIA::BL operator >= (const _DataType& t) const;
			GINL GAIA::BL operator >= (const _DataType* p) const;
			GINL GAIA::BL operator <= (const BasicString<_DataType, _SizeType>& src) const;
			GINL GAIA::BL operator <= (const _DataType& t) const;
			GINL GAIA::BL operator <= (const _DataType* p) const;
			GINL GAIA::BL operator > (const BasicString<_DataType, _SizeType>& src) const;
			GINL GAIA::BL operator > (const _DataType& t) const;
			GINL GAIA::BL operator > (const _DataType* p) const;
			GINL GAIA::BL operator < (const BasicString<_DataType, _SizeType>& src) const;
			GINL GAIA::BL operator < (const _DataType& t) const;
			GINL GAIA::BL operator < (const _DataType* p) const;
			GINL const _DataType& operator[](const _SizeType& index) const;
			GINL _DataType& operator[](const _SizeType& index);
			GINL operator _DataType*();
			GINL operator const _DataType*() const;
			GINL operator GAIA::UM() const;
			GINL operator GAIA::NM() const;
			GINL operator GAIA::N8() const;
			GINL operator GAIA::N16() const;
			GINL operator GAIA::N32() const;
			GINL operator GAIA::N64() const;
			GINL operator GAIA::N128() const;
			GINL operator GAIA::U8() const;
			GINL operator GAIA::U16() const;
			GINL operator GAIA::U32() const;
			GINL operator GAIA::U64() const;
			GINL operator GAIA::U128() const;
			GINL operator GAIA::F32() const;
			GINL operator GAIA::F64() const;
			GINL operator GAIA::BL() const;
		private:
			_DataType* m_pData;
			_SizeType m_size;
			_SizeType m_capacity;
		};
	};
};

#endif
