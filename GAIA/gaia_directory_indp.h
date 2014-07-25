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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::SetWorkingDirectory(const GAIA::CH* dir)
		{
			if(GAIA::ALGORITHM::stremp(dir))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::SetCurrentDirectoryA(dir))
		#else
			if(chdir(dir) == 0)
		#endif
				return GAIA::True;
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Directory::GetWorkingDirectory(GAIA::CONTAINER::AString& result) const
		{
			GAIA::CH szPath[MAXPL];
		#if GAIA_OS == GAIA_OS_WINDOWS
			::GetCurrentDirectoryA(MAXPL, szPath);
		#else
			::getcwd(szPath, MAXPL);
		#endif
			result = szPath;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Directory::GetBinaryDirectory(GAIA::CONTAINER::AString& result) const
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			GAIA::CH szPath[MAXPL];
			::GetModuleFileNameA(GNULL, szPath, MAXPL);
			GAIA::CH* p = GAIA::ALGORITHM::strdropr(szPath, "/\\");
			result = szPath;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Create(const GAIA::CH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
			if(this->Exist(pszName))
				return GAIA::False;
			/* Generate szFind for recursive file collection. */
			GAIA::CH szFind[MAXPL];
			GAIA::ALGORITHM::strcpy(szFind, pszName);
			GAIA::CH* p = GAIA::ALGORITHM::strend(szFind);
			--p;
			if(*p != '\\' && *p != '/')
				GAIA::ALGORITHM::strcat(p, "/");
			if(bOverlapped)
			{
				const GAIA::CH* pCursor = szFind;
			#if GAIA_OS == GAIA_OS_WINDOWS
				/* Jump after Windows-OS disk name. */
				if(GAIA::ALGORITHM::strch(szFind, ':') != GNULL)
				{
					pCursor = GAIA::ALGORITHM::strdrop(pCursor, "/\\");
					if(pCursor == GNULL)
						return GAIA::False;
					++pCursor;
				}
			#endif
				while((pCursor = GAIA::ALGORITHM::strdrop(pCursor, "/\\\0")) != GNULL)
				{
					GAIA::CH sz[MAXPL];
					GAIA::ALGORITHM::xmemcpy(sz, szFind, (pCursor - szFind + 1) * sizeof(GAIA::CH));
					sz[pCursor - szFind + 1] = 0;
					if(!this->Exist(sz))
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
						if(!::CreateDirectoryA(sz, GNULL))
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
				if(::CreateDirectoryA(pszName, GNULL))
			#else
				if(mkdir(pszName, S_IRWXU | S_IRWXG | S_IRWXO) == 0)
			#endif
					return GAIA::True;
				return GAIA::False;
			}
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Remove(const GAIA::CH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(bOverlapped)
			{
				/* Generate szFind for recursive file collection. */
				GAIA::CH szFind[MAXPL];
				GAIA::ALGORITHM::strcpy(szFind, pszName);
				GAIA::CH* p = GAIA::ALGORITHM::strend(szFind);
				--p;
				if(*p != '\\' && *p != '/')
					GAIA::ALGORITHM::strcat(p, "/");
				/* Generate szTarget for FindFirstFile. */
				GAIA::CH szTarget[MAXPL];
				GAIA::ALGORITHM::strcpy(szTarget, szFind);
				GAIA::ALGORITHM::strcat(szTarget + (p - szFind), "*.*");
				WIN32_FIND_DATAA fdata;
				HANDLE hFF = ::FindFirstFileA(szTarget, &fdata);
				if(hFF == (HANDLE)GINVALID)
					return GAIA::False;
				GAIA::BL bFinded = GAIA::True;
				while(bFinded)
				{
					if(GAIA::ALGORITHM::strcmp(fdata.cFileName, ".") == 0 ||
						GAIA::ALGORITHM::strcmp(fdata.cFileName, "..") == 0){}
					else
					{
						GAIA::CH sz[MAXPL];
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
					bFinded = ::FindNextFileA(hFF, &fdata) != 0;
				}
				::FindClose(hFF);
				return this->Remove(pszName, GAIA::False);
			}
			else
			{
				if(::RemoveDirectoryA(pszName))
					return GAIA::True;
				return GAIA::False;
			}
		#else
			if(bOverlapped)
			{
				/* Generate szFind for recursive file collection. */
				GAIA::CH szFind[MAXPL];
				GAIA::ALGORITHM::strcpy(szFind, pszName);
				GAIA::CH* p = GAIA::ALGORITHM::strend(szFind);
				--p;
				if(*p != '/')
					GAIA::ALGORITHM::strcat(p, "/");
				/* find */
				DIR* pdir = opendir(pszName);
				if(pdir == GNULL)
					return GAIA::False;
				dirent* pdirent;
				while((pdirent = readdir(pdir)) != GNULL)
				{
					if(GAIA::ALGORITHM::strcmp(pdirent->d_name, ".") == 0 ||
						GAIA::ALGORITHM::strcmp(pdirent->d_name, "..") == 0){}
					else
					{
						struct stat s;
						GAIA::CH sz[MAXPL];
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Exist(const GAIA::CH* pszName) const
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			DWORD dwFileAttribute = ::GetFileAttributesA(pszName);
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::RemoveFile(const GAIA::CH* pszName)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::DeleteFileA(pszName))
				return GAIA::True;
			return GAIA::False;
		#else
			if(unlink(pszName) == 0)
				return GAIA::True;
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::CopyFile(const GAIA::CH* pszSrc, const GAIA::CH* pszDst)
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
			if(link(pszSrc, pszDst) == 0)
				return GAIA::True;
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::MoveFile(const GAIA::CH* pszSrc, const GAIA::CH* pszDst)
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
			if(rename(pszSrc, pszDst) == 0)
				return GAIA::True;
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::CollectFile(const GAIA::CH* pszName, const GAIA::CH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszName));
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			/* Generate szFind for recursive file collection. */
			GAIA::CH szFind[MAXPL];
			GAIA::ALGORITHM::strcpy(szFind, pszName);
			GAIA::CH* p = GAIA::ALGORITHM::strend(szFind);
			--p;
			if(*p != '\\' && *p != '/')
				GAIA::ALGORITHM::strcat(p, "/");
			/* Generate szTarget for FindFirstFile. */
			GAIA::CH szTarget[MAXPL];
			GAIA::ALGORITHM::strcpy(szTarget, szFind);
			GAIA::ALGORITHM::strcat(szTarget + (p - szFind), "*.*");
			WIN32_FIND_DATAA fdata;
			/* Find. */
			HANDLE hFF = ::FindFirstFileA(szTarget, &fdata);
			if(hFF == (HANDLE)GINVALID)
				return GAIA::False;
			GAIA::BL bFinded = GAIA::True;
			while(bFinded)
			{
				if(GAIA::ALGORITHM::strcmp(fdata.cFileName, ".") == 0 ||
					GAIA::ALGORITHM::strcmp(fdata.cFileName, "..") == 0){}
				else if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && bOverlapped)
				{
					GAIA::CH sz[MAXPL];
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
						const GAIA::CH* pExt = GAIA::ALGORITHM::strext(fdata.cFileName);
						if(pExt != GNULL && GAIA::ALGORITHM::striwrd(pszFilter, pExt) != GNULL)
							bExtMatch = GAIA::True;
					}
					if(bExtMatch)
					{
						GAIA::CH szFinal[MAXPL];
						GAIA::ALGORITHM::strcpy(szFinal, szFind);
						GAIA::ALGORITHM::strcat(szFinal, fdata.cFileName);
						GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::AString, GAIA::N16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>> listResult;
						const GAIA::CH* pFinal = szFinal;
						for(;;)
						{
							const GAIA::CH* pNew = GAIA::ALGORITHM::strdrop(pFinal, "/\\\0");
							if(pNew != pFinal)
							{
								if(pNew == GNULL || *pNew == 0)
								{
									GAIA::CH szTemp[MAXPL];
									GAIA::ALGORITHM::strcpy(szTemp, pFinal);
									if(szTemp[0] != 0)
										listResult.push_back(szTemp);
									break;
								}
								else
								{
									GAIA::CH szTemp[MAXPL];
									GAIA::ALGORITHM::xmemcpy(szTemp, pFinal, (pNew - pFinal) * sizeof(GAIA::CH));
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
				bFinded = ::FindNextFileA(hFF, &fdata) != 0;
			}
			::FindClose(hFF);
			return GAIA::True;
		#else
			/* Generate szFind for recursive file collection. */
			GAIA::CH szFind[MAXPL];
			GAIA::ALGORITHM::strcpy(szFind, pszName);
			GAIA::CH* p = GAIA::ALGORITHM::strend(szFind);
			--p;
			if(*p != '/')
				GAIA::ALGORITHM::strcat(p, "/");
			/* find */
			DIR* pdir = opendir(pszName);
			if(pdir == GNULL)
				return GAIA::False;
			dirent* pdirent;
			while((pdirent = readdir(pdir)) != GNULL)
			{
				if(GAIA::ALGORITHM::strcmp(pdirent->d_name, ".") == 0 ||
					GAIA::ALGORITHM::strcmp(pdirent->d_name, "..") == 0){}
				else
				{
					struct stat s;
					GAIA::CH sz[MAXPL];
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
								const GAIA::CH* pExt = GAIA::ALGORITHM::strext(pdirent->d_name);
								if(pExt != GNULL && GAIA::ALGORITHM::striwrd(pszFilter, pExt) != GNULL)
									bExtMatch = GAIA::True;
							}
							if(bExtMatch)
							{
								GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::AString, GAIA::N16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > listResult;
								const GAIA::CH* pFinal = sz;
								for(;;)
								{
									const GAIA::CH* pNew = GAIA::ALGORITHM::strdrop(pFinal, "/\\\0");
									if(pNew != pFinal)
									{
										if(pNew == GNULL || *pNew == 0)
										{
											GAIA::CH szTemp[MAXPL];
											GAIA::ALGORITHM::strcpy(szTemp, pFinal);
											if(szTemp[0] != 0)
												listResult.push_back(szTemp);
											break;
										}
										else
										{
											GAIA::CH szTemp[MAXPL];
											GAIA::ALGORITHM::xmemcpy(szTemp, pFinal, (pNew - pFinal) * sizeof(GAIA::CH));
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
