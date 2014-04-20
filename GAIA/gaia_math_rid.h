#ifndef 	__GAIA_MATH_RID_H__
#define 	__GAIA_MATH_RID_H__

namespace GAIA
{
	namespace MATH
	{
		/*
		 *	The following property we can select for generate RID in
		 *	many versions(RID's version in different length).
		 *
		 *		Time property(Total	52B).
		 *		0.)		Year				(6B)		[0,64)		Base time is 2014.
		 *		1.)		Month				(4B)		[0,16)
		 *		2.)		Day					(5B)		[0,32)
		 *		3.)		Hour				(5B)		[0,32)
		 *		4.)		Minute				(6B)		[0,64)
		 *		5.)		Second				(6B)		[0,64)
		 *		7.)		MSecond				(10B)		[0,1024)
		 *		8.)		USecond				(10B)		[0,1024)
		 *
		 *		Random property.
		 *		0.)		PIDSeedRandom		(12B)		[0,4096)
		 *		1.)		TIDSeedRandom		(15B)		[0,32768)
		 *		2.)		FileLineSeedRandom	(4B)		[0,16)
		 *		3.)		StartTimeSeedRandom	(13)		[0,8192)
		 *
		 *		Serial property.
		 *		0.)		SelfIncreaseSerial	(22)		[0,4194304)
		 *
		 *		Location property.
		 *		0.)		EarthZone			(2B)		[0,3)		0 means asia, 1 means america, 2 means europe, 3 means oceania.
		 *		1.)		IPTail				(8B)		[0,256)
		 */

		/* 128 bit random id. */
		class RID128 : public GAIA::Base
		{
		public:
			GINL GAIA::BL empty() const{return u64_0 == 0 && u64_1 == 0;}
			GINL GAIA::GVOID clear(){u64_0 = u64_1 = 0;}
			GINL GAIA::GVOID generate()
			{
				GAIA::TIME::Time t;
				GAIA::U16 uPIDSeedRandom;
				GAIA::U16 uTIDSeedRandom;
				GAIA::U8 uFileLineSeedRandom;
				GAIA::U16 uStartTimeSeedRandom;
				
			}
			GINL GAIA::GVOID fromstring(const GAIA::GCH* psz){GAIA::ALGORITHM::str2hex(psz, sizeofarray(u), u);}
			GINL GAIA::GVOID tostring(GAIA::GCH* psz){GAIA::ALGORITHM::hex2str(u, sizeofarray(u), psz);}
			GINL RID128& operator = (const RID128& src){u64_0 = src.u64_0; u64_1 = src.u64_1; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE2(u64_0, u64_0, u64_1, u64_1, RID128);
		public:
			union
			{
				GAIA::U8 u[16];
				class
				{
				public:
					GAIA::U32 u0;
					GAIA::U32 u1;
					GAIA::U32 u2;
					GAIA::U32 u3;
				};
				class
				{
				public:
					GAIA::U64 u64_0;
					GAIA::U64 u64_1;
				};
			};
		};

		/* 64 bit random id. */
		class RID64 : public GAIA::Base
		{
		public:
			GINL GAIA::BL empty() const{return u64_0 == 0;}
			GINL GAIA::GVOID clear(){u64_0 = 0;}
			GINL GAIA::GVOID generate(){}
			GINL GAIA::GVOID fromstring(const GAIA::GCH* psz){GAIA::ALGORITHM::str2hex(psz, sizeofarray(u), u);}
			GINL GAIA::GVOID tostring(GAIA::GCH* psz){GAIA::ALGORITHM::hex2str(u, sizeofarray(u), psz);}
			GINL RID64& operator = (const RID64& src){u64_0 = src.u64_0; return *this;}
			GAIA_CLASS_OPERATOR_COMPARE(u64_0, u64_0, RID64);
		public:
			union
			{
				GAIA::U8 u[8];
				class
				{
				public:
					GAIA::U32 u0;
					GAIA::U32 u1;
				};
				class
				{
				public:
					GAIA::U64 u64_0;
				};
			};
		};
	};
};

#endif
