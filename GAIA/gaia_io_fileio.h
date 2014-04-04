#ifndef 	__GAIA_IO_FILEIO_H__
#define 	__GAIA_IO_FILEIO_H__

namespace GAIA
{
	namespace IO
	{
		class FileIO : public IO
		{
		public:
			GINL FileIO(){this->init();}
			GINL ~FileIO(){}
			virtual GAIA::FRAMEWORK::ClsID GetClassID() const{return GAIA::FRAMEWORK::GAIA_CLSID_FILEIO;}
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
				if(this->IsOpen())
					this->Close();
				if(pszIOName == GNULL)
					return GAIA::False;
				if(uTypeMask & GAIA::IO::IO::IO_TYPE_READ)
				{
					GAIA::BL bRet = m_file.Open(pszIOName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_READ);
					if(bRet)
						m_uTypeMask = uTypeMask;
					return bRet;
				}
				else if(uTypeMask & GAIA::IO::IO::IO_TYPE_WRITE)
				{
					GAIA::BL bRet = m_file.Open(pszIOName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE | GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS);
					if(bRet)
						m_uTypeMask = uTypeMask;
					return bRet;
				}
				else
					return GAIA::False;
			}
			virtual GAIA::BL Close(){this->init(); return m_file.Close();}
			virtual GAIA::BL IsOpen() const{return m_file.IsOpen();}	
			virtual GAIA::UM GetType() const{return m_uTypeMask;}
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::U32 uSize)
			{
				if(!this->IsOpen())
					return GAIA::False;
				GAIA::N64 nReaded = m_file.Read(pData, uSize);
				if(nReaded == (GAIA::N64)uSize)
					return GAIA::True;
				m_file.Seek(SEEK_TYPE_FORWARD, nReaded);
				return GAIA::False;
			}
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::U32 uSize)
			{
				if(!this->IsOpen())
					return GAIA::False;
				GAIA::N64 nWrite = m_file.Write(pData, uSize);
				if(nWrite == (GAIA::N64)uSize)
					return GAIA::True;
				m_file.Seek(SEEK_TYPE_FORWARD, nWrite);
				return GAIA::False;
			}
		private:
			GINL GAIA::GVOID init(){m_bBegin = GAIA::False; m_uTypeMask = 0;}
		private:
			GAIA::U8 m_bBegin : 1;
			GAIA::UM m_uTypeMask;
			GAIA::FILESYSTEM::File m_file;
		};
	};
};

#endif
