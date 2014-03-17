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
#	include <sys/dirent.h>
#	include <unistd.h>
#endif

namespace GAIA
{
	namespace FILESYSTEM
	{
	#if GAIA_OS == GAIA_OS_WINDOWS
		static GAIA::UM MAXPL = MAX_PATH;
	#else
		static GAIA::UM MAXPL = 260;
	#endif
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::SetWorkingDirectory(const GAIA::GCH* dir)
		{
			if(GAIA::ALGORITHM::stremp(dir))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::SetCurrentDirectory(dir))
		#else
			if(chdir(dir) == 0)
		#endif
				return GAIA::True;
			return GAIA::False;
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID Directory::GetWorkingDirectory(GAIA::CONTAINER::AString& result) const
		{
			GAIA::GCH szPath[MAXPL];
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
			GAIA::GCH szPath[MAXPL];
			::GetModuleFileNameA(GNULL, szPath, MAXPL);
			GAIA::GCH* p = GAIA::ALGORITHM::strdropr(szPath, "/\\");
			result = szPath;
		#else
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Create(const GAIA::GCH* pszName, GAIA::BL bOverlapped)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
			if(this->Exist(pszName))
				return GAIA::False;
			if(bOverlapped)
			{
				const GAIA::GCH* p = pszName;
			#if GAIA_OS == GAIA_OS_WINDOWS
				/* Jump after Windows-OS disk name. */
				p = GAIA::ALGORITHM::strdrop(p, "/\\");
				if(p == GNULL)
					return GAIA::False;
				++p;
			#endif
				while((p = GAIA::ALGORITHM::strdrop(p, "/\\\0")) != GNULL)
				{
					GAIA::GCH sz[MAXPL];
					GAIA::ALGORITHM::memcpy(sz, pszName, (p - pszName + 1) * sizeof(GAIA::GCH));
					sz[p - pszName + 1] = 0;
					if(!this->Exist(sz))
					{
					#if GAIA_OS == GAIA_OS_WINDOWS
						if(!::CreateDirectoryA(sz, GNULL))
					#else
						if(mkdir(sz, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
					#endif
							return GAIA::False;
					}
					if(*p == 0)
						break;
					else
						++p;
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
					GAIA::GCH sz[MAXPL];
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
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::Exist(const GAIA::GCH* pszName) const
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::RemoveFile(const GAIA::GCH* pszName)
		{
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			if(::DeleteFileA(pszName))
				return GAIA::True;
			return GAIA::False;
		#else
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::CopyFile(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst)
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
			return GAIA::False;
		#endif
		}
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::MoveFile(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst)
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
		GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Directory::CollectFile(const GAIA::GCH* pszName, const GAIA::GCH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult)
		{
			GAIA_AST(!GAIA::ALGORITHM::stremp(pszName));
			if(GAIA::ALGORITHM::stremp(pszName))
				return GAIA::False;
		#if GAIA_OS == GAIA_OS_WINDOWS
			/* Generate szFind for recursive file collection. */
			GAIA::GCH szFind[MAXPL];
			GAIA::ALGORITHM::strcpy(szFind, pszName);
			GAIA::GCH* p = GAIA::ALGORITHM::strend(szFind);
			--p;
			if(*p != '\\' && *p != '/')
				GAIA::ALGORITHM::strcat(p, "/");
			/* Generate szTarget for FindFirstFile. */
			GAIA::GCH szTarget[MAXPL];
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
					GAIA::GCH szNext[MAXPL];
					GAIA::ALGORITHM::strcpy(szNext, szFind);
					GAIA::ALGORITHM::strcat(szNext, fdata.cFileName);
					this->CollectFile(szNext, pszFilter, bOverlapped, treeResult);
				}
				else
				{
					GAIA::BL bExtMatch = GAIA::False;
					if(GAIA::ALGORITHM::stremp(pszFilter))
						bExtMatch = GAIA::True;
					else
					{
						const GAIA::GCH* pExt = GAIA::ALGORITHM::strext(fdata.cFileName);
						if(pExt != GNULL && GAIA::ALGORITHM::striwrd(pszFilter, pExt) != GNULL)
							bExtMatch = GAIA::True;
					}
					if(bExtMatch)
					{
						GAIA::GCH szFinal[MAXPL];
						GAIA::ALGORITHM::strcpy(szFinal, szFind);
						GAIA::ALGORITHM::strcat(szFinal, fdata.cFileName);
						GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::AString, GAIA::N16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32>> listResult;
						const GAIA::GCH* pFinal = szFinal;
						for(;;)
						{
							const GAIA::GCH* pNew = GAIA::ALGORITHM::strdrop(pFinal, "/\\\0");
							if(pNew != pFinal)
							{
								if(pNew == GNULL || *pNew == 0)
								{
									GAIA::GCH szTemp[MAXPL];
									GAIA::ALGORITHM::strcpy(szTemp, pFinal);
									if(szTemp[0] != 0)
										listResult.push_back(szTemp);
									break;
								}
								else
								{
									GAIA::GCH szTemp[MAXPL];
									GAIA::ALGORITHM::memcpy(szTemp, pFinal, (pNew - pFinal) * sizeof(GAIA::GCH));
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
				bFinded = ::FindNextFileA(hFF, &fdata);
			}
			::FindClose(hFF);
			return GAIA::True;
		#else
			/* Generate szFind for recursive file collection. */
			GAIA::GCH szFind[MAXPL];
			GAIA::ALGORITHM::strcpy(szFind, pszName);
			GAIA::GCH* p = GAIA::ALGORITHM::strend(szFind);
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
					GAIA::GCH szNext[MAXPL];
					GAIA::ALGORITHM::strcpy(szNext, szFind);
					GAIA::ALGORITHM::strcat(szNext, pdirent->d_name);
					if(lstat(szNext, &s) >= 0)
					{
						if(S_ISDIR(s.st_mode))
						{
							if(bOverlapped)
								this->CollectFile(szNext, pszFilter, bOverlapped, treeResult);
						}
						else
						{
							GAIA::BL bExtMatch = GAIA::False;
							if(GAIA::ALGORITHM::stremp(pszFilter))
								bExtMatch = GAIA::True;
							else
							{
								const GAIA::GCH* pExt = GAIA::ALGORITHM::strext(pdirent->d_name);
								if(pExt != GNULL && GAIA::ALGORITHM::striwrd(pszFilter, pExt) != GNULL)
									bExtMatch = GAIA::True;
							}
							if(bExtMatch)
							{
								GAIA::CONTAINER::BasicVector<GAIA::CONTAINER::AString, GAIA::N16, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::N32> > listResult;
								const GAIA::GCH* pFinal = szNext;
								for(;;)
								{
									const GAIA::GCH* pNew = GAIA::ALGORITHM::strdrop(pFinal, "/\\\0");
									if(pNew != pFinal)
									{
										if(pNew == GNULL || *pNew == 0)
										{
											GAIA::GCH szTemp[MAXPL];
											GAIA::ALGORITHM::strcpy(szTemp, pFinal);
											if(szTemp[0] != 0)
												listResult.push_back(szTemp);
											break;
										}
										else
										{
											GAIA::GCH szTemp[MAXPL];
											GAIA::ALGORITHM::memcpy(szTemp, pFinal, (pNew - pFinal) * sizeof(GAIA::GCH));
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
