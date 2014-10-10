#ifndef		__GAIA_FILESYSTEM_DIRECTORY_H__
#define		__GAIA_FILESYSTEM_DIRECTORY_H__

namespace GAIA
{
	namespace FSYS
	{
		class Directory : public GAIA::Entity
		{
		public:
			typedef GAIA::CTN::BasicTrieTree<GAIA::CTN::TString, GAIA::NM, GAIA::ALGO::TwiceSizeIncreaser<GAIA::NM> > __ResultTree;
		public:
			Directory(){}
			~Directory(){}
			GINL GAIA::BL SetWorkingDirectory(const GAIA::TCH* dir);
			GINL GAIA::GVOID GetWorkingDirectory(GAIA::CTN::TString& result) const;
			GINL GAIA::GVOID GetBinaryDirectory(GAIA::CTN::TString& result) const;
			GINL GAIA::BL Create(const GAIA::TCH* pszName, GAIA::BL bOverlapped);
			GINL GAIA::BL Remove(const GAIA::TCH* pszName, GAIA::BL bOverlapped);
			GINL GAIA::BL Exist(const GAIA::TCH* pszName) const;
			GINL GAIA::BL RemoveFile(const GAIA::TCH* pszName);
			GINL GAIA::BL CopyFile(const GAIA::TCH* pszSrc, const GAIA::TCH* pszDst);
			GINL GAIA::BL MoveFile(const GAIA::TCH* pszSrc, const GAIA::TCH* pszDst);
			GINL GAIA::BL ExistFile(const GAIA::TCH* pszName);
			GINL GAIA::BL CollectFile(const GAIA::TCH* pszName, const GAIA::TCH* pszFilter, GAIA::BL bOverlapped, __ResultTree& treeResult);
		private:
			GINL Directory& operator = (const Directory& src){GAIA_AST(&src != this); return *this;}
		};
	};
};

#include "gaia_filesystem_directory_indp.h"

#endif
