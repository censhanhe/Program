#ifndef		__GAIA_CONTAINER_COOPERATION_H__
#define		__GAIA_CONTAINER_COOPERATION_H__

namespace GAIA
{
	namespace CONTAINER
	{
		/* BasicChars and BasicString's convert. */
		template<typename _DataType, typename _SizeType, _SizeType size>
		GAIA::CONTAINER::BasicChars<_DataType, _SizeType, size> operator + (
			const GAIA::CONTAINER::BasicChars<_DataType, _SizeType, size>& p1, 
			const GAIA::CONTAINER::BasicString<_DataType, _SizeType>& p2)
		{
			GAIA::CONTAINER::BasicChars<_DataType, _SizeType, size> ret = p1;
			ret += p2.front_ptr();
			return ret;
		}

		template<typename _DataType, typename _SizeType, _SizeType size>
		GAIA::CONTAINER::BasicString<_DataType, _SizeType> operator + (
			const GAIA::CONTAINER::BasicString<_DataType, _SizeType>& p1, 
			const GAIA::CONTAINER::BasicChars<_DataType, _SizeType, size>& p2)
		{
			GAIA::CONTAINER::BasicString<_DataType, _SizeType> ret = p1;
			ret += p2.front_ptr();
			return ret;
		}

		template<typename _DataType, typename _SizeType, _SizeType size>
		GAIA::CONTAINER::BasicChars<_DataType, _SizeType, size>& operator += (
			GAIA::CONTAINER::BasicChars<_DataType, _SizeType, size>& p1, 
			const GAIA::CONTAINER::BasicString<_DataType, _SizeType>& p2)
		{
			p1 += p2.front_ptr();
			return p1;
		}

		template<typename _DataType, typename _SizeType, _SizeType size>
		GAIA::CONTAINER::BasicString<_DataType, _SizeType>& operator += (
			GAIA::CONTAINER::BasicString<_DataType, _SizeType>& p1, 
			const GAIA::CONTAINER::BasicChars<_DataType, _SizeType, size>& p2)
		{
			p1 += p2.front_ptr();
			return p1;
		}
	};
};

#endif