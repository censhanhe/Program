#ifndef		__GAIA_FAVO_FETCHDATA_H__
#define		__GAIA_FAVO_FETCHDATA_H__

namespace GAIA
{
	namespace FAVO
	{
		class FetchDataBase : public virtual GAIA::FWORK::Instance
		{
		public:
			class FetchDataDesc : public virtual GAIA::FWORK::InstanceDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					bDiscard = GAIA::True;
				}
				virtual GAIA::BL check() const
				{
					return GAIA::True;
				}
				GAIA::U8 bDiscard : 1;
			};
		public:
			virtual const FetchDataDesc& GetDesc() const = 0;
			virtual GAIA::SIZE GetSize() const = 0;
			virtual GAIA::BL Set(const GAIA::GVOID* p, const GAIA::SIZE& sOffset, const GAIA::SIZE& sSize);
			virtual GAIA::BL Get(GAIA::GVOID* p, const GAIA::SIZE& sOffset, const GAIA::SIZE& sSize);
			virtual GAIA::SIZE GetSequenceSize() const = 0;
			virtual GAIA::GVOID* GetSequenceHead(const GAIA::SIZE& sOffset) const = 0;
		};

		class FetchData1 : public virtual FetchDataBase
		{
		public:
			class FetchDataDesc : public virtual FetchDataBase::FetchDataDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					FetchDataBase::FetchDataDesc::reset();
					sOffsetX = 0;
					sSizeX = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!FetchDataBase::FetchDataDesc::check())
						return GAIA::False;
					if(sOffsetX < 0)
						return GAIA::False;
					if(sSizeX <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				GAIA::SIZE sOffsetX;
				GAIA::SIZE sSizeX;
			};
		public:
		};

		class FetchData2 : public virtual FetchData1
		{
		public:
			class FetchDataDesc : public virtual FetchData1::FetchDataDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					FetchData1::FetchDataDesc::reset();
					sOffsetY = 0;
					sSizeY = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!FetchData1::FetchDataDesc::check())
						return GAIA::False;
					if(sOffsetY < 0)
						return GAIA::False;
					if(sSizeY <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				GAIA::SIZE sOffsetY;
				GAIA::SIZE sSizeY;
			};
		public:
		};

		class FetchData3 : public virtual FetchData2
		{
		public:
			class FetchDataDesc : public virtual FetchData2::FetchDataDesc
			{
			public:
				virtual GAIA::GVOID reset()
				{
					FetchData2::FetchDataDesc::reset();
					sOffsetZ = 0;
					sSizeZ = 0;
				}
				virtual GAIA::BL check() const
				{
					if(!FetchData2::FetchDataDesc::check())
						return GAIA::False;
					if(sOffsetZ < 0)
						return GAIA::False;
					if(sSizeZ <= 0)
						return GAIA::False;
					return GAIA::True;
				}
				GAIA::SIZE sOffsetZ;
				GAIA::SIZE sSizeZ;
			};
		public:
		};
	};
};

#endif