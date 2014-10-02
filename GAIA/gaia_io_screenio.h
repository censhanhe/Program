#ifndef		__GAIA_IO_SCREEN_IO_H__
#define		__GAIA_IO_SCREEN_IO_H__

namespace GAIA
{
	namespace IO
	{
		class ScreenIO : public virtual IO
		{
		public:
			GINL ScreenIO(){this->init();}
			GINL ~ScreenIO(){}
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
				if(this->IsOpen())
					this->Close();
				if(!GAIA::FWORK::Instance::InstanceEnd())
					return GAIA::False;
				return GAIA::True;
			}
			virtual GAIA::BL IsInstanceBegin() const{return GAIA::FWORK::Instance::IsInstanceBegin();}
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
				return GAIA::True;
			}
			virtual GAIA::UM GetType() const
			{
				return GAIA::True;
			}
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::U32 uSize)
			{
				return GAIA::True;
			}
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::U32 uSize)
			{
				return GAIA::True;
			}
		private:
			GINL GAIA::GVOID init(){}
		};
	};
};

#endif
