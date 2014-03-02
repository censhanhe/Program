#ifndef		__GAIA_SERIALIZER_H__
#define		__GAIA_SERIALIZER_H__

namespace GAIA
{
	namespace OBJECT
	{
		class Serializer : public GAIA::FRAMEWORK::Instance
		{
		public:
			GINL Serializer(){this->init();}
			GINL ~Serializer(){}
			GINL GAIA::BL BindIO(GAIA::OBJECT::IO* pIO){m_pIO = pIO; return GAIA::True;}
			GINL GAIA::OBJECT::IO* GetBindIO() const{return m_pIO;}
			template<typename _ParamType> GINL Serializer& operator << (const _ParamType& t)
			{
				if(this->GetBindIO() == GNULL)
					return *this;
				return *this;
			}
			template<typename _ParamType> GINL Serializer& operator >> (const _ParamType& t)
			{
				if(this->GetBindIO() == GNULL)
					return *this;
				return *this;
			}
			GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize)
			{
				if(this->GetBindIO() == GNULL)
					return GAIA::False;
				return this->GetBindIO()->Read(pData, uSize);
			}
			GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize)
			{
				if(this->GetBindIO() == GNULL)
					return GAIA::False;
				return this->GetBindIO()->Write(pData, uSize);
			}
		private:
			GINL GAIA::GVOID init(){m_pIO = GNULL;}
		private:
			GAIA::OBJECT::IO* m_pIO;
		};
	};
};

#endif
