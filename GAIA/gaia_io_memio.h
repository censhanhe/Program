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
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_MEMIO;}
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
				if(this->IsOpen())
					this->Close();
				m_bBegin = GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsBegin() const{return m_bBegin;}
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
			GINL GAIA::GVOID init(){m_bBegin = GAIA::False; m_uTypeMask = 0;}
		private:
			GAIA::U8 m_bBegin : 1;
			GAIA::UM m_uTypeMask;
		};
	};
};

#endif
