#ifndef 	__GAIA_IO_MEMIO_H__
#define 	__GAIA_IO_MEMIO_H__

namespace GAIA
{
	namespace IO
	{
		class MemIO : public virtual IO
		{
		public:
			GINL MemIO(){this->init();}
			GINL ~MemIO(){}
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_IO_MEMIO;}
			virtual GAIA::BL Begin(GAIA::GVOID* pParameter)
			{
				if(this->IsBegin())
					return GAIA::False;
				if(!GAIA::FWORK::Instance::Begin(pParameter))
					return GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL End()
			{
				if(!this->IsBegin())
					return GAIA::False;
				if(this->IsOpen())
					this->Close();
				if(!GAIA::FWORK::Instance::End())
					return GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsBegin() const{return GAIA::FWORK::Instance::IsBegin();}
			virtual GAIA::BL Open(const GAIA::TCH* pszIOName, GAIA::UM uTypeMask)
			{
				return GAIA::True;
			}
			virtual GAIA::BL Close()
			{
				return GAIA::True;
			}
			virtual GAIA::BL IsOpen() const
			{
				return GAIA::False;
			}
			virtual GAIA::UM GetType() const{return m_uTypeMask;}
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::U32 uSize)
			{
				return GAIA::True;
			}
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::U32 uSize)
			{
				return GAIA::False;
			}
		private:
			GINL GAIA::GVOID init(){m_uTypeMask = 0;}
		private:
			GAIA::UM m_uTypeMask;
		};
	};
};

#endif
