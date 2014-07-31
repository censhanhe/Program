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
			GINL Obj(){this->init();}
		public:
			virtual const GAIA::TCH* GetName() const{return GNULL;}
			virtual GAIA::SIZE GetNameSize() const{return GINVALID;}
			virtual TYPE GetType() const{return TYPE_INVALID;}
			virtual STRUCTTYPE GetStructType() const{return STRUCTTYPE_INVALID;}
			virtual REFTYPE GetRefType() const{return REFTYPE_INVALID;}
		public:
			GINL GAIA::GVOID SetLocation(const Loc& l){m_loc = l;}
			GINL const Loc& GetLocation() const{return m_loc;}
			GINL GAIA::GVOID SetNameIndex(const GAIA::SIZE& index){m_nameindex = index;}
			GINL GAIA::SIZE GetNameIndex() const{return m_nameindex;}
			GINL GAIA::GVOID SetTypeIndex(const GAIA::SIZE& index){m_typeindex = index;}
			GINL GAIA::SIZE GetTypeIndex() const{return m_typeindex;}
		private:
			GINL GAIA::GVOID init()
			{
				m_nameindex = GINVALID;
				m_typeindex = GINVALID;
			}
		private:
			Loc m_loc;
			GAIA::SIZE m_nameindex;
			GAIA::SIZE m_typeindex;
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
		};
		class RecLocation : public Rec
		{
		public:
			GINL GAIA::BL operator == (const RecLocation& src) const{return pObj->GetLocation() == src.pObj->GetLocation();}
			GINL GAIA::BL operator != (const RecLocation& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const RecLocation& src) const{return pObj->GetLocation() >= src.pObj->GetLocation();}
			GINL GAIA::BL operator <= (const RecLocation& src) const{return pObj->GetLocation() <= src.pObj->GetLocation();}
			GINL GAIA::BL operator > (const RecLocation& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const RecLocation& src) const{return !this->operator >= (src);}
		};
		class RecName : public Rec
		{
		public:
			GINL GAIA::BL operator == (const RecName& src) const{return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) == 0;}
			GINL GAIA::BL operator != (const RecName& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const RecName& src) const{return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) >= 0;}
			GINL GAIA::BL operator <= (const RecName& src) const{return GAIA::ALGORITHM::cmps(pObj->GetName(), pObj->GetNameSize(), src.pObj->GetName(), src.pObj->GetNameSize()) <= 0;}
			GINL GAIA::BL operator > (const RecName& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const RecName& src) const{return !this->operator >= (src);}
		};
		class RecType : public Rec
		{
		public:
			GINL GAIA::BL operator == (const RecLocation& src) const{return pObj->GetType() == src.pObj->GetType();}
			GINL GAIA::BL operator != (const RecLocation& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const RecLocation& src) const{return pObj->GetType() >= src.pObj->GetType();}
			GINL GAIA::BL operator <= (const RecLocation& src) const{return pObj->GetType() <= src.pObj->GetType();}
			GINL GAIA::BL operator > (const RecLocation& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const RecLocation& src) const{return !this->operator >= (src);}
		};
	public:
		GINL PLC_ObjCtn(){}
		GINL ~PLC_ObjCtn(){}
		virtual const GAIA::TCH* GetName() const{return _T("Prom:PLC_ObjCtn");}
		GINL GAIA::BL AddObj(Obj* pObj)
		{
			GPCHR_NULL_RET(pObj, GAIA::False);
			GAIA_AST(pObj->GetNameIndex() == GINVALID);
			GAIA_AST(pObj->GetTypeIndex() == GINVALID);
			if(this->FindObjByLoc(pObj->GetLocation()) != GNULL)
				return GAIA::False;
			RecLocation rl;
			rl.pObj = pObj;
			if(!rec_location.insert(rl))
				return GAIA::False;
			RecName rn;
			rn.pObj = pObj;
			pObj->SetNameIndex(rec_name.insert(rn));
			RecType rt;
			rt.pObj = pObj;
			pObj->SetTypeIndex(rec_type.insert(rt));
			return GAIA::True;
		}
		GINL GAIA::BL DeleteObj(Obj* pObj)
		{
			GPCHR_NULL_RET(pObj, GAIA::False);
			if(this->FindObjByLoc(pObj->GetLocation()) == GNULL)
				return GAIA::False;
			RecLocation rl;
			rl.pObj = pObj;
			if(!rec_location.erase(rl))
				return GAIA::False;
			rec_name.erase_index(pObj->GetNameIndex());
			rec_type.erase_index(pObj->GetTypeIndex());
			return GAIA::True;
		}
		GINL GAIA::GVOID DeleteObjAll()
		{
			rec_location.clear();
			rec_name.clear();
			rec_type.clear();
		}
		GINL Obj* FindObjByLoc(const Loc& loc) const
		{
			Obj obj;
			obj.SetLocation(loc);
			RecLocation rl;
			rl.pObj = &obj;
			const RecLocation* pFinded = rec_location.find(rl);
			if(pFinded == GNULL)
				return GNULL;
			return pFinded->pObj;
		}
		GINL GAIA::BL FindObjByName(const GAIA::TCH* pszName, GAIA::CONTAINER::Vector<Obj*>& listResult) const
		{
			GPCHR_NULLSTRPTR_RET(pszName, GAIA::False);
			GAIA::BL bRet = GAIA::False;
			GAIA::SIZE namelen = GAIA::ALGORITHM::strlen(pszName);
			for(GAIA::SIZE x = 0; x < rec_name.size(); ++x)
			{
				if(!rec_name.exist(x))
					continue;
				Obj* pObj = rec_name[x].pObj;
				if(pObj == GNULL)
					continue;
				const GAIA::TCH* pszTempName = pObj->GetName();
				if(GAIA::ALGORITHM::stremp(pszTempName))
					continue;
				if(pObj->GetNameSize() != namelen)
					continue;
				if(GAIA::ALGORITHM::xmemcmp(pszTempName, pszName, namelen * sizeof(GAIA::TCH)) == 0)
				{
					listResult.push_back(pObj);
					bRet = GAIA::True;
				}
			}
			return bRet;
		}
		GINL GAIA::BL FindObjByType(Obj::TYPE type, GAIA::CONTAINER::Vector<Obj*> &listResult) const
		{
			GAIA::BL bRet = GAIA::False;
			for(GAIA::SIZE x = 0; x < rec_type.size(); ++x)
			{
				if(!rec_type.exist(x))
					continue;
				Obj* pObj = rec_type[x].pObj;
				if(pObj == GNULL)
					continue;
				if(pObj->GetType() == type)
				{
					listResult.push_back(pObj);
					bRet = GAIA::True;
				}
			}
			return bRet;
		}
	public:
		typedef GAIA::CONTAINER::Set<RecLocation> __RecLocationSetType;
		typedef GAIA::CONTAINER::Orderless<RecName> __RecNameListType;
		typedef GAIA::CONTAINER::Orderless<RecType> __RecTypeListType;
	public:
		__RecLocationSetType rec_location;
		__RecNameListType rec_name;
		__RecTypeListType rec_type;
	};
};

#endif