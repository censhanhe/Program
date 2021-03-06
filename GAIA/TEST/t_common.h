#ifndef		__T_COMMON_H__
#define		__T_COMMON_H__

#define GTLINE(sz) do{stm << (sz) << "\n"; file.WriteText(sz); file.WriteText(GAIA_FILELINEBREAK);}while(0)
#define GTLINEI(sz) do{stm << "\t\t" << (sz) << "\n"; file.WriteText("\t\t"); file.WriteText(sz); file.WriteText(GAIA_FILELINEBREAK);}while(0)
#define GTLINE1(sz) do{if(!bOutputTime)\
							uTimeBegin = GAIA::TIME::tick_time();\
						else\
						{\
							uTimeEnd = GAIA::TIME::tick_time();\
							str.clear();\
							str += "Timelost ";\
							str += GSCAST(GAIA::F64)(uTimeEnd - uTimeBegin) / 1000.0;\
							str += "(MS)";\
							GTLINEI(str.front_ptr());\
						}\
						bOutputTime = !bOutputTime;\
						stm << "\t" << (sz) << "\n"; file.WriteText("\t"); file.WriteText(sz); file.WriteText(GAIA_FILELINEBREAK);\
					}while(0)
#define GTLINE2(sz) do{stm << "\t\t" << (sz) << " " << __FILE__ << "(" << __LINE__ << ")" << "\n";\
						GAIA::CTN::AString temp;\
						temp = (sz);\
						temp += " ";\
						temp += __FILE__;\
						temp += "(";\
						temp += __LINE__;\
						temp += ")";\
						file.WriteText("\t\t"); file.WriteText(temp.front_ptr()); file.WriteText(GAIA_FILELINEBREAK);\
					}while(0)

#endif
