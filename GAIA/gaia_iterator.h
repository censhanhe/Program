#ifndef		__GAIA_ITERATOR_H__
#define		__GAIA_ITERATOR_H__

namespace GAIA
{
	namespace ITERATOR
	{
		template<typename _DataType> class Iterator : public GAIA::Base
		{
		public:
			GINL virtual ~Iterator(){}
			GINL virtual GAIA::BL empty() const = 0;
			GINL virtual _DataType& operator * () = 0;
			GINL virtual const _DataType& operator * () const = 0;
			GINL virtual Iterator<_DataType>& operator ++ () = 0;
			GINL virtual Iterator<_DataType>& operator -- () = 0;
			GINL virtual Iterator<_DataType>& operator = (const Iterator<_DataType>& src) = 0;
			GINL virtual GAIA::BL operator == (const Iterator<_DataType>& src) const = 0;
			GINL virtual GAIA::BL operator != (const Iterator<_DataType>& src) const = 0;
		private:
			GINL virtual Iterator<_DataType>& operator ++ (GAIA::N32) = 0;
			GINL virtual Iterator<_DataType>& operator -- (GAIA::N32) = 0;
		};

		template<typename _DataType> class ConstIterator : public GAIA::Base
		{
		public:
			GINL virtual ~ConstIterator(){}
			GINL virtual GAIA::BL empty() const = 0;
			GINL virtual const _DataType& operator * () const = 0;
			GINL virtual ConstIterator<_DataType>& operator ++ () = 0;
			GINL virtual ConstIterator<_DataType>& operator -- () = 0;
			GINL virtual ConstIterator<_DataType>& operator = (const ConstIterator<_DataType>& src) = 0;
			GINL virtual GAIA::BL operator == (const ConstIterator<_DataType>& src) const = 0;
			GINL virtual GAIA::BL operator != (const ConstIterator<_DataType>& src) const = 0;
		private:
			GINL virtual ConstIterator<_DataType>& operator ++ (GAIA::N32) = 0;
			GINL virtual ConstIterator<_DataType>& operator -- (GAIA::N32) = 0;
		};
	};
};

#endif
