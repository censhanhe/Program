#ifndef		__GAIA_RESOURCE_RESOURCEDRIVER_H__
#define		__GAIA_RESOURCE_RESOURCEDRIVER_H__

namespace GAIA
{
	namespace RESOURCE
	{
		ENUM_BEGIN(RESOURCE_TYPE)
			RESOURCE_TYPE_STRING,
			RESOURCE_TYPE_HEIGHTFIELD,
			RESOURCE_TYPE_STATICMESH,
			RESOURCE_TYPE_PARTICLE,
		ENUM_END

		class ResourceDriver
		{
		public:
			GINL ResourceDriver();
			GINL ~ResourceDriver();
			GINL Resource* RequestResource();
		};
	};
};

#endif