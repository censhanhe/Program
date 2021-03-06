#ifndef		__GAIA_SERIALIZE_SERIALIZE_PROC_H__
#define		__GAIA_SERIALIZE_SERIALIZE_PROC_H__

namespace GAIA
{
	namespace SERIALIZER
	{
		class SerializerProc
		{
		public:
			/* Base type serialize. */
			template<typename _ParamType> GAIA::BL write(Serializer* p, const _ParamType& t);
			template<typename _ParamType> GAIA::BL read(Serializer* p, _ParamType& t);

			/* BasicArray serialize. */
			template<typename _DataType, typename _SizeType, _SizeType _Size> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicArray<_DataType, _SizeType, _Size>& t);
			template<typename _DataType, typename _SizeType, _SizeType _Size> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicArray<_DataType, _SizeType, _Size>& t);

			/* BasicVector serialize. */
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicVector<_DataType, _SizeType, _SizeIncreaserType>& t);
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicVector<_DataType, _SizeType, _SizeIncreaserType>& t);

			/* BasicStack serialize. */
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicStack<_DataType, _SizeType, _SizeIncreaserType>& t);
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicStack<_DataType, _SizeType, _SizeIncreaserType>& t);

			/* BasicQueue serialize. */
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicQueue<_DataType, _SizeType, _SizeIncreaserType>& t);
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicQueue<_DataType, _SizeType, _SizeIncreaserType>& t);

			/* BasicList serialize. */
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicList<_DataType, _SizeType, _SizeIncreaserType>& t);
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicList<_DataType, _SizeType, _SizeIncreaserType>& t);

			/* BasicTree serialize. */
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicTree<_DataType, _SizeType, _SizeIncreaserType>& t);
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicTree<_DataType, _SizeType, _SizeIncreaserType>& t);

			/* BasicAVLTree serialize. */
			template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType>& t);
			template<typename _DataType, typename _SizeType, typename _HeightType, typename _SizeIncreaserType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicAVLTree<_DataType, _SizeType, _HeightType, _SizeIncreaserType>& t);

			/* BasicTrieTree serialize. */
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType>& t);
			template<typename _DataType, typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicTrieTree<_DataType, _SizeType, _SizeIncreaserType>& t);

			/* BasicBuffer serialize. */

			/* BasicOrderless serialize */

			/* BasicStackBitset serialize. */
			template<typename _SizeType, _SizeType _Size> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicStackBitset<_SizeType, _Size>& t);
			template<typename _SizeType, _SizeType _Size> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicStackBitset<_SizeType, _Size>& t);

			/* BasicBitset serialize. */
			template<typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicBitset<_SizeType, _SizeIncreaserType>& t);
			template<typename _SizeType, typename _SizeIncreaserType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicBitset<_SizeType, _SizeIncreaserType> &t);

			/* BasicStorage serialize. */

			/* BasicChars serialize. */
			template<typename _DataType, typename _SizeType, _SizeType _Size> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicChars<_DataType, _SizeType, _Size>& t);
			template<typename _DataType, typename _SizeType, _SizeType _Size> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicChars<_DataType, _SizeType, _Size>& t);

			/* BasicString serialize. */
			template<typename _DataType, typename _SizeType> GAIA::BL
				write(Serializer* p, const GAIA::CTN::BasicString<_DataType, _SizeType>& t);
			template<typename _DataType, typename _SizeType> GAIA::BL
				read(Serializer* p, GAIA::CTN::BasicString<_DataType, _SizeType>& t);

			/* BasicGraph serialize. */

			/* Ref serialize. */

			/* Ptr serialize. */

			/* Var serialize. */

	#ifdef GAIA_DEBUG_MACHINELENGTH
		private: // Protect for 32-64bit error.
			GINL GAIA::BL write(Serializer* p, const GAIA::NM& t);
			GINL GAIA::BL read(Serializer* p, GAIA::NM& t);
			GINL GAIA::BL write(Serializer* p, const GAIA::UM& t);
			GINL GAIA::BL read(Serializer* p, GAIA::UM& t);
		};
	#endif
	};
};

#endif
