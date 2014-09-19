#ifndef		__GAIA_SERIALIZE_SERIALIZER_H__
#define		__GAIA_SERIALIZE_SERIALIZER_H__

namespace GAIA
{
	namespace SERIALIZER
	{
		class Serializer : public virtual GAIA::FRAMEWORK::Instance
		{
		public:
			GINL Serializer(){this->init();}
			GINL ~Serializer(){}
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::CLSID_SCREENIO;}
			virtual GAIA::BL Begin(GAIA::GVOID* pParameter)
			{
				if(this->IsBegin())
					return GAIA::False;
				m_bBegin = GAIA::True;
				return GAIA::True;
			}
			virtual GAIA::BL End()
			{
				if(!this->IsBegin())
					return GAIA::False;
				if(m_pIO != GNIL)
				{
					m_pIO->Release();
					m_pIO = GNIL;
				}
				m_bBegin = GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsBegin() const{return m_bBegin;}
			GINL GAIA::BL BindIO(GAIA::IO::IO* pIO)
			{
				if(pIO == m_pIO)
					return GAIA::True;
				if(!pIO->IsOpen())
					return GAIA::False;
				if(m_pIO != GNIL)
					m_pIO->Release();
				if(pIO != GNIL)
					pIO->Reference();
				m_pIO = pIO;
				return GAIA::True;
			}
			GINL GAIA::IO::IO* GetBindIO() const
			{
				if(m_pIO != GNIL)
					m_pIO->Reference();
				return m_pIO;
			}
			template<typename _ParamType> Serializer& operator << (const _ParamType& t)
			{
				if(m_pIO == GNIL)
					return *this;
				SerializerProc sp;
				sp.write(this, t);
				return *this;
			}
			template<typename _ParamType> Serializer& operator >> (_ParamType& t)
			{
				if(m_pIO == GNIL)
					return *this;
				SerializerProc sp;
				sp.read(this, t);
				return *this;
			}
		private:
			GINL GAIA::GVOID init(){m_bBegin = GAIA::False; m_pIO = GNIL;}
		private:
			GAIA::U8 m_bBegin : 1;
			GAIA::IO::IO* m_pIO;
		};
	};
};

#endif
