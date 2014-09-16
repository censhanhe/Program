#ifndef		__PROM_COMMON_H__
#define		__PROM_COMMON_H__

namespace PROM
{
	typedef GAIA::TCH __FileNameChar;
	typedef GAIA::CTN::TString __FileName;
	typedef GAIA::CTN::TString __WordType;

	template<typename _DataType> GAIA::BL is_word_char(_DataType t)
	{
		if(t >= 'a' && t <= 'z' ||
			t >= 'A' && t <= 'Z' ||
			t >= '0' && t <= '9' ||
			t == '_')
			return GAIA::True;
		return GAIA::False;
	}
	template<typename _DataType> GAIA::BL is_blank_char(_DataType t)
	{
		if(t == ' ' || t == '\t')
			return GAIA::True;
		return GAIA::False;
	}
};

#endif