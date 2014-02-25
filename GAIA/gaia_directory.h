#ifndef		__GAIA_FILESYSTEM_DIRECTORY_H__
#define		__GAIA_FILESYSTEM_DIRECTORY_H__

namespace GAIA
{
	namespace FILESYSTEM
	{
		class Directory
		{
		public:
			typedef GAIA::CONTAINER::BasicTrieTree<GAIA::CONTAINER::AString, GAIA::NM, GAIA::ALGORITHM::TwiceSizeIncreaser<GAIA::NM>, GAIA_DEFAULT_GROUPELEMENTSIZE> __ResultTree;
		public:
			Directory();
			~Directory();
			GAIA::GVOID Set(const GAIA::GCH* pszName);
			const GAIA::GCH* Get() const;
			GAIA::BL Create(const GAIA::GCH* pszName);
			GAIA::BL Remove(const GAIA::GCH* pszName);
			GAIA::BL RemoveFile(const GAIA::GCH* pszName);
			GAIA::BL Copy(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst);
			GAIA::BL Move(const GAIA::GCH* pszSrc, const GAIA::GCH* pszDst);
			GAIA::BL Collect(const GAIA::GCH* pszFilter, GAIA::BL bEnterChild, __ResultTree& listResult);
		private:
			GINL Directory& operator = (const Directory& src){return *this;}
		};
	};
};

#endif