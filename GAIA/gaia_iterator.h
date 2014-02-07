#ifndef		__GAIA_ITERATOR_H__
#define		__GAIA_ITERATOR_H__

namespace GAIA
{
	namespace ITERATOR
	{
		template <typename _DataType> class Iterator
		{
		public:
			GINL virtual ~Iterator(){}
			GINL virtual GAIA::BL empty() const = 0;
			GINL virtual _DataType& operator * () = 0;
			GINL virtual const _DataType& operator * () const = 0;
			GINL virtual Iterator& operator ++ () = 0;
			GINL virtual Iterator& operator -- () = 0;
		private:
			GINL virtual Iterator& operator ++ (GAIA::N32) = 0;
			GINL virtual Iterator& operator -- (GAIA::N32) = 0;
		};

		template <typename _DataType> class ConstIterator
		{
		public:
			GINL virtual ~ConstIterator(){}
			GINL virtual GAIA::BL empty() const = 0;
			GINL virtual const _DataType& operator * () const = 0;
			GINL virtual ConstIterator& operator ++ () = 0;
			GINL virtual ConstIterator& operator -- () = 0;
		private:
			GINL virtual ConstIterator& operator ++ (GAIA::N32) = 0;
			GINL virtual ConstIterator& operator -- (GAIA::N32) = 0;
		};
	};
};

#endif
