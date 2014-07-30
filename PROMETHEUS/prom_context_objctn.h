#ifndef		__PROM_CONTEXT_OBJCTN_H__
#define		__PROM_CONTEXT_OBJCTN_H__

namespace PROM
{
	class PLC_ObjCtn : public PipelineContext
	{
	public:
		class Obj : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(TYPE)
				MACRO,
				INCLUDE,
				TEMPLATE,
				EXPRESSION,
				VAR,
				ARRAY,
				FUNC,
				ENUM,
				UNION,
				STRUCT,
				CLASS,
				NAMESPACE,
				FIELD,
				OTHERS,
				GAIA_ENUM_END(TYPE)

				GAIA_ENUM_BEGIN(STRUCTTYPE)
				DECLARATION,
				IMPLEMENT,
				GAIA_ENUM_END(STRUCTTYPE)

				GAIA_ENUM_BEGIN(REFTYPE)
				INST,
				REF,
				PTR,
				GAIA_ENUM_END(REFTYPE)
		public:
			virtual const GAIA::TCH* GetName() const{return GNULL;}
			virtual GAIA::SIZE GetNameSize() const{return GINVALID;}
			virtual TYPE GetType() const{return TYPE_INVALID;}
			virtual STRUCTTYPE GetStructType() const{return STRUCTTYPE_INVALID;}
			virtual REFTYPE GetRefType() const{return REFTYPE_INVALID;}
		public:
			GINL GAIA::GVOID SetLocation(const Loc& l){m_loc = l;}
			GINL const Loc& GetLocation() const{return m_loc;}
		private:
			Loc m_loc;
		};
		class ObjVar
		{
		public:
			GAIA_ENUM_BEGIN(TYPE)
				BOOL,
				INT8,
				INT16,
				INT32,
				INT64,
				REAL32,
				REAL64,
				STRING,
				WSTRING,
				GAIA_ENUM_END(TYPE)
		};
		class ObjExpression
		{
		public:
			GAIA_ENUM_BEGIN(TYPE)
				PRE_INC,
				PRE_DEC,
				POST_INC,
				POST_DEC,
				ADD1,
				SUB1,
				MUL1,
				DIV1,
				ADD2,
				SUB2,
				MUL2,
				DIV2,
				MOD,
				GAIA_ENUM_END(TYPE)
		};
		class Rec : public GAIA::Base
		{
		public:
			Obj* pObj;
			GAIA::SIZE uLocationIndex;
			GAIA::SIZE uNameIndex;
			GAIA::SIZE uTypeIndex;
		};
		class RecLocation : public Rec
		{
		public:
			GINL GAIA::BL operator == (const RecLocation& src){return pObj->GetLocation() == src.pObj->GetLocation();}
			GINL GAIA::BL operator != (const RecLocation& src){return !this->operator == (src);}
			GINL GAIA::BL operator >= (const RecLocation& src){return pObj->GetLocation() >= src.pObj->GetLocation();}
			GINL GAIA::BL operator <= (const RecLocation& src){return pObj->GetLocation() <= src.pObj->GetLocation();}
			GINL GAIA::BL operator > (const RecLocation& src){return !this->operator <= (src);}
			GINL GAIA::BL operator < (const RecLocation& src){return !this->operator >= (src);}
		};
		class RecName : public Rec
		{
		public:
			GINL GAIA::BL operator == (const RecName& src){return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) == 0;}
			GINL GAIA::BL operator != (const RecName& src){return !this->operator == (src);}
			GINL GAIA::BL operator >= (const RecName& src){return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) >= 0;}
			GINL GAIA::BL operator <= (const RecName& src){return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) <= 0;}
			GINL GAIA::BL operator > (const RecName& src){return !this->operator <= (src);}
			GINL GAIA::BL operator < (const RecName& src){return !this->operator >= (src);}
		};
		class RecType : public Rec
		{
		public:
			GINL GAIA::BL operator == (const RecLocation& src){return pObj->GetType() == src.pObj->GetType();}
			GINL GAIA::BL operator != (const RecLocation& src){return !this->operator == (src);}
			GINL GAIA::BL operator >= (const RecLocation& src){return pObj->GetType() >= src.pObj->GetType();}
			GINL GAIA::BL operator <= (const RecLocation& src){return pObj->GetType() <= src.pObj->GetType();}
			GINL GAIA::BL operator > (const RecLocation& src){return !this->operator <= (src);}
			GINL GAIA::BL operator < (const RecLocation& src){return !this->operator >= (src);}
		};
	public:
		GINL PLC_ObjCtn(){}
		GINL ~PLC_ObjCtn(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_ObjCtn");}
	public:
		typedef GAIA::CONTAINER::Vector<RecLocation> __RecLocationListType;
		typedef GAIA::CONTAINER::Vector<RecName> __RecNameListType;
		typedef GAIA::CONTAINER::Vector<RecType> __RecTypeListType;
	public:
		__RecLocationListType rec_location;
		__RecNameListType rec_name;
		__RecTypeListType rec_type;
	};
};

#endif