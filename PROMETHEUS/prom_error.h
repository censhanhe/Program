#ifndef 	__PROM_ERROR_H__
#define 	__PROM_ERROR_H__

namespace PROM
{
	class ERROR_SYSTEM
	{
	public:
		GAIA_ENUM_BEGIN(ERROR_TYPE)
			ERROR_TYPE_INTERNAL_WARNING,
			ERROR_TYPE_INTERNAL_ERROR,
			ERROR_TYPE_WARING,
			ERROR_TYPE_ERROR,
		GAIA_ENUM_END(ERROR_TYPE)
		class ErrorBase : public GAIA::Entity
		{
		public:
			GINL ErrorBase(){m_uFileLine = (GAIA::U32)GINVALID;}
			virtual GAIA::U16 getid() const = 0;
			virtual GAIA::U8 getstage() const = 0;
			virtual GAIA::U8 getlevel() const = 0;
			virtual const GAIA::CH* getdesc() const = 0;
			virtual const GAIA::CH* getsample() const = 0;
			GINL GAIA::GVOID setfilename(const GAIA::TCH* pszFileName){m_strFileName = pszFileName;}
			GINL const GAIA::TCH* getfilename() const{return m_strFileName.front_ptr();}
			GINL GAIA::GVOID setfileline(GAIA::U32 uFileLine){m_uFileLine = uFileLine;}
			GINL GAIA::U32 getfileline() const{return m_uFileLine;}
		private:
			__FileName m_strFileName;
			GAIA::U32 m_uFileLine;
		};
		#define PROM_ERROR(id, stage, level, desc, sample) \
			class ERROR_##id : public ErrorBase\
			{\
			public:\
				virtual GAIA::U16 getid() const{return id;}\
				virtual GAIA::U8 getstage() const{return stage;}\
				virtual GAIA::U8 getlevel() const{return level;}\
				virtual const GAIA::CH* getdesc() const{return desc;}\
				virtual const GAIA::CH* getsample() const{return sample;}\
			};
		PROM_ERROR(101,		0x0000, 0x0000, "pipeline execute failed, no pipeline context returned", "");
		PROM_ERROR(102,		0x0000, 0x0000, "command parameters error", "");
		PROM_ERROR(103,		0x0000, 0x0000, "pipeline link structure error", "");
		PROM_ERROR(104,		0x0000, 0x0002, "pipeline output stage result failed", "");
		PROM_ERROR(501,		0x0000, 0x0003, "file specified by -i parameter is not exist", "");
		PROM_ERROR(502,		0x0000, 0x0004, "file not exist", "");
		PROM_ERROR(503,		0x0000, 0x0002, "create file failed", "");
		PROM_ERROR(504,		0x0000, 0x0003, "open file failed", "");
		PROM_ERROR(505,		0x0000, 0x0003, "delete file failed", "");
		PROM_ERROR(506,		0x0000, 0x0002, "create directory failed", "");
		PROM_ERROR(507,		0x0000, 0x0003, "open directory failed", "");
		PROM_ERROR(508,		0x0000, 0x0003, "delete directory failed", "");
		PROM_ERROR(511,		0x0000, 0x0002, "text line analyze failed", "");
		PROM_ERROR(512,		0x0000, 0x0002, "text line save failed", "");
		PROM_ERROR(1001,	0x0000, 0x0002, "allocate size not match the object", "Object* p = (Object*)malloc/calloc/realloc...(sizeof(Object));");
	};

#define PROM_RAISE_FATALERROR(id) \
	do\
	{\
		PROM::ERROR_SYSTEM::ERROR_##id* temp_error = new PROM::ERROR_SYSTEM::ERROR_##id;\
		errs.push_back(temp_error);\
	}while(GAIA::ALWAYSFALSE)

#define PROM_RAISE_FILEERROR(id, filename) \
	do\
	{\
		PROM::ERROR_SYSTEM::ERROR_##id* temp_error = new PROM::ERROR_SYSTEM::ERROR_##id;\
		errs.push_back(temp_error);\
		temp_error->setfilename(filename);\
	}while(GAIA::ALWAYSFALSE)

#define PROM_RAISE_ERROR(id, filename, line) \
	do\
	{\
		PROM::ERROR_SYSTEM::ERROR_##id* temp_error = new PROM::ERROR_SYSTEM::ERROR_##id;\
		errs.push_back(temp_error);\
		temp_error->setfilename(filename);\
		temp_error->setfileline(line);\
	}while(GAIA::ALWAYSFALSE)

	typedef GAIA::CTN::Vector<PROM::ERROR_SYSTEM::ErrorBase*> __ErrorListType;
};

#endif