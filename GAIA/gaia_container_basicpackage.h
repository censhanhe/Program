#ifndef		__GAIA_CONTAINER_PACKAGE_H__
#define		__GAIA_CONTAINER_PACKAGE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeType, typename _SizeIncreaserType> class BasicPackage
		{
		public:
			typedef _SizeType _sizetype;
			typedef _SizeIncreaserType _sizeincreasertype;
		public:
			typedef BasicBuffer<_SizeType, _SizeIncreaserType> __BufferType;
			typedef BasicPackage<_SizeType, _SizeIncreaserType> __MyType;
		public:
			GINL BasicPackage(){}
			GINL BasicPackage(const __MyType& src){this->operator = (src);}
			GINL ~BasicPackage(){}
			GINL GAIA::BL empty(){return m_buf.empty();}
			GINL _SizeType size() const{return m_buf.size();}
			GINL _SizeType capacity() const{return m_buf.capacity();}
			GINL GAIA::GVOID clear(){return m_buf.clear();}
			GINL GAIA::GVOID destroy(){return m_buf.destroy();}
			GINL GAIA::GVOID resize(const _SizeType& size){m_buf.resize(size);}
			GINL GAIA::GVOID reserve(const _SizeType& size){m_buf.reserve(size);}
			GINL __MyType& operator = (const __MyType& src){m_buf = src.m_buf; return *this;}
		private:
			__BufferType m_buf;
		};
	};
};

#endif
