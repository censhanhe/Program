#ifndef		__GAIA_ASSERT_H__
#define		__GAIA_ASSERT_H__

namespace GAIA
{
	namespace DEBUG
	{
#ifdef GAIA_DEBUG_AST
#	define GAIA_AST(e)	do\
						{\
							if(!(e))\
							{\
								GAIA::STREAM::STDStream stm;\
								stm << "GAIA_AST Failed:\n\t" << __FILE__ << "(" << __LINE__ << ")\n\tInput 1 to break and other to continue:";\
								GAIA::CH ch[32];\
								stm >> ch;\
								if(ch[0] == '1' && ch[1] == '\0')\
									throw GAIA::EXCEPTION::ExceptionAst(__FILE__, __LINE__);\
							}\
						}while(0)
#else
#	define GAIA_AST(e)
#endif

#ifdef GAIA_DEBUG_ASTDEBUG
#	define GAIA_ASTDEBUG(e)		do\
								{\
									if(!(e))\
									{\
										GAIA::STREAM::STDStream stm;\
										stm << "GAIA_AST Failed:\n\t" << __FILE__ << "(" << __LINE__ << ")\n\tInput 1 to break and other to continue(Debug):";\
										GAIA::CH ch;\
										stm >> ch;\
										if(ch == '1')\
											throw GAIA::EXCEPTION::ExceptionAstDebug(__FILE__, __LINE__);\
									}\
								}while(0)
#else
#	define GAIA_ASTDEBUG(e)
#endif

#ifdef GAIA_DEBUG_STATICAST
#	define GAIA_STATIC_AST(e) do{typedef class GAIA_STATIC_ASSERT_STRUCT GAIA_STATIC_ASSERT_FAILED[(e) ? 1 : -1];}while(GAIA::ALWAYSFALSE)
#endif
	};
};
#endif
