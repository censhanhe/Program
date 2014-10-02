#ifndef		__GAIA_SERIALIZE_SERIALIZER_H__
#define		__GAIA_SERIALIZE_SERIALIZER_H__

namespace GAIA
{
	namespace SERIALIZER
	{
		class Serializer : public virtual GAIA::FWORK::Instance
		{
		public:
			GINL Serializer(){this->init();}
			GINL ~Serializer(){}
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_IO_SCREENIO;}
			virtual GAIA::BL InstanceBegin(GAIA::GVOID* pParameter)
			{
				if(this->IsInstanceBegin())
					return GAIA::False;
				if(!GAIA::FWORK::Instance::InstanceBegin(pParameter))
					return GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL InstanceEnd()
			{
				if(!this->IsInstanceBegin())
					return GAIA::False;
				if(m_pIO != GNIL)
				{
					m_pIO->Release();
					m_pIO = GNIL;
				}
				if(!GAIA::FWORK::Instance::InstanceEnd())
					return GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsInstanceBegin() const{return GAIA::FWORK::Instance::IsInstanceBegin();}
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
			GINL GAIA::GVOID init(){m_pIO = GNIL;}
		private:
			GAIA::IO::IO* m_pIO;
		};
	};
};

#endif
