#ifndef		__GAIA_DIRECTORY_INDP_H__
#define		__GAIA_DIRECTORY_INDP_H__

#if GAIA_OS == GAIA_OS_WINDOWS
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
	namespace FSYS
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		static const GAIA::U32 MAXPL = MAX_PATH;
	#else
		static const GAIA::U32 MAXPL = 260;
	#endif
		GINL GAIA::BL Directory::SetWorkingDirectory(const GAIA::TCH* dir)
		{
			if(GAIA::ALGO::stremp(dir))
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
		GINL GAIA::GVOID Directory::GetWorkingDirectory(GAIA::CTN::TString& result) const
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
		GINL GAIA::GVOID Directory::GetBinaryDirectory(GAIA::CTN::TString& result) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::TCH szPath[MAXPL];
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				::GetModuleFileNameA(GNIL, szPath, MAXPL);
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				::GetModuleFileNameW(GNIL, szPath, MAXPL);
		#	endif
			GAIA::TCH* p = GAIA::ALGO::strdropr(szPath, _T("/\\"));
			result = szPath;
		#else
		#endif
		}
		GINL GAIA::BL Directory::Create(const GAIA::TCH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGO::stremp(pszName))
				return GAIA::False;
			if(this->Exist(pszName))
				return GAIA::False;
			/* Generate szFind for recursive file collection. */
			GAIA::TCH szFind[MAXPL];
			GAIA::ALGO::strcpy(szFind, pszName);
			GAIA::TCH* p = GAIA::ALGO::strend(szFind);
			--p;
			if(*p != '\\' && *p != '/')
				GAIA::ALGO::strcat(p, _T("/"));
			if(bOverlapped)
			{
				const GAIA::TCH* pCursor = szFind;
			#if GAIA_OS == GAIA_OS_WINDOWS
				/* Jump after Windows-OS disk name. */
				if(GAIA::ALGO::strch(szFind, ':') != GNIL)
				{
					pCursor = GAIA::ALGO::strdrop(pCursor, _T("/\\"));
					if(pCursor == GNIL)
						return GAIA::False;
					++pCursor;
				}
			#endif
				while((pCursor = GAIA::ALGO::strdrop(pCursor, _T("/\\\0"))) != GNIL)
				{
					GAIA::TCH sz[MAXPL];
					GAIA::ALGO::xmemcpy(sz, szFind, (pCursor - szFind + 1) * sizeof(GAIA::TCH));
					sz[pCursor - szFind + 1] = 0;
					if(!this->Exist(sz))
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
					#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
							if(!::CreateDirectoryA(sz, GNIL))
					#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
							if(!::CreateDirectoryW(sz, GNIL))
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
					if(::CreateDirectoryA(pszName, GNIL))
			#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
					if(::CreateDirectoryW(pszName, GNIL))
			#	endif
			#else
				if(mkdir(pszName, S_IRWXU | S_IRWXG | S_IRWXO) == 0)
			#endif
					return GAIA::True;
				return GAIA::False;
			}
		}
		GINL GAIA::BL Directory::Remove(const GAIA::TCH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGO::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(bOverlapped)
			{
				/* Generate szFind for recursive file collection. */
				GAIA::TCH szFind[MAXPL];
				GAIA::ALGO::strcpy(szFind, pszName);
				GAIA::TCH* p = GAIA::ALGO::strend(szFind);
				--p;
				if(*p != '\\' && *p != '/')
					GAIA::ALGO::strcat(p, _T("/"));
				/* Generate szTarget for FindFirstFile. */
				GAIA::TCH szTarget[MAXPL];
				GAIA::ALGO::strcpy(szTarget, szFind);
				GAIA::ALGO::strcat(szTarget + (p - szFind), _T("*.*"));
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
					if(GAIA::ALGO::strcmp(fdata.cFileName, _T(".")) == 0 ||
						GAIA::ALGO::strcmp(fdata.cFileName, _T("..")) == 0){}
					else
					{
						GAIA::TCH sz[MAXPL];
						GAIA::ALGO::strcpy(sz, szFind);
						GAIA::ALGO::strcat(sz, fdata.cFileName);
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
				GAIA::ALGO::strcpy(szFind, pszName);
				GAIA::TCH* p = GAIA::ALGO::strend(szFind);
				--p;
				if(*p != '/')
					GAIA::ALGO::strcat(p, _T("/"));
				/* find */
				DIR* pdir = opendir(pszName);
				if(pdir == GNIL)
					return GAIA::False;
				dirent* pdirent;
				while((pdirent = readdir(pdir)) != GNIL)
				{
					if(GAIA::ALGO::strcmp(pdirent->d_name, _T(".")) == 0 ||
						GAIA::ALGO::strcmp(pdirent->d_name, _T("..")) == 0){}
					else
					{
						struct stat s;
						GAIA::TCH sz[MAXPL];
						GAIA::ALGO::strcpy(sz, szFind);
						GAIA::ALGO::strcat(sz, pdirent->d_name);
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
		GINL GAIA::BL Directory::Exist(const GAIA::TCH* pszName) const
		{
			if(GAIA::ALGO::stremp(pszName))
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
		GINL GAIA::BL Directory::RemoveFile(const GAIA::TCH* pszName)
		{
			if(GAIA::ALGO::stremp(pszName))
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
		GINL GAIA::BL Directory::CopyFile(const GAIA::TCH* pszSrc, const GAIA::TCH* pszDst)
		{
			if(GAIA::ALGO::stremp(pszSrc))
				return GAIA::False;
			if(GAIA::ALGO::stremp(pszDst))
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
		GINL GAIA::BL Directory::MoveFile(const GAIA::TCH* pszSrc, const GAIA::TCH* pszDst)
		{
			if(GAIA::ALGO::stremp(pszSrc))
				return GAIA::False;
			if(GAIA::ALGO::stremp(pszDst))
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
		GINL GAIA::BL Directory::ExistFile(const GAIA::TCH* pszName)
		{
			if(GAIA::ALGO::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
		#	if GAIA_CHARSET == GAIA_CHARSET_ANSI
				GAIA::UM uFlag = ::GetFileAttributesA(pszName);
		#	elif GAIA_CHARSET == GAIA_CHARSET_UNICODE
				GAIA::UM uFlag = ::GetFileAttributesW(pszName);
		#	endif
			if(uFlag == GINVALID)
				return GAIA::False;
			else if(uFlag & FILE_ATTRIBUTE_DIRECTORY)
				return GAIA::False;
			return GAIA::True;
		#else
			struct stat s;
			if(lstat(pszName, &s) >= 0)
			{
				if(S_ISDIR(s.st_mode))
					return GAIA::False;
				return GAIA::True;
			}
			return GAIA::False;
		#endif
		}
		GINL GAIA::BL Directory::CollectFile(const GAIA::TCH* pszName, const GAIA::TCH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult)
		{
			GAIA_AST(!GAIA::ALGO::stremp(pszName));
			if(GAIA::ALGO::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			/* Generate szFind for recursive file collection. */
			GAIA::TCH szFind[MAXPL];
			GAIA::ALGO::strcpy(szFind, pszName);
			GAIA::TCH* p = GAIA::ALGO::strend(szFind);
			--p;
			if(*p != '\\' && *p != '/')
				GAIA::ALGO::strcat(p, _T("/"));
			/* Generate szTarget for FindFirstFile. */
			GAIA::TCH szTarget[MAXPL];
			GAIA::ALGO::strcpy(szTarget, szFind);
			GAIA::ALGO::strcat(szTarget + (p - szFind), _T("*.*"));
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
				if(GAIA::ALGO::strcmp(fdata.cFileName, _T(".")) == 0 ||
					GAIA::ALGO::strcmp(fdata.cFileName, _T("..")) == 0){}
				else if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && bOverlapped)
				{
					GAIA::TCH sz[MAXPL];
					GAIA::ALGO::strcpy(sz, szFind);
					GAIA::ALGO::strcat(sz, fdata.cFileName);
					this->CollectFile(sz, pszFilter, bOverlapped, treeResult);
				}
				else
				{
					GAIA::BL bExtMatch = GAIA::False;
					if(GAIA::ALGO::stremp(pszFilter))
						bExtMatch = GAIA::True;
					else
					{
						const GAIA::TCH* pExt = GAIA::ALGO::strext(fdata.cFileName);
						if(pExt != GNIL && GAIA::ALGO::striwrd(pszFilter, pExt) != GNIL)
							bExtMatch = GAIA::True;
					}
					if(bExtMatch)
					{
						GAIA::TCH szFinal[MAXPL];
						GAIA::ALGO::strcpy(szFinal, szFind);
						GAIA::ALGO::strcat(szFinal, fdata.cFileName);
						GAIA::CTN::BasicVector<GAIA::CTN::TString, GAIA::N16, GAIA::ALGO::TwiceSizeIncreaser<GAIA::N32>> listResult;
						const GAIA::TCH* pFinal = szFinal;
						for(;;)
						{
							const GAIA::TCH* pNew = GAIA::ALGO::strdrop(pFinal, _T("/\\\0"));
							if(pNew != pFinal)
							{
								if(pNew == GNIL || *pNew == 0)
								{
									GAIA::TCH szTemp[MAXPL];
									GAIA::ALGO::strcpy(szTemp, pFinal);
									if(szTemp[0] != 0)
										listResult.push_back(szTemp);
									break;
								}
								else
								{
									GAIA::TCH szTemp[MAXPL];
									GAIA::ALGO::xmemcpy(szTemp, pFinal, (pNew - pFinal) * sizeof(GAIA::TCH));
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
			GAIA::ALGO::strcpy(szFind, pszName);
			GAIA::TCH* p = GAIA::ALGO::strend(szFind);
			--p;
			if(*p != '/')
				GAIA::ALGO::strcat(p, _T("/"));
			/* find */
			DIR* pdir = opendir(pszName);
			if(pdir == GNIL)
				return GAIA::False;
			dirent* pdirent;
			while((pdirent = readdir(pdir)) != GNIL)
			{
				if(GAIA::ALGO::strcmp(pdirent->d_name, _T(".")) == 0 ||
					GAIA::ALGO::strcmp(pdirent->d_name, _T("..")) == 0){}
				else
				{
					struct stat s;
					GAIA::TCH sz[MAXPL];
					GAIA::ALGO::strcpy(sz, szFind);
					GAIA::ALGO::strcat(sz, pdirent->d_name);
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
							if(GAIA::ALGO::stremp(pszFilter))
								bExtMatch = GAIA::True;
							else
							{
								const GAIA::TCH* pExt = GAIA::ALGO::strext(pdirent->d_name);
								if(pExt != GNIL && GAIA::ALGO::striwrd(pszFilter, pExt) != GNIL)
									bExtMatch = GAIA::True;
							}
							if(bExtMatch)
							{
								GAIA::CTN::BasicVector<GAIA::CTN::TString, GAIA::N16, GAIA::ALGO::TwiceSizeIncreaser<GAIA::N32> > listResult;
								const GAIA::TCH* pFinal = sz;
								for(;;)
								{
									const GAIA::TCH* pNew = GAIA::ALGO::strdrop(pFinal, _T("/\\\0"));
									if(pNew != pFinal)
									{
										if(pNew == GNIL || *pNew == 0)
										{
											GAIA::TCH szTemp[MAXPL];
											GAIA::ALGO::strcpy(szTemp, pFinal);
											if(szTemp[0] != 0)
												listResult.push_back(szTemp);
											break;
										}
										else
										{
											GAIA::TCH szTemp[MAXPL];
											GAIA::ALGO::xmemcpy(szTemp, pFinal, (pNew - pFinal) * sizeof(GAIA::TCH));
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
