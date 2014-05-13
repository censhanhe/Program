#ifndef		__GAIA_FILESYSTEM_DIRECTORY_H__
#define		__GAIA_FILESYSTEM_DIRECTORY_H__

namespace GAIA
{
	namespace FILESYSTEM
	{
		class Directory : public GAIA::Base
		{
		public:
			typedef GAIA::CONTAINER::BasicTrieTree<GAIA::CONTAINER::AString, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM> > __ResultTree;
		public:
			Directory(){}
			~Directory(){}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL SetWorkingDirectory(const GAIA::GCH* dir);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID GetWorkingDirectory(GAIA::CONTAINER::AString& result) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID GetBinaryDirectory(GAIA::CONTAINER::AString& result) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Create(const GAIA::GCH* pszName, GAIA::BL bOverlapped);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Remove(const GAIA::GCH* pszName, GAIA::BL bOverlapped);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Exist(const GAIA::GCH* pszName) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL RemoveFile(const GAIA::GCH* pszName);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL CopyFile(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL MoveFile(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL CollectFile(const GAIA::GCH* pszName, const GAIA::GCH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult);
		private:
			GINL Directory& operator = (const Directory& src){GAIA_AST(&src != this); return *this;}
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_directory_indp.h"
#endif

#endif
