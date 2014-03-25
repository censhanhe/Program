#ifndef 	__GAIA_MATH_RANDOM_H__
#define 	__GAIA_MATH_RANDOM_H__

namespace GAIA
{
	namespace MATH
	{
		GAIA_DEBUG_CODEPURE_FUNC GAIA::N32 random();
		GAIA_DEBUG_CODEPURE_FUNC GAIA::GVOID random_seed(GAIA::N32 seed);
		template<GAIA::NM _Size> class RID
		{
		public:
			static const GAIA::NM _size = _Size;
		public:
			typedef RID<_Size> __MyType;
		public:
			GINL GAIA::BL empty() const;
			GINL GAIA::BL clear() const;
			GINL GAIA::GVOID generate();
			GINL GAIA::GVOID fromstring(const GAIA::GCH* psz);
			GINL GAIA::GVOID tostring(GAIA::GCH* psz);
			GINL RID& operator = (const RID& src);
			GINL GAIA::BL operator == (const RID& src) const;
			GINL GAIA::BL operator != (const RID& src) const;
			GINL GAIA::BL operator >= (const RID& src) const;
			GINL GAIA::BL operator <= (const RID& src) const;
			GINL GAIA::BL operator > (const RID& src) const;
			GINL GAIA::BL operator < (const RID& src) const;
		public:
			/*
			*	The following property we can select for generate RID in
			*	many versions(RID's version in different length).
			*
			*		Time property(Total	52B).
			*		0.)		Year				(6B)		[0,64)
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
			GAIA::U8 u[_Size];
		};
	};
};

#ifndef GAIA_DEBUG_CODEPURE
#	include "gaia_math_random_indp.h"
#endif

#endif
