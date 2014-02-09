#ifndef		__GAIA_CONTAINER_PACKAGE_H__
#define		__GAIA_CONTAINER_PACKAGE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeIncreaserType, typename _SizeType> BasicPackage
		{
		public:
			typedef _SizeIncreaserType _sizeincreasertype;
			typedef _SizeType _sizetype;
		public:
			typedef BasicPackage<_SizeIncreaserType, _SizeType> __MyType;
			typedef GAIA::CONTAINER::BasicBuffer<_SizeIncreaserType, _SizeType> __BufferType;
		public:
			GINL Package(){this->init();}
			GINL Package(const __MyType& src){this->init();}
			GINL ~Package(){}
			GINL GAIA::BL empty() const{}
			GINL _SizeType size() const{}
			GINL _SizeType element_size() const{}
			GINL _SizeType capacity() const{}
			GINL GAIA::GVOID clear(){}
			GINL GAIA::GVOID destroy(){}
			GINL __MyType operator << (const __BufferType& t){return *this;}
			template <typename _ParamType> GINL __MyType& operator << (const _ParamType& t){return *this;}
			GINL __MyType operator >> (__BufferType& t){return *this;}
			template <typename _ParamType> GINL __MyType& operator >> (const _ParamType& t){return *this;}
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
			GINL GAIA::GVOID init(){m_esize = 0;}
		private:
			__BufferType m_buf;
			_SizeType m_esize;
		};
	};
};

#endif
