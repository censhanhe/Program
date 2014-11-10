#ifndef		__GAIA_GLOBAL_DECL_H__
#define		__GAIA_GLOBAL_DECL_H__

/* Global allocator. */
#ifndef GAIA_DEBUG_MEMORYLEAK
	extern GAIA::ALLOCATOR::AllocatorESG g_gaia_globalallocator;
#endif

/* Platform. */
extern GAIA::Platform g_gaia_platform;

/* Locale. */
extern GAIA::SYNC::Lock g_gaia_localelock;
extern GAIA::CHARSET_TYPE g_gaia_charsettype;

/* Log. */
extern GAIA::LOG::Log g_gaia_log;
class DefaultGAIALogCallBack : public GAIA::LOG::Log::CallBack
{
public:
	GINL DefaultGAIALogCallBack()
	{
		this->init();
		g_gaia_log.SetCallBack(this);
	}
	GINL ~DefaultGAIALogCallBack()
	{
		if(m_pFile != GNIL)
		{
			if(m_pFile->IsOpen())
				m_pFile->Close();
			GAIA_DELETE_SAFE(m_pFile);
		}
	}
	virtual GAIA::BL LogWrite(
		const GAIA::TIME::Time& logtime,
		GAIA::LOG::Log::TYPE type,
		GAIA::LOG::Log::__FilterType userfilter,
		const GAIA::TCH* pszLog)
	{
		/* Parameter checkup. */
		GPCHR_NULLSTRPTR_RET(pszLog, GAIA::False);
		GAIA_AST(type < GAIA::LOG::Log::TYPE_MAXENUMCOUNT);
		if(type >= GAIA::LOG::Log::TYPE_MAXENUMCOUNT)
			return GAIA::False;

		/* If the file is not openned, open it. */
		if(m_pFile == GNIL)
		{
			m_pFile = new GAIA::FSYS::File;
			if(!m_pFile->Open(_T("last.log"), GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS | GAIA::FSYS::File::OPEN_TYPE_WRITE))
				return GAIA::False;
		}

		/* Generate the string. */
		GAIA::TCH szLogTime[64];
		logtime.to(szLogTime);
		GAIA::TCH szLogTimeAux[64];
		GAIA::TIME::timemkaux(szLogTime, szLogTimeAux);
		GAIA::TCH szFilter[32];
		GAIA::ALGO::hex2str(GRCAST(const GAIA::U8*)(&userfilter), sizeof(userfilter), szFilter);

		/* Write log to file. */
		m_pFile->WriteText(szLogTimeAux);
		m_pFile->WriteText(_T(" "));
		m_pFile->WriteText(g_gaia_log.GetLogTypeString(type));
		m_pFile->WriteText(_T(" "));
		m_pFile->WriteText(szFilter);
		m_pFile->WriteText(_T(" "));
		m_pFile->WriteText(pszLog);
		m_pFile->WriteText(g_gaia_log.GetLineBreak());
		return GAIA::True;
	}
private:
	GINL GAIA::GVOID init()
	{
		m_pFile = GNIL;
	}
private:
	GAIA::FSYS::File* m_pFile;
};
extern DefaultGAIALogCallBack g_gaia_log_callback;

/* Global canvas list. */
#if GAIA_OS == GAIA_OS_WINDOWS
	extern GAIA::SYNC::Lock g_gaia_windowlistlock;
	extern GAIA::CTN::Set<GAIA::CTN::Ref<GAIA::UI::Canvas> > g_gaia_windowlist;
#endif

#endif