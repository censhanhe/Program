#ifndef 	__GAIA_CONTAINER_ACCESSER_H__
#define 	__GAIA_CONTAINER_ACCESSER_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template<typename _DataType, typename _SizeType> class Accesser : public GAIA::Base
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			typedef Accesser<_DataType, _SizeType> __MyType;
		public:
			GINL Accesser();
			GINL Accesser(const __MyType& src);
			GINL ~Accesser();
			GINL GAIA::BL empty() const;
			GINL GAIA::BL open(const GAIA::GCH* psz, const _SizeType& size);
			GINL GAIA::BL close();
			GINL GAIA::BL isopenned() const;
			GINL __MyType& operator = (const __MyType& src){return *this;}
		private:
		};
	};
};

#endif