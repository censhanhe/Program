#ifndef		__GAIA_CONTAINER_BASICARRAY_H__
#define		__GAIA_CONTAINER_BASICARRAY_H__

namespace GAIA
{
	namespace CONTAINER
	{
		template <typename _DataType, typename _SizeType, _SizeType _Size> class BasicArray
		{
		public:
			typedef _DataType _datatype;
			typedef _SizeType _sizetype;
		public:
			GINL BasicArray(){this->init();}
			GINL BasicArray(const BasicArray<_DataType, _sizetype, _Size>& src){this->init(); this->operator = (src);}
			GINL GAIA::BL empty(){if(this->size() == 0) return GAIA::True; return GAIA::False;}
			GINL _SizeType size(){return m_size;}
			GINL _SizeType capacity(){return _Size;}
			GINL GAIA::GVOID clear(){m_size = 0;}
			GINL GAIA::BL push_back(const _DataType& t){if(this->size() < _Size){m_data[m_size++] = t; return GAIA::True;} else return GAIA::False;}
			GINL GAIA::BL pop_back(){if(this->size() > 0){m_size--; return GAIA::True;} else return GAIA::False;}
			GINL const _DataType& front() const{GAIA_ASSERT(this->size() > 0); this->operator[](0);}
			GINL _DataType& front(){GAIA_ASSERT(this->size() > 0); return this->operator[](0);}
			GINL const _DataType& back() const{GAIA_ASSERT(this->size() > 0); this->operator[](this->size() - 1);}
			GINL _DataType& back(){GAIA_ASSERT(this->size() > 0); return this->operator[](this->size() - 1);}
			GINL const _DataType* front_ptr() const{GAIA_ASSERT(this->size() > 0); return &this->operator[](0);}
			GINL _DataType* front_ptr(){GAIA_ASSERT(this->size() > 0); return &this->operator[](0);}
			GINL const _DataType* back_ptr() const{GAIA_ASSERT(this->size() > 0); return &this->operator[](this->size() - 1);}
			GINL _DataType* back_ptr(){GAIA_ASSERT(this->size() > 0); return &this->operator[](this->size() - 1);}
			GINL GAIA::GVOID resize(const _SizeType& size){GAIA_ASSERT(size >= 0 && size <= _Size); m_size = size;}
			GINL GAIA::GVOID reset(const _DataType& t){for(_SizeType x = 0; x < this->size(); ++x) m_data[x] = t;}
			GINL GAIA::GVOID sort(){if(this->size() == 0) return; GAIA::ALGORITHM::sort(m_data, &m_data[this->size() - 1]);}
			GINL _SizeType search(const _DataType& t) const
			{
				if(this->size() <= 0)
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::search(m_data, &m_data[this->size() - 1], t);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_data;
			}
			GINL _SizeType find(const _SizeType& index) const
			{
				if(this->size() == 0)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::find(&m_data[index], &m_data[index]);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_data;
			}
			GINL _SizeType rfind(const _SizeType& index) const
			{
				if(this->size() == 0)
					return (_SizeType)-1;
				if(index >= this->size())
					return (_SizeType)-1;
				_DataType* pFinded = GAIA::ALGORITHM::rfind(m_data, &m_data[index]);
				if(pFinded == GNULL)
					return (_SizeType)-1;
				return pFinded - m_data;
			}
			GINL GAIA::BL replace(const _DataType& t, const _SizeType& index)
			{
			}
			GINL GAIA::BL replace_all(const _DataType& t, const _SizeType& index)
			{
			}
			GINL GAIA::BL erase(const _SizeType& index)
			{
				GAIA_ASSERT(index >= 0);
				if(this->empty())
					return GAIA::False;
				if(index >= this->size())
					return GAIA::False;
				if(index + 1 < this->size())
					GAIA::ALGORITHM::move_prev(&this->operator[](index), &this->operator[](index + 1), this->size() - index - 1);
				m_size--;
				return GAIA::True;
			}
			GINL const _DataType& operator [] (const _SizeType& index) const{return m_data[index];}
			GINL _DataType& operator [] (const _SizeType& index){return m_data[index];}
			GINL BasicArray<_DataType, _SizeType, _Size>& operator << (const _DataType& t){this->push_back(t); return *this;}
			GINL BasicArray<_DataType, _SizeType, _Size>& operator >> (const _DataType& t){this->push_back(t); return *this;}
			GINL BasicArray<_DataType, _SizeType, _Size>& operator = (const BasicArray<_DataType, _SizeType, _Size>& src)
			{
				this->resize(src.size());
				for(_sizetype x = 0; x < src.size(); ++x)
					this->operator[](x) = src[x];
				return *this;
			}
		private:
			GINL GAIA::GVOID init(){m_size = 0;}
		private:
			_DataType m_data[_Size];
			_SizeType m_size;
		};
	};
};

#endif
