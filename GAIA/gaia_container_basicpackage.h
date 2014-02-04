#ifndef		__GAIA_CONTAINER_PACKAGE_H__
#define		__GAIA_CONTAINER_PACKAGE_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _SizeType> BasicPackage
		{
		public:
			typedef _SizeType _sizetype;
		public:
			typedef BasicPackage<_SizeType> __MyType;
		public:
			GINL Package();
			GINL ~Package();
		private:
		};
	};
};

#endif
