#ifndef		__DWARFS_MISC_EXPRESS_H__
#define		__DWARFS_MISC_EXPRESS_H__

namespace DWARFS_MISC
{
	template<typename _CharType, typename _CalUnitType> class Express : public GAIA::Entity
	{
	public:
		typedef _CharType _chartype;
		typedef _CalUnitType _calunittype;
	public:
		typedef GAIA::CONTAINER::BasicString<_CharType, GAIA::SIZE> __StringType;
		typedef Express<_CharType, _CalUnitType> __MyType;
	public:
		GINL Express(){}
		GINL ~Express(){}
		GINL GAIA::SIZE get_formula_count() const{return m_fmlist.size();}
		GINL const _CharType* get_formula(const GAIA::SIZE& index) const{return m_fmlist[index].formula;}
		GINL GAIA::BL set_formula(const GAIA::SIZE& index, const _CharType* pFormula)
		{
			GPCHR_NULL_RET(pFormula, GAIA::False);
			m_fmlist[index].formula = pFormula;
			return GAIA::True;
		}
		GINL GAIA::SIZE add_formula(const _CharType* pName, const _CharType* pFormula)
		{
			GPCHR_NULLSTRPTR_RET(pName, GINVALID);
			GPCHR_NULL_RET(pFormula, GINVALID);
			if(this->get_formula_by_name(pName) != GINVALID)
				return GINVALID;
			if(m_freestack.empty())
			{
				Formula newf;
				newf.index = m_fmlist.size();
				m_fmlist.push_back(newf);
				m_fmlist.back().name = pName;
				m_fmlist.back().formula = pFormula;
				m_fmset.insert(m_fmlist.back());
				return newf.index;
			}
			else
			{
				Formula& oldf = m_fmlist[m_freestack.back()];
				oldf.name = pName;
				oldf.formula = pFormula;
				m_fmset.insert(oldf);
				return oldf.index;
			}
		}
		GINL GAIA::BL delete_formula(const GAIA::SIZE& index)
		{
			Formula& oldf = m_fmlist[index];
			if(oldf.name.empty())
				return GAIA::False;
			if(!m_fmset.erase(oldf))
				return GAIA::False;
			oldf.name.clear();
			oldf.formula.clear();
			m_freestack.push_back(oldf.index);
			return GAIA::True;
		}
		GINL GAIA::BL delete_formula_all()
		{
			m_fmlist.clear();
			m_fmset.clear();
			m_freestack.clear();
			return GAIA::True;
		}
		GINL GAIA::SIZE get_formula_by_name(const _CharType* pName)
		{
			GPCHR_NULLSTRPTR_RET(pName, GINVALID);
			m_finder.name = pName;
			typename __FormulaSetType::_datatype reffinder(&m_finder);
			const typename __FormulaSetType::_datatype* pFinded = m_fmset.find(reffinder);
			if(pFinded == GNULL)
				return GINVALID;
			return pFinded->index;
		}
		GINL GAIA::BL calculate(const _CharType* pName, _CharType* pResult, GAIA::SIZE& uResuleSize)
		{
		}
	private:
		class Formula : public GAIA::Base
		{
		public:
			GINL Formula& operator = (const Formula& src)
			{
				name = src.name;
				formula = src.formula;
				index = src.index;
				return *this;
			}
			GAIA_CLASS_OPERATOR_COMPARE(name, name, Formula); 
		public:
			__StringType name;
			__StringType formula;
			GAIA::SIZE index;
		};
	public:
		typedef GAIA::CONTAINER::Vector<Formula> __FormulaListType;
		typedef GAIA::CONTAINER::Set<GAIA::CONTAINER::Ref<Formula> > __FormulaSetType;
		typedef GAIA::CONTAINER::Stack<GAIA::SIZE> __FreeStackType;
	private:
		__FormulaListType m_fmlist;
		__FormulaSetType m_fmset;
		__FreeStackType m_freestack;
		Formula m_finder;
	};
};

#endif
