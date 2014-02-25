#ifndef		__GAIA_DIRECTORY_INDP_H__
#define		__GAIA_DIRECTORY_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#endif

namespace GAIA
{
	namespace FILESYSTEM
	{
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Directory::GetWorkingDirectory(GAIA::CONTAINER::AString& result) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::GCH szPath[MAX_PATH];
			::GetCurrentDirectoryA(MAX_PATH, szPath);
			result = szPath;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Directory::GetBinaryDirectory(GAIA::CONTAINER::AString& result) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::GCH szPath[MAX_PATH];
			::GetModuleFileNameA(GNULL, szPath, MAX_PATH);
			GAIA::GCH* p = GAIA::ALGORITHM::stridropr(szPath, "\\/");
			result = szPath;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Create(const GAIA::GCH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::UM uAttr = ::GetFileAttributesA(pszName);
			if(uAttr != GINVALID && uAttr & FILE_ATTRIBUTE_DIRECTORY)
				return GAIA::False;
			if(bOverlapped)
			{
				const GAIA::GCH* p = pszName;
				p = GAIA::ALGORITHM::stridrop(p, "\\/");
				if(p == GNULL)
					return GAIA::False;
				++p;
				while((p = GAIA::ALGORITHM::stridrop(p, "\\/\0")) != GNULL)
				{
					GAIA::GCH sz[MAX_PATH];
					GAIA::ALGORITHM::memcpy(sz, pszName, (p - pszName + 1) * sizeof(GAIA::GCH));
					sz[p - pszName + 1] = 0;
					if(!::CreateDirectoryA(sz, NULL))
						return GAIA::False;
					if(*p == 0)
						break;
					else
						++p;
				}
				return GAIA::True;
			}
			else
			{
				if(::CreateDirectoryA(pszName, GNULL))
					return GAIA::True;
				return GAIA::False;
			}
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Remove(const GAIA::GCH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(bOverlapped)
			{
				WIN32_FIND_DATAA fdata;
				HANDLE hFF = ::FindFirstFileA(pszName, &fdata);
				if(hFF == (HANDLE)GINVALID)
					return GAIA::False;
				GAIA::BL bFinded = GAIA::True;
				while(bFinded)
				{
					GAIA::GCH sz[MAX_PATH];
					GAIA::ALGORITHM::strcpy(sz, pszName);
					const GAIA::GCH* p = GAIA::ALGORITHM::strend(pszName);
					--p;
					if(*p != '\\' && *p != '/')
						GAIA::ALGORITHM::strcat(sz, "/");
					GAIA::ALGORITHM::strcat(sz, fdata.cFileName);
					if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if(!this->Remove(sz, bOverlapped))
						{
							::FindClose(hFF);
							return GAIA::False;
						}
					}
					else
					{
						if(!this->RemoveFile(sz))
						{
							::FindClose(hFF);
							return GAIA::False;
						}
					}
					bFinded = ::FindNextFileA(hFF, &fdata);
				}
				::FindClose(hFF);
				return GAIA::True;
			}
			else
			{
				if(::RemoveDirectoryA(pszName))
					return GAIA::True;
				return GAIA::False;
			}
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::RemoveFile(const GAIA::GCH* pszName)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::DeleteFileA(pszName))
				return GAIA::True;
			return GAIA::False;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Copy(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst)
		{
			if(GAIA::ALGORITHM::stremp(pszSrc))
				return GAIA::False;
			if(GAIA::ALGORITHM::stremp(pszDst))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::CopyFileA(pszSrc, pszDst, GAIA::False))
				return GAIA::True;
			return GAIA::False;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Move(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst)
		{
			if(GAIA::ALGORITHM::stremp(pszSrc))
				return GAIA::False;
			if(GAIA::ALGORITHM::stremp(pszDst))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::MoveFileA(pszSrc, pszDst))
				return GAIA::True;
			return GAIA::False;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Collect(const GAIA::GCH* pszName, const GAIA::GCH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult)
		{
			if(GAIA::ALGORITHM::stremp(pszFilter))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			WIN32_FIND_DATAA fdata;
			HANDLE hFF = ::FindFirstFileA(pszName, &fdata);
			if(hFF == (HANDLE)GINVALID)
				return GAIA::False;
			GAIA::BL bFinded = GAIA::True;
			while(bFinded)
			{
				GAIA::GCH sz[MAX_PATH];
				GAIA::ALGORITHM::strcpy(sz, pszName);
				const GAIA::GCH* p = GAIA::ALGORITHM::strend(pszName);
				--p;
				if(*p != '\\' && *p != '/')
					GAIA::ALGORITHM::strcat(sz, "/");
				GAIA::ALGORITHM::strcat(sz, fdata.cFileName);
				if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if(bOverlapped)
						this->Collect(sz, pszFilter, bOverlapped, treeResult);
				}
				else
				{
				}
				bFinded = ::FindNextFileA(hFF, &fdata);
			}
			::FindClose(hFF);
			return GAIA::True;
		#else

		#endif
		}
	};
};

#endif