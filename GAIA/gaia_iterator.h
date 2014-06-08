#ifndef		__GAIA_ITERATOR_H__
#define		__GAIA_ITERATOR_H__

namespace GAIA
{
	namespace ITERATOR
	{
		template<typename _DataType> class Iterator : public GAIA::Base
		{
		public:
			virtual ~Iterator(){}
			virtual GAIA::BL empty() const = 0;
			virtual _DataType& operator * () = 0;
			virtual const _DataType& operator * () const = 0;
			virtual Iterator<_DataType>& operator ++ () = 0;
			virtual Iterator<_DataType>& operator -- () = 0;
			virtual Iterator<_DataType>& operator = (const Iterator<_DataType>& src) = 0;
			virtual GAIA::BL operator == (const Iterator<_DataType>& src) const = 0;
			virtual GAIA::BL operator != (const Iterator<_DataType>& src) const = 0;
			virtual GAIA::BL operator ! (){return this->empty();}
		private:
			virtual Iterator<_DataType>& operator ++ (GAIA::N32) = 0;
			virtual Iterator<_DataType>& operator -- (GAIA::N32) = 0;
		};

		template<typename _DataType> class ConstIterator : public GAIA::Base
		{
		public:
			virtual ~ConstIterator(){}
			virtual GAIA::BL empty() const = 0;
			virtual const _DataType& operator * () const = 0;
			virtual ConstIterator<_DataType>& operator ++ () = 0;
			virtual ConstIterator<_DataType>& operator -- () = 0;
			virtual ConstIterator<_DataType>& operator = (const ConstIterator<_DataType>& src) = 0;
			virtual GAIA::BL operator == (const ConstIterator<_DataType>& src) const = 0;
			virtual GAIA::BL operator != (const ConstIterator<_DataType>& src) const = 0;
			virtual GAIA::BL operator ! (){return this->empty();}
		private:
			virtual ConstIterator<_DataType>& operator ++ (GAIA::N32) = 0;
			virtual ConstIterator<_DataType>& operator -- (GAIA::N32) = 0;
		};
	};
};

#endif
