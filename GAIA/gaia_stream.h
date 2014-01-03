#ifndef		__GAIA_STREAM_H__
#define		__GAIA_STREAM_H__

namespace GAIA
{
	template <typename _DataSizeType> class Stream
	{
	public:
		ENUM_BEGIN(BIND_TYPE)
			BIND_TYPE_READ			= 0x00000001,
			BIND_TYPE_WRITE			= 0x00000002,
		ENUM_END

	public:
		virtual	GAIA::BL		Bind(const GAIA::TCHAR* pszSource, GAIA::UM type) = 0;
		virtual GAIA::BL		Unbind() const = 0;
		virtual GAIA::TCHAR*	GetBindingSourceName() const = 0;
		virtual _DataSizeType	GetSize() const = 0;
		virtual GAIA::BL		Seek(_DataSizeType position, N8 nDirection) = 0;
		virtual GAIA::BL		Read() = 0;
		virtual GAIA::BL		Write() = 0;
	};
};

#endif