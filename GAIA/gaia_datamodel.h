#ifndef		__GAIA_DATAMODEL_H__
#define		__GAIA_DATAMODEL_H__

namespace GAIA
{
	namespace MODEL
	{
		template <typename _SizeType, typename _KeyType> class DataModel // SP means seperate piece.
		{
		public:
			GINL virtual GAIA::BL insert(const _KeyType& keytype, const GAIA::VOID* pBuffer, const _SizeType& size) = 0;
			GINL virtual GAIA::BL erase(const _KeyType& keytype) = 0;
			GINL virtual GAIA::VOID clear() = 0;
		};
	};
};

#endif