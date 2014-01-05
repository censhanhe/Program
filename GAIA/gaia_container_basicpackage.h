#ifndef		__GAIA_CONTAINER_PACKAGE_H__
#define		__GAIA_CONTAINER_PACKAGE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeType> BasicPackage
		{
			typedef _SizeType _sizetype;
		public:
			GINL Package();
			GINL ~Package();

		};
	};
};

#endif
