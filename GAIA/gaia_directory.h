#ifndef		__GAIA_FILESYSTEM_DIRECTORY_H__
#define		__GAIA_FILESYSTEM_DIRECTORY_H__

namespace GAIA
{
	namespace FILESYSTEM
	{
		class Directory
		{
		public:
			typedef GAIA::CONTAINER::BasicTrieTree<GAIA::CONTAINER::AString, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM> > __ResultTree;
		public:
			Directory(){}
			~Directory(){}
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID GetWorkingDirectory(GAIA::CONTAINER::AString& result) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::GVOID GetBinaryDirectory(GAIA::CONTAINER::AString& result) const;
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Create(const GAIA::GCH* pszName, GAIA::BL bOverlapped);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Remove(const GAIA::GCH* pszName, GAIA::BL bOverlapped);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL RemoveFile(const GAIA::GCH* pszName);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Copy(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Move(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst);
			GAIA_DEBUG_CODEPURE_MEMFUNC GAIA::BL Collect(const GAIA::GCH* pszName, const GAIA::GCH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult);
		private:
			GINL Directory& operator = (const Directory& src){return *this;}
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_directory_indp.h"
#endif

#endif