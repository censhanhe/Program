#ifndef		__GAIA_SERIALIZE_SERIALIZE_PROC_IMPL_H__
#define		__GAIA_SERIALIZE_SERIALIZE_PROC_IMPL_H__

namespace GAIA
{
	namespace SERIALIZER
	{
		class Serializer;

		/* Base type serialize. */
		template<typename _ParamType> GINL GAIA::BL serializer_write_proc(Serializer* p, const _ParamType& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			pIO->Write(&t, sizeof(t));
			pIO->Release();
			return GAIA::True;
		}
		template<typename _ParamType> GINL GAIA::BL serializer_read_proc(Serializer* p, _ParamType& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			pIO->Read(&t, sizeof(t));
			pIO->Release();
			return GAIA::True;
		}

		/* BasicArray serialize. */
		template<typename _DataType, typename _SizeType, _SizeType _Size> GINL GAIA::BL 
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicArray<_DataType, _SizeType, _Size>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicArray<_DataType, _SizeType, _Size>::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename GAIA::CONTAINER::BasicArray<_DataType, _SizeType, _Size>::const_it it = t.const_front_it();
				while(!it.empty())
				{
					if(!serializer_write_proc(p, *it))
					{
						pIO->Release();
						return GAIA::False;
					}
					++it;
				}
			}
			pIO->Release();
			return GAIA::True;
		}
		template<typename _DataType, typename _SizeType, _SizeType _Size> GINL GAIA::BL 
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicArray<_DataType, _SizeType, _Size>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicArray<_DataType, _SizeType, _Size>::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				typename GAIA::CONTAINER::BasicArray<_DataType, _SizeType, _Size>::it it = t.front_it();
				while(!it.empty())
				{
					if(!serializer_read_proc(p, *it))
					{
						pIO->Release();
						return GAIA::False;
					}
					++it;
				}
			}
			pIO->Release();
			return GAIA::True;
		}
		/* BasicVector serialize. */
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GINL GAIA::BL 
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType>::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType>::const_it it = t.const_front_it();
				while(!it.empty())
				{
					if(!serializer_write_proc(p, *it))
					{
						pIO->Release();
						return GAIA::False;
					}
					++it;
				}
			}
			pIO->Release();
			return GAIA::True;
		}
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GINL GAIA::BL 
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType>::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				typename GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType>::it it = t.front_it();
				while(!it.empty())
				{
					if(!serializer_read_proc(p, *it))
					{
						pIO->Release();
						return GAIA::False;
					}
					++it;
				}
			}
			pIO->Release();
			return GAIA::True;
		}

		/* BasicStack serialize. */
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicStack<_DataType, _SizeType, _SizeIncreaserType>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicStack<_DataType, _SizeType, _SizeIncreaserType>::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename GAIA::CONTAINER::BasicStack<_DataType, _SizeType, _SizeIncreaserType>::const_it it = t.const_front_it();
				while(!it.empty())
				{
					if(!serializer_write_proc(p, *it))
					{
						pIO->Release();
						return GAIA::False;
					}
					++it;
				}
			}
			pIO->Release();
			return GAIA::True;
		}
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicStack<_DataType, _SizeType, _SizeIncreaserType>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicStack<_DataType, _SizeType, _SizeIncreaserType>::_sizetype size = t.size();
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				typename GAIA::CONTAINER::BasicStack<_DataType, _SizeType, _SizeIncreaserType>::it it = t.front_it();
				while(!it.empty())
				{
					if(!serializer_read_proc(p, *it))
					{
						pIO->Release();
						return GAIA::False;
					}
					++it;
				}
			}
			pIO->Release();
			return GAIA::True;
		}

		/* BasicQueue serialize. */
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicQueue<_DataType, _SizeType, _SizeIncreaserType>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicQueue<_DataType, _SizeType, _SizeIncreaserType>::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename GAIA::CONTAINER::BasicQueue<_DataType, _SizeType, _SizeIncreaserType>::const_it it = t.const_front_it();
				while(!it.empty())
				{
					if(!serializer_write_proc(p, *it))
					{
						pIO->Release();
						return GAIA::False;
					}
					++it;
				}
			}
			pIO->Release();
			return GAIA::True;
		}
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicQueue<_DataType, _SizeType, _SizeIncreaserType>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicQueue<_DataType, _SizeType, _SizeIncreaserType>::_sizetype size = t.size();
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				typename GAIA::CONTAINER::BasicQueue<_DataType, _SizeType, _SizeIncreaserType>::it it = t.front_it();
				while(!it.empty())
				{
					if(!serializer_read_proc(p, *it))
					{
						pIO->Release();
						return GAIA::False;
					}
					++it;
				}
			}
			pIO->Release();
			return GAIA::True;
		}

		/* BasicList serialize. */
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
		}
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
		}
		/* BasicTree serialize. */
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
		}
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
		}
		/* BasicAVLTree serialize. */
		template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize>& t)
		{
		}
		template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize>& t)
		{
		}
		/* BasicTrieTree serialize. */
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
		}
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
		}
		/* BasicString serialize. */
		template<typename _DataType, typename _SizeType> GINL GAIA::BL 
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicString<_DataType, _SizeType>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicString<_DataType, _SizeType>::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				for(typename GAIA::CONTAINER::BasicString<_DataType, _SizeType>::_sizetype x = 0; x < size; ++x)
				{
					if(!serializer_write_proc(p, t[x]))
					{
						pIO->Release();
						return GAIA::False;
					}
				}
			}
			pIO->Release();
			return GAIA::True;
		}
		template<typename _DataType, typename _SizeType> GINL GAIA::BL 
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicString<_DataType, _SizeType>& t)
		{
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename GAIA::CONTAINER::BasicString<_DataType, _SizeType>::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				for(typename GAIA::CONTAINER::BasicString<_DataType, _SizeType>::_sizetype x = 0; x < size; ++x)
				{
					if(!serializer_read_proc(p, t[x]))
					{
						pIO->Release();
						return GAIA::False;
					}
				}
			}
			pIO->Release();
			return GAIA::True;
		}
	};
};

#endif
