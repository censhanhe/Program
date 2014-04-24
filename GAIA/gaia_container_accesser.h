#ifndef 	__GAIA_CONTAINER_ACCESSER_H__
#define 	__GAIA_CONTAINER_ACCESSER_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType> class Accesser : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(BIND_TYPE)
				BIND_TYPE_MEM,
				BIND_TYPE_FILE,
			GAIA_ENUM_END(BIND_TYPE)

			GAIA_ENUM_BEGIN(ACCESS_TYPE)
				ACCESS_TYPE_READ = 1 << 0,
				ACCESS_TYPE_WRITE = 1 << 1,
			GAIA_ENUM_END(ACCESS_TYPE)
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			typedef Accesser<_DataType, _SizeType> __MyType;
		public:
			GINL Accesser();
			GINL Accesser(const __MyType& src);
			GINL ~Accesser();
			GINL GAIA::BL bind(GAIA::FILESYSTEM::File* pFile, const _SizeType& size);
			GINL GAIA::BL bind(_DataType* p, const _SizeType& size);
			GINL GAIA::BL unbind();
			GINL GAIA::BL empty() const;
			GINL const _SizeType& size() const;
			GINL GAIA::BL offset(const _SizeType& offsetsize);
			GINL const _SizeType& offset() const;
			GINL GAIA::GVOID stride(const _SizeType& stride);
			GINL const _SizeType& stride() const;
			GINL __MyType& operator = (const __MyType& src);
			GINL __MyType& operator ++ ();
			GINL __MyType& operator -- ();
			GINL __MyType& operator += (const _SizeType& size);
			GINL __MyType& operator -= (const _SizeType& size);
		private:
			GINL __MyType& operator ++ (GAIA::N32);
			GINL __MyType& operator -- (GAIA::N32);
		private:
			BIND_TYPE m_bindtype;
			GAIA::UM m_atm; // atm means access type mask.
			_DataType* m_p;
			GAIA::FILESYSTEM::File* m_file;
			_SizeType m_size;
			_SizeType m_offset;
			_SizeType m_stride;
		};
	};
};

#endif
