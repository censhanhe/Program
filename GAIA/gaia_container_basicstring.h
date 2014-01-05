#ifndef		__GAIA_CONTAINER_BASICSTRING_H__
#define		__GAIA_CONTAINER_BASICSTRING_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType> class BasicString
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;

		public:
			BasicString(){}
			~BasicString(){}

			GINL GAIA::GVOID clear();
			GINL GAIA::GVOID destory();

		private:
		};
	};
};

#endif
