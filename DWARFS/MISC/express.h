#ifndef		__DWARFS_MISC_EXPRESS_H__
#define		__DWARFS_MISC_EXPRESS_H__

namespace DWARFS_MISC
{
	template<typename _StringType> class Express : public GAIA::Entity
	{
	public:
		typedef _StringType _stringtype;
		typedef Express<_StringType> __MyType;
	public:
		GINL Express(){}
		GINL ~Express(){}
		GINL GAIA::BL set_formula(const _StringType* pszName, const _StringType* pszFormula);
		GINL const _StringType* set_formula(const _StringType* pszName) const;
		GINL GAIA::SIZE get_formula_count() const;
		GINL const _StringType* get_formula(const GAIA::SIZE& index) const;
		GINL GAIA::BL delete_formula(const GAIA::SIZE& index);
		GINL GAIA::BL delete_formula_all();
		GINL GAIA::SIZE get_formula_by_name(const _StringType* pszName) const;
		GINL GAIA::BL calculate(const _StringType* pszName, __StringType* pResult, GAIA::SIZE& uResuleSize);

	private:
	};
};

#endif