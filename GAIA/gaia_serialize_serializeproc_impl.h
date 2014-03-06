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
			typedef GAIA::CONTAINER::BasicArray<_DataType, _SizeType, _Size> __ArrayType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __ArrayType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename __ArrayType::const_it it = t.const_front_it();
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
			typedef GAIA::CONTAINER::BasicArray<_DataType, _SizeType, _Size> __ArrayType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __ArrayType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				typename __ArrayType::it it = t.front_it();
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
			typedef GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __VectorType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __VectorType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename __VectorType::const_it it = t.const_front_it();
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
			typedef GAIA::CONTAINER::BasicVector<_DataType, _SizeType, _SizeIncreaserType> __VectorType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __VectorType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				typename __VectorType::it it = t.front_it();
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
			typedef GAIA::CONTAINER::BasicStack<_DataType, _SizeType, _SizeIncreaserType> __StackType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __StackType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename __StackType::const_it it = t.const_front_it();
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
			typedef GAIA::CONTAINER::BasicStack<_DataType, _SizeType, _SizeIncreaserType> __StackType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __StackType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				typename __StackType::it it = t.front_it();
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
			typedef GAIA::CONTAINER::BasicQueue<_DataType, _SizeType, _SizeIncreaserType> __QueueType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __QueueType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename __QueueType::const_it it = t.const_front_it();
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
			typedef GAIA::CONTAINER::BasicQueue<_DataType, _SizeType, _SizeIncreaserType> __QueueType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __QueueType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				typename __QueueType::it it = t.front_it();
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
			typedef GAIA::CONTAINER::BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __ListType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __ListType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename __ListType::const_it it = t.const_front_it();
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
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
			typedef GAIA::CONTAINER::BasicList<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __ListType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __ListType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				for(typename __ListType::_sizetype x = 0; x < size; ++x)
				{
					typename __ListType::_datatype d;
					if(!serializer_read_proc(p, d))
					{
						pIO->Release();
						return GAIA::False;
					}
					t.push_back(d);
				}
			}
			pIO->Release();
			return GAIA::True;
		}

		/* BasicTree serialize. */
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
			typedef GAIA::CONTAINER::BasicTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __TreeType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			pIO->Release();
			return GAIA::True;
		}
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
			typedef GAIA::CONTAINER::BasicTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __TreeType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			pIO->Release();
			return GAIA::True;
		}

		/* BasicAVLTree serialize. */
		template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize>& t)
		{
			typedef GAIA::CONTAINER::BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __AVLTreeType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				typename __AVLTreeType::const_it it = t.const_front_it();
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
		template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize>& t)
		{
			typedef GAIA::CONTAINER::BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType, _GroupElementSize> __AVLTreeType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __AVLTreeType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				for(typename __AVLTreeType::_sizetype x = 0; x < size; ++x)
				{
					typename __AVLTreeType::_datatype d;
					if(!serializer_read_proc(p, d))
					{
						pIO->Release();
						return GAIA::False;
					}
					t.insert(d);
				}
			}
			pIO->Release();
			return GAIA::True;
		}

		/* BasicTrieTree serialize. */
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
			typedef GAIA::CONTAINER::BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __TrieTreeType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __TrieTreeType::_sizetype size = 0;
			typename __TrieTreeType::const_it it = t.const_front_it();
			while(!it.empty())
			{
				if(t.leaf(it))
					++size;
				++it;
			}
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			it = t.const_front_it();
			while(!it.empty())
			{
				if(t.leaf(it))
				{
					typename __TrieTreeType::_sizetype subsize = 0;
					typename __TrieTreeType::const_it subit = it;
					while(!subit.empty())
					{
						subit = t.parent_it(subit);
						++subsize;
					}
					if(!serializer_write_proc(p, subsize))
					{
						pIO->Release();
						return GAIA::False;
					}
					subit = it;
					while(!subit.empty())
					{
						if(!serializer_write_proc(p, *subit))
						{
							pIO->Release();
							return GAIA::False;
						}
						subit = t.parent_it(subit);
					}
				}
				++it;
			}
			pIO->Release();
			return GAIA::True;
		}
		template<typename _DataType, typename _SizeType, typename _SizeIncreaserType, _SizeType _GroupElementSize> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize>& t)
		{
			typedef GAIA::CONTAINER::BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType, _GroupElementSize> __TrieTreeType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __TrieTreeType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			GAIA::CONTAINER::BasicVector<typename __TrieTreeType::_datatype, _SizeType, _SizeIncreaserType> vt;
			for(typename __TrieTreeType::_sizetype x = 0; x < size; ++x)
			{
				typename __TrieTreeType::_sizetype subsize;
				if(!serializer_read_proc(p, subsize))
				{
					pIO->Release();
					return GAIA::False;
				}
				for(typename __TrieTreeType::_sizetype y = 0; y < subsize; ++y)
				{
					typename __TrieTreeType::_datatype d;
					if(!serializer_read_proc(p, d))
					{
						pIO->Release();
						return GAIA::False;
					}
					vt.push_back(d);
				}
				vt.inverse();
				t.insert(vt.front_ptr(), vt.size());
			}
			pIO->Release();
			return GAIA::True;
		}

		/* BasicStackBitset serialize. */
		template<typename _SizeType, _SizeType _Size> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicStackBitset<_SizeType, _Size>& t)
		{
			typedef GAIA::CONTAINER::BasicStackBitset<_SizeType, _Size> __StackBitsetType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __StackBitsetType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				for(typename __StackBitsetType::_sizetype x = 0; x < t.size(); ++x)
				{
					if(!serializer_write_proc(p, t.front_ptr()[x]))
					{
						pIO->Release();
						return GAIA::False;
					}
				}
			}
			pIO->Release();
			return GAIA::True;
		}
		template<typename _SizeType, _SizeType _Size> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicStackBitset<_SizeType, _Size>& t)
		{
			typedef GAIA::CONTAINER::BasicStackBitset<_SizeType, _Size> __StackBitsetType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __StackBitsetType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				for(typename __StackBitsetType::_sizetype x = 0; x < t.size(); ++x)
				{
					if(!serializer_read_proc(p, t.front_ptr()[x]))
					{
						pIO->Release();
						return GAIA::False;
					}
				}
			}
			pIO->Release();
			return GAIA::True;
		}

		/* BasicBitset serialize. */
		template<typename _SizeType> GINL GAIA::BL
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicBitset<_SizeType>& t)
		{
			typedef GAIA::CONTAINER::BasicBitset<_SizeType> __BitsetType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __BitsetType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				for(typename __BitsetType::_sizetype x = 0; x < t.size(); ++x)
				{
					if(!serializer_write_proc(p, t.front_ptr()[x]))
					{
						pIO->Release();
						return GAIA::False;
					}
				}
			}
			pIO->Release();
			return GAIA::True;
		}
		template<typename _SizeType> GINL GAIA::BL
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicBitset<_SizeType> &t)
		{
			typedef GAIA::CONTAINER::BasicBitset<_SizeType> __BitsetType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __BitsetType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				for(typename __BitsetType::_sizetype x = 0; x < t.size(); ++x)
				{
					if(!serializer_read_proc(p, t.front_ptr()[x]))
					{
						pIO->Release();
						return GAIA::False;
					}
				}
			}
			pIO->Release();
			return GAIA::True;
		}

		/* BasicChars serialize. */
		template<typename _DataType, typename _SizeType, _SizeType _Size> GINL GAIA::BL 
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicChars<_DataType, _SizeType, _Size>& t)
		{
			typedef GAIA::CONTAINER::BasicChars<_DataType, _SizeType, _Size> __CharsType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __CharsType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				for(typename __CharsType::_sizetype x = 0; x < size; ++x)
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
		template<typename _DataType, typename _SizeType, _SizeType _Size> GINL GAIA::BL 
			serializer_read_proc(Serializer* p, GAIA::CONTAINER::BasicChars<_DataType, _SizeType, _Size>& t)
		{
			typedef GAIA::CONTAINER::BasicChars<_DataType, _SizeType, _Size> __CharsType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __CharsType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > t.capacity())
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				for(typename __CharsType::_sizetype x = 0; x < size; ++x)
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

		/* BasicString serialize. */
		template<typename _DataType, typename _SizeType> GINL GAIA::BL 
			serializer_write_proc(Serializer* p, const GAIA::CONTAINER::BasicString<_DataType, _SizeType>& t)
		{
			typedef GAIA::CONTAINER::BasicString<_DataType, _SizeType> __StringType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			typename __StringType::_sizetype size = t.size();
			if(!serializer_write_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				for(typename __StringType::_sizetype x = 0; x < size; ++x)
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
			typedef GAIA::CONTAINER::BasicString<_DataType, _SizeType> __StringType;
			GAIA::IO::IO* pIO = p->GetBindIO();
			if(pIO == GNULL)
				return GAIA::False;
			t.clear();
			typename __StringType::_sizetype size;
			if(!serializer_read_proc(p, size))
			{
				pIO->Release();
				return GAIA::False;
			}
			if(size > 0)
			{
				t.resize(size);
				for(typename __StringType::_sizetype x = 0; x < size; ++x)
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