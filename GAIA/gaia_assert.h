#ifndef		__GAIA_ASSERT_H__
#define		__GAIA_ASSERT_H__

namespace GAIA
{
	namespace DEBUG_MANAGEMENT
	{
		class AstException
		{
		public:
			AstException(const GAIA::GCH* pszFile, GAIA::N32 nLine){m_pszFile = pszFile; m_nLine = nLine;}
			const GAIA::GCH* m_pszFile;
			GAIA::N32 m_nLine;
		};

#ifdef GAIA_DEBUG_AST
#	define GAIA_AST(e)	do\
						{\
							if(!(e))\
							{\
								GAIA::PRINT::Print prt;\
								prt << "GAIA_AST Failed:\n\t" << __FILE__ << "(" << __LINE__ << ")\n\tInput 1 to break and other to ignore:";\
								GAIA::GCH ch;\
								prt >> ch;\
								if(ch == '1')\
									throw GAIA::DEBUG_MANAGEMENT::AstException(__FILE__, __LINE__);\
							}\
						}while(0)
#else
#	define GAIA_AST(e)
#endif

#ifdef GAIA_DEBUG_STATICAST
#	define GAIA_STATIC_AST(e) do{typedef class GAIA_STATIC_ASSERT_STRUCT GAIA_STATIC_ASSERT_FAILED[(e) ? 1 : -1];}while(GAIA::ALWAYSFALSE)
#endif
	};
};
#endif
