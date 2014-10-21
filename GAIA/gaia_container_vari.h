#ifndef		__GAIA_CONTAINER_VARI_H__
#define		__GAIA_CONTAINER_VARI_H__

namespace GAIA
{
	namespace CTN
	{
		class Vari : public GAIA::Entity
		{
		public:
			GAIA_ENUM_BEGIN(TYPE)
				TYPE_BL,
				TYPE_N8,
				TYPE_N16,
				TYPE_N32,
				TYPE_N64,
				TYPE_U8,
				TYPE_U16,
				TYPE_U32,
				TYPE_U64,
				TYPE_X128,
				TYPE_F32,
				TYPE_F64,
				TYPE_REAL,
			GAIA_ENUM_END(TYPE)

		public:
			GINL Vari();
			GINL ~Vari();
			GINL Vari& operator = (const Vari& src);
			GINL GAIA::BL operator == (const Vari& src) const;
			GINL GAIA::BL operator != (const Vari& src) const;
			GINL GAIA::BL operator >= (const Vari& src) const;
			GINL GAIA::BL operator <= (const Vari& src) const;
			GINL GAIA::BL operator > (const Vari& src) const;
			GINL GAIA::BL operator < (const Vari& src) const;
		private:
			union
			{
				GAIA::BL b;

				GAIA::N8 n8;
				GAIA::N16 n16;
				GAIA::N32 n32;
				GAIA::N64 n64;
				GAIA::U8 u8;
				GAIA::U16 u16;
				GAIA::U32 u32;
				GAIA::U64 u64;
				GAIA::F32 f32;
				GAIA::F64 f64;
				GAIA::REAL real;
			};
			GAIA::X128 x128;
		};
	};
};

#endif
