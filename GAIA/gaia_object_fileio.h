#ifndef 	__GAIA_OBJECT_FILEIO_H__
#define 	__GAIA_OBJECT_FILEIO_H__

namespace GAIA
{
	namespace OBJECT
	{
		class FileIO : public IO
		{
		public:
			GINL FileIO(){}
			GINL ~FileIO(){}
			virtual GAIA::BL Open(const GAIA::GCH* pszIOName, GAIA::UM uTypeMask)
			{
				if(pszIOName == GNULL)
					return GAIA::False;
				if(uTypeMask & GAIA::OBJECT::IO::IO_TYPE_READ)
					return m_file.Open(pszIOName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_READ);
				else if(uTypeMask & GAIA::OBJECT::IO::IO_TYPE_WRITE)
					return m_file.Open(pszIOName, GAIA::FILESYSTEM::FILE_OPEN_TYPE_WRITE | GAIA::FILESYSTEM::FILE_OPEN_TYPE_CREATEALWAYS);
				else
					return GAIA::False;
			}
			virtual GAIA::BL Close(){return m_file.Close();}
			virtual GAIA::BL IsOpen() const{return m_file.IsOpen();}	
			virtual GAIA::UM GetType() const
			{ 
			}
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize)
			{
				if(this->IsOpen())
					return GAIA::False;
				GAIA::N64 nReaded = m_file.Read(pData, uSize);
				if(nReaded == (GAIA::N64)uSize)
					return GAIA::True;
				m_file.Seek(SEEK_TYPE_FORWARD, nReaded);
				return GAIA::False;
			}
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize)
			{
				if(this->IsOpen())
					return GAIA::False;
				GAIA::N64 nWrite = m_file.Write(pData, uSize);
				if(nWrite == (GAIA::N64)uSize)
					return GAIA::True;
				m_file.Seek(SEEK_TYPE_FORWARD, nWrite);
				return GAIA::False;
			}
		private:
			GAIA::FILESYSTEM::File m_file;
		};
	};
};

#endif
