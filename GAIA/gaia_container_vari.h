#ifndef		__GAIA_CONTAINER_VARI_H__
#define		__GAIA_CONTAINER_VARI_H__

namespace GAIA
{
	namespace CONTAINER
	{
		class Vari : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(VARI_TYPE)
				VARI_TYPE_BL,
				VARI_TYPE_N8,
				VARI_TYPE_N16,
				VARI_TYPE_N32,
				VARI_TYPE_N64,
				VARI_TYPE_U8,
				VARI_TYPE_U16,
				VARI_TYPE_U32,
				VARI_TYPE_U64,
				VARY_TYPE_X128,
				VARI_TYPE_F32,
				VARI_TYPE_F64,
				VARI_TYPE_REAL,
			GAIA_ENUM_END(VARI_TYPE)

		public:
			GINL Vari();
			GINL ~Vari();

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
			GAIA::X128		x128;
		};
	};
};

#endif