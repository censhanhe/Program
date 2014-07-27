#ifndef		__GAIA_DIRECTORY_INDP_H__
#define		__GAIA_DIRECTORY_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
#	define NOMINMAX
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <windows.h>
#else
#	include <stdio.h>
#	include <sys/stat.h>
#	include <sys/dir.h>
#	include <dirent.h>
#	include <unistd.h>
#endif

namespace GAIA
{
	namespace FILESYSTEM
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		static const GAIA::U32 MAXPL = MAX_PATH;
	#else
		static const GAIA::U32 MAXPL = 260;
	#endif
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::SetWorkingDirectory(const GAIA::TCH* dir)
		{
			if(GAIA::ALGORITHM::stremp(dir))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				if(::SetCurrentDirectoryA(dir))
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				if(::SetCurrentDirectoryW(dir))
		#	endif
		#else
			if(chdir(dir) == 0)
		#endif
				return GAIA::True;
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Directory::GetWorkingDirectory(GAIA::CONTAINER::TString& result) const
		{
			GAIA::TCH szPath[MAXPL];
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				::GetCurrentDirectoryA(MAXPL, szPath);
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				::GetCurrentDirectoryW(MAXPL, szPath);
		#	endif
		#else
			::getcwd(szPath, MAXPL);
		#endif
			result = szPath;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Directory::GetBinaryDirectory(GAIA::CONTAINER::TString& result) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::TCH szPath[MAXPL];
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				::GetModuleFileNameA(GNULL, szPath, MAXPL);
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				::GetModuleFileNameW(GNULL, szPath, MAXPL);
		#	endif
			GAIA::TCH* p = GAIA::ALGORITHM::strdropr(szPath, _T("/\\"));
			result = szPath;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Create(const GAIA::TCH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
			if(this->Exist(pszName))
				return GAIA::False;
			/* Generate szFind for recursive file collection. */
			GAIA::TCH szFind[MAXPL];
			GAIA::ALGORITHM::strcpy(szFind, pszName);
			GAIA::TCH* p = GAIA::ALGORITHM::strend(szFind);
			--p;
			if(*p != '\\' && *p != '/')
				GAIA::ALGORITHM::strcat(p, _T("/"));
			if(bOverlapped)
			{
				const GAIA::TCH* pCursor = szFind;
			#if GAIA_OS == GAIA_OS_WINDOWS
				/* Jump after Windows-OS disk name. */
				if(GAIA::ALGORITHM::strch(szFind, ':') != GNULL)
				{
					pCursor = GAIA::ALGORITHM::strdrop(pCursor, _T("/\\"));
					if(pCursor == GNULL)
						return GAIA::False;
					++pCursor;
				}
			#endif
				while((pCursor = GAIA::ALGORITHM::strdrop(pCursor, _T("/\\\0"))) != GNULL)
				{
					GAIA::TCH sz[MAXPL];
					GAIA::ALGORITHM::xmemcpy(sz, szFind, (pCursor - szFind + 1) * sizeof(GAIA::TCH));
					sz[pCursor - szFind + 1] = 0;
					if(!this->Exist(sz))
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
					#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
							if(!::CreateDirectoryA(sz, GNULL))
					#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
							if(!::CreateDirectoryW(sz, GNULL))
					#	endif
					#else
						if(mkdir(sz, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
					#endif
							return GAIA::False;
					}
					if(*pCursor == 0)
						break;
					else
						++pCursor;
				}
				return GAIA::True;
			}
			else
			{
			#if GAIA_OS == GAIA_OS_WINDOWS
			#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
					if(::CreateDirectoryA(pszName, GNULL))
			#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					if(::CreateDirectoryW(pszName, GNULL))
			#	endif
			#else
				if(mkdir(pszName, S_IRWXU | S_IRWXG | S_IRWXO) == 0)
			#endif
					return GAIA::True;
				return GAIA::False;
			}
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Remove(const GAIA::TCH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(bOverlapped)
			{
				/* Generate szFind for recursive file collection. */
				GAIA::TCH szFind[MAXPL];
				GAIA::ALGORITHM::strcpy(szFind, pszName);
				GAIA::TCH* p = GAIA::ALGORITHM::strend(szFind);
				--p;
				if(*p != '\\' && *p != '/')
					GAIA::ALGORITHM::strcat(p, _T("/"));
				/* Generate szTarget for FindFirstFile. */
				GAIA::TCH szTarget[MAXPL];
				GAIA::ALGORITHM::strcpy(szTarget, szFind);
				GAIA::ALGORITHM::strcat(szTarget + (p - szFind), _T("*.*"));
			#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					WIN32_FIND_DATAA fdata;
					HANDLE hFF = ::FindFirstFileA(szTarget, &fdata);
			#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					WIN32_FIND_DATAW fdata;
					HANDLE hFF = ::FindFirstFileW(szTarget, &fdata);
			#endif
				if(hFF == (HANDLE)GINVALID)
					return GAIA::False;
				GAIA::BL bFinded = GAIA::True;
				while(bFinded)
				{
					if(GAIA::ALGORITHM::strcmp(fdata.cFileName, _T(".")) == 0 ||
						GAIA::ALGORITHM::strcmp(fdata.cFileName, _T("..")) == 0){}
					else
					{
						GAIA::TCH sz[MAXPL];
						GAIA::ALGORITHM::strcpy(sz, szFind);
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
					}
				#if GAIA_CHARSET == GAIA_CHARSET_ANSI
					bFinded = ::FindNextFileA(hFF, &fdata) != 0;
				#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					bFinded = ::FindNextFileW(hFF, &fdata) != 0;
				#endif
				}
				::FindClose(hFF);
				return this->Remove(pszName, GAIA::False);
			}
			else
			{
			#if GAIA_CHARSET == GAIA_CHARSET_ANSI
				if(::RemoveDirectoryA(pszName))
			#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				if(::RemoveDirectoryW(pszName))
			#endif
					return GAIA::True;
				return GAIA::False;
			}
		#else
			if(bOverlapped)
			{
				/* Generate szFind for recursive file collection. */
				GAIA::TCH szFind[MAXPL];
				GAIA::ALGORITHM::strcpy(szFind, pszName);
				GAIA::TCH* p = GAIA::ALGORITHM::strend(szFind);
				--p;
				if(*p != '/')
					GAIA::ALGORITHM::strcat(p, _T("/"));
				/* find */
				DIR* pdir = opendir(pszName);
				if(pdir == GNULL)
					return GAIA::False;
				dirent* pdirent;
				while((pdirent = readdir(pdir)) != GNULL)
				{
					if(GAIA::ALGORITHM::strcmp(pdirent->d_name, _T(".")) == 0 ||
						GAIA::ALGORITHM::strcmp(pdirent->d_name, _T("..")) == 0){}
					else
					{
						struct stat s;
						GAIA::TCH sz[MAXPL];
						GAIA::ALGORITHM::strcpy(sz, szFind);
						GAIA::ALGORITHM::strcat(sz, pdirent->d_name);
						if(lstat(sz, &s) >= 0)
						{
							if(S_ISDIR(s.st_mode))
							{
								if(!this->Remove(sz, bOverlapped))
								{
									closedir(pdir);
									return GAIA::False;
								}
							}
							else
							{
								if(!this->RemoveFile(sz))
								{
									closedir(pdir);
									return GAIA::False;
								}
							}
						}
					}
				}
				closedir(pdir);
				return this->Remove(pszName, GAIA::False);
			}
			else
			{
				if(rmdir(pszName) == 0)
					return GAIA::True;
				return GAIA::False;
			}
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Exist(const GAIA::TCH* pszName) const
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				DWORD dwFileAttribute = ::GetFileAttributesA(pszName);
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				DWORD dwFileAttribute = ::GetFileAttributesW(pszName);
		#	endif
			if(dwFileAttribute == INVALID_FILE_ATTRIBUTES)
				return GAIA::False;
			if(dwFileAttribute & FILE_ATTRIBUTE_DIRECTORY)
				return GAIA::True;
			return GAIA::False;
		#else
			struct stat s;
			if(lstat(pszName, &s) >= 0)
			{
				if(S_ISDIR(s.st_mode))
					return GAIA::True;
				return GAIA::False;
			}
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::RemoveFile(const GAIA::TCH* pszName)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				if(::DeleteFileA(pszName))
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				if(::DeleteFileW(pszName))
		#	endif
				return GAIA::True;
			return GAIA::False;
		#else
			if(unlink(pszName) == 0)
				return GAIA::True;
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::CopyFile(const GAIA::TCH* pszSrc, const GAIA::TCH* pszDst)
		{
			if(GAIA::ALGORITHM::stremp(pszSrc))
				return GAIA::False;
			if(GAIA::ALGORITHM::stremp(pszDst))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				if(::CopyFileA(pszSrc, pszDst, GAIA::False))
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				if(::CopyFileW(pszSrc, pszDst, GAIA::False))
		#	endif
				return GAIA::True;
			return GAIA::False;
		#else
			if(link(pszSrc, pszDst) == 0)
				return GAIA::True;
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::MoveFile(const GAIA::TCH* pszSrc, const GAIA::TCH* pszDst)
		{
			if(GAIA::ALGORITHM::stremp(pszSrc))
				return GAIA::False;
			if(GAIA::ALGORITHM::stremp(pszDst))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				if(::MoveFileA(pszSrc, pszDst))
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				if(::MoveFileW(pszSrc, pszDst))
		#	endif
				return GAIA::True;
			return GAIA::False;
		#else
			if(rename(pszSrc, pszDst) == 0)
				return GAIA::True;
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::CollectFile(const GAIA::TCH* pszName, const GAIA::TCH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszName));
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			/* Generate szFind for recursive file collection. */
			GAIA::TCH szFind[MAXPL];
			GAIA::ALGORITHM::strcpy(szFind, pszName);
			GAIA::TCH* p = GAIA::ALGORITHM::strend(szFind);
			--p;
			if(*p != '\\' && *p != '/')
				GAIA::ALGORITHM::strcat(p, _T("/"));
			/* Generate szTarget for FindFirstFile. */
			GAIA::TCH szTarget[MAXPL];
			GAIA::ALGORITHM::strcpy(szTarget, szFind);
			GAIA::ALGORITHM::strcat(szTarget + (p - szFind), _T("*.*"));
			/* Find. */
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				WIN32_FIND_DATAA fdata;
				HANDLE hFF = ::FindFirstFileA(szTarget, &fdata);
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				WIN32_FIND_DATAW fdata;
				HANDLE hFF = ::FindFirstFileW(szTarget, &fdata);
		#	endif
			if(hFF == (HANDLE)GINVALID)
				return GAIA::False;
			GAIA::BL bFinded = GAIA::True;
			while(bFinded)
			{
				if(GAIA::ALGORITHM::strcmp(fdata.cFileName, _T(".")) == 0 ||
					GAIA::ALGORITHM::strcmp(fdata.cFileName, _T("..")) == 0){}
				else if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && bOverlapped)
				{
					GAIA::TCH sz[MAXPL];
					GAIA::ALGORITHM::strcpy(sz, szFind);
					GAIA::ALGORITHM::strcat(sz, fdata.cFileName);
					this->CollectFile(sz, pszFilter, bOverlapped, treeResult);
				}
				else
				{
					GAIA::BL bExtMatch = GAIA::False;
					if(GAIA::ALGORITHM::stremp(pszFilter))
						bExtMatch = GAIA::True;
					else
					{
						const GAIA::TCH* pExt = GAIA::ALGORITHM::strext(fdata.cFileName);
						if(pExt != GNULL && GAIA::ALGORITHM::striwrd(pszFilter, pExt) != GNULL)
							bExtMatch = GAIA::True;
					}
					if(bExtMatch)
					{
						GAIA::TCH szFinal[MAXPL];
						GAIA::ALGORITHM::strcpy(szFinal, szFind);
						GAIA::ALGORITHM::strcat(szFinal, fdata.cFileName);
						GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::TString, GAIA::N16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>> listResult;
						const GAIA::TCH* pFinal = szFinal;
						for(;;)
						{
							const GAIA::TCH* pNew = GAIA::ALGORITHM::strdrop(pFinal, _T("/\\\0"));
							if(pNew != pFinal)
							{
								if(pNew == GNULL || *pNew == 0)
								{
									GAIA::TCH szTemp[MAXPL];
									GAIA::ALGORITHM::strcpy(szTemp, pFinal);
									if(szTemp[0] != 0)
										listResult.push_back(szTemp);
									break;
								}
								else
								{
									GAIA::TCH szTemp[MAXPL];
									GAIA::ALGORITHM::xmemcpy(szTemp, pFinal, (pNew - pFinal) * sizeof(GAIA::TCH));
									szTemp[pNew - pFinal] = 0;
									if(szTemp[0] != 0)
										listResult.push_back(szTemp);
								}
							}
							pFinal = pNew + 1;
						}
						treeResult.insert(listResult.front_ptr(), listResult.size());
					}
				}
			#if GAIA_CHARSET == GAIA_CHARSET_ANSI
				bFinded = ::FindNextFileA(hFF, &fdata) != 0;
			#elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				bFinded = ::FindNextFileW(hFF, &fdata) != 0;
			#endif
			}
			::FindClose(hFF);
			return GAIA::True;
		#else
			/* Generate szFind for recursive file collection. */
			GAIA::TCH szFind[MAXPL];
			GAIA::ALGORITHM::strcpy(szFind, pszName);
			GAIA::TCH* p = GAIA::ALGORITHM::strend(szFind);
			--p;
			if(*p != '/')
				GAIA::ALGORITHM::strcat(p, _T("/"));
			/* find */
			DIR* pdir = opendir(pszName);
			if(pdir == GNULL)
				return GAIA::False;
			dirent* pdirent;
			while((pdirent = readdir(pdir)) != GNULL)
			{
				if(GAIA::ALGORITHM::strcmp(pdirent->d_name, _T(".")) == 0 ||
					GAIA::ALGORITHM::strcmp(pdirent->d_name, _T("..")) == 0){}
				else
				{
					struct stat s;
					GAIA::TCH sz[MAXPL];
					GAIA::ALGORITHM::strcpy(sz, szFind);
					GAIA::ALGORITHM::strcat(sz, pdirent->d_name);
					if(lstat(sz, &s) >= 0)
					{
						if(S_ISDIR(s.st_mode))
						{
							if(bOverlapped)
								this->CollectFile(sz, pszFilter, bOverlapped, treeResult);
						}
						else
						{
							GAIA::BL bExtMatch = GAIA::False;
							if(GAIA::ALGORITHM::stremp(pszFilter))
								bExtMatch = GAIA::True;
							else
							{
								const GAIA::TCH* pExt = GAIA::ALGORITHM::strext(pdirent->d_name);
								if(pExt != GNULL && GAIA::ALGORITHM::striwrd(pszFilter, pExt) != GNULL)
									bExtMatch = GAIA::True;
							}
							if(bExtMatch)
							{
								GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::TString, GAIA::N16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > listResult;
								const GAIA::TCH* pFinal = sz;
								for(;;)
								{
									const GAIA::TCH* pNew = GAIA::ALGORITHM::strdrop(pFinal, _T("/\\\0"));
									if(pNew != pFinal)
									{
										if(pNew == GNULL || *pNew == 0)
										{
											GAIA::TCH szTemp[MAXPL];
											GAIA::ALGORITHM::strcpy(szTemp, pFinal);
											if(szTemp[0] != 0)
												listResult.push_back(szTemp);
											break;
										}
										else
										{
											GAIA::TCH szTemp[MAXPL];
											GAIA::ALGORITHM::xmemcpy(szTemp, pFinal, (pNew - pFinal) * sizeof(GAIA::TCH));
											szTemp[pNew - pFinal] = 0;
											if(szTemp[0] != 0)
												listResult.push_back(szTemp);
										}
									}
									pFinal = pNew + 1;
								}
								treeResult.insert(listResult.front_ptr(), listResult.size());
							}
						}
					}
				}
			}
			closedir(pdir);
			return GAIA::True;
		#endif
		}
	};
};

#endif
