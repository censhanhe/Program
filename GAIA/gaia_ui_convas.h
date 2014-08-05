#ifndef		__GAIA_UI_CONVAS_H__
#define		__GAIA_UI_CONVAS_H__

namespace GAIA
{
	namespace UI
	{
		class Convas : public GAIA::FRAMEWORK::Instance
		{
		public:
			typedef GAIA::MATH::VEC2<GAIA::N32> __PosType;
			typedef __PosType __SizeType;
		public:
			GAIA::GVOID Show(GAIA::BL bShow);
			GAIA::BL IsShow() const;
			GAIA::GVOID Position(const __PosType& pos);
			const __PosType& Position() const;
			GAIA::GVOID Size(const __SizeType& pos);
			const __SizeType& Size() const;
		};
	};
};

#endif