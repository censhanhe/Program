#ifndef		__GAIA_CONTAINER_ORDERLESS_H__
#define		__GAIA_CONTAINER_ORDERLESS_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, typename _SizeIncreaserType> class Orderless
		{
		public:
			GINL Orderless();
			GINL Orderless(const 
			GINL ~Orderless(const Orderless<_DataType, _SizeType, _SizeIncreaserType>& src);

			_SizeType push(

		private:
			BasicVector<_DataType, _SizeType, _SizeIncreaserType> m_use;
			BasicStack<_DataType, _SizeType, _SizeIncreaserType> m_free;
		};
	};
};

#endif