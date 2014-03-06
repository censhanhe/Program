#ifndef		__GAIA_IO_SCREEN_IO_H__
#define		__GAIA_IO_SCREEN_IO_H__

namespace GAIA
{
	namespace IO
	{
		class ScreenIO : public IO
		{
		public:
			GINL ScreenIO(){this->init();}
			GINL ~ScreenIO(){}
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::GAIA_CLSID_SCREENIO;}
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
			virtual GAIA::BL Open(const GAIA::GCH* pszIOName, GAIA::UM uTypeMask)
			{
				return GAIA::True;
			}
			virtual GAIA::BL Close()
			{
				return GAIA::True;
			}
			virtual GAIA::BL IsOpen() const
			{
				return GAIA::True;
			}
			virtual GAIA::UM GetType() const
			{
				return GAIA::True;
			}
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize)
			{
				return GAIA::True;
			}
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize)
			{
				return GAIA::True;
			}
		private:
			GINL GAIA::GVOID init(){m_bBegin = GAIA::False;}
		private:
			GAIA::U8 m_bBegin : 1;
		};
	};
};

#endif
