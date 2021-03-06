#ifndef 	__GAIA_IO_FILEIO_H__
#define 	__GAIA_IO_FILEIO_H__

namespace GAIA
{
	namespace IO
	{
		class FileIO : public virtual IO
		{
		public:
			GINL FileIO(){this->init();}
			GINL ~FileIO(){}
			virtual GAIA::FWORK::ClsID GetClassID() const{return GAIA::FWORK::CLSID_IO_FILEIO;}
			virtual GAIA::BL InstanceBegin(GAIA::GVOID* pParameter)
			{
				if(this->IsInstanceBegin())
					return GAIA::False;
				if(pParameter == GNIL)
					return GAIA::False;
				if(!GAIA::FWORK::Instance::InstanceBegin(pParameter))
					return GAIA::False;
				m_file = GSCAST(GAIA::FSYS::FileBase*)(pParameter);
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
				if(this->IsOpen())
					this->Close();
				if(pszIOName == GNIL)
					return GAIA::False;
				if(uTypeMask & GAIA::IO::IO::IO_TYPE_READ)
				{
					GAIA::BL bRet = m_file->Open(pszIOName, GAIA::FSYS::File::OPEN_TYPE_READ);
					if(bRet)
						m_uTypeMask = uTypeMask;
					return bRet;
				}
				else if(uTypeMask & GAIA::IO::IO::IO_TYPE_WRITE)
				{
					GAIA::BL bRet = m_file->Open(pszIOName, GAIA::FSYS::File::OPEN_TYPE_WRITE | GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS);
					if(bRet)
						m_uTypeMask = uTypeMask;
					return bRet;
				}
				else
					return GAIA::False;
			}
			virtual GAIA::BL Close(){this->init(); return m_file->Close();}
			virtual GAIA::BL IsOpen() const{return m_file->IsOpen();}
			virtual GAIA::UM GetType() const{return m_uTypeMask;}
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::U32 uSize)
			{
				if(!this->IsOpen())
					return GAIA::False;
				GAIA::N64 nReaded = m_file->Read(pData, uSize);
				if(nReaded == (GAIA::N64)uSize)
					return GAIA::True;
				m_file->Seek(SEEK_TYPE_FORWARD, nReaded);
				return GAIA::False;
			}
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::U32 uSize)
			{
				if(!this->IsOpen())
					return GAIA::False;
				GAIA::N64 nWrite = m_file->Write(pData, uSize);
				if(nWrite == (GAIA::N64)uSize)
					return GAIA::True;
				m_file->Seek(SEEK_TYPE_FORWARD, nWrite);
				return GAIA::False;
			}
		private:
			GINL GAIA::GVOID init(){m_uTypeMask = 0; m_file = GNIL;}
		private:
			GAIA::UM m_uTypeMask;
			GAIA::FSYS::FileBase* m_file;
		};
	};
};

#endif
