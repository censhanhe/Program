#ifndef		__GAIA_FILESYSTEM_DIRECTORY_H__
#define		__GAIA_FILESYSTEM_DIRECTORY_H__

namespace GAIA
{
	namespace FILESYSTEM
	{
		class Directory : public GAIA::Entity
		{
		public:
			typedef GAIA::CONTAINER::BasicTrieTree<GAIA::CONTAINER::TString, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM> > __ResultTree;
		public:
			Directory(){}
			~Directory(){}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL SetWorkingDirectory(const GAIA::TCH* dir);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID GetWorkingDirectory(GAIA::CONTAINER::TString& result) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID GetBinaryDirectory(GAIA::CONTAINER::TString& result) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Create(const GAIA::TCH* pszName, GAIA::BL bOverlapped);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Remove(const GAIA::TCH* pszName, GAIA::BL bOverlapped);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Exist(const GAIA::TCH* pszName) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL RemoveFile(const GAIA::TCH* pszName);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL CopyFile(const GAIA::TCH* pszSrc, const GAIA::TCH* pszDst);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL MoveFile(const GAIA::TCH* pszSrc, const GAIA::TCH* pszDst);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL CollectFile(const GAIA::TCH* pszName, const GAIA::TCH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult);
		private:
			GINL Directory& operator = (const Directory& src){GAIA_AST(&src != this); return *this;}
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_directory_indp.h"
#endif

#endif
