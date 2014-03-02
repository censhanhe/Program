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
			virtual GAIA::BL Open(const GAIA::GCH* pszIOName)
			{
				if(pszIOName == GNULL)
					return GAIA::False;
				return m_file.Open(pszIOName, );
			}
			virtual GAIA::BL Close(){return m_file.Close();}
			virtual GAIA::BL IsOpen() const{return m_file.IsOpen();}
			virtual GAIA::BL Read(GAIA::GVOID* pData, GAIA::UM uSize)
			{
			}
			virtual GAIA::BL Write(const GAIA::GVOID* pData, GAIA::UM uSize)
			{
			}
		private:
			GAIA::FILESYSTEM::File m_file;
		};
	};
};

#endif
