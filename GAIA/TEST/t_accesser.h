#ifndef		__T_ACCESSER_H__
#define		__T_ACCESSER_H__

namespace GAIATEST
{
	GINL GAIA::N32 t_accesser(GAIA::FILESYSTEM::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::N32 ACCESS_ELEMENT_COUNT = 1024;

		/* RAM based accesser test. */
		{
			/* Accesser pointer operator test. */
			{
				typedef GAIA::N16 __DataType;
				typedef GAIA::CONTAINER::Accesser<__DataType, GAIA::NM> __AccType;
				__AccType acc;
				__DataType arr[ACCESS_ELEMENT_COUNT];
				if(!acc.bind(arr, ACCESS_ELEMENT_COUNT, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE))
				{
					GTLINE2("RAM accesser bind a RAM failed!");
					++nRet;
				}
				if(!acc.offset(100))
				{
					GTLINE2("RAM accesser offset failed!");
					++nRet;
				}
				if(acc.offset() != 100)
				{
					GTLINE2("RAM accesser offset changed!");
					++nRet;
				}
				if(!acc.stride(sizeof(__DataType) + 1))
				{
					GTLINE2("RAM accesser stride failed!");
					++nRet;
				}
				if(acc.stride() != sizeof(__DataType) + 1)
				{
					GTLINE2("RAM accesser stride changed!");
					++nRet;
				}
				if(!acc.index(0))
				{
					GTLINE2("RAM accesser index failed!");
					++nRet;
				}
				if(acc.index() != 0)
				{
					GTLINE2("RAM accesser index changed!");
					++nRet;
				}
				__AccType::_datatype t = 0;
				while(!acc.empty())
				{
					*acc = t;
					++t;
					++acc;
				}
				if(t != (ACCESS_ELEMENT_COUNT - 100) / 3)
				{
					GTLINE2("RAM accesser _DataType write times error!");
					++nRet;
				}
				if(!acc.index(t / 2))
				{
					GTLINE2("RAM accesser reindex failed!");
					++nRet;
				}
				if(acc.index() != t / 2)
				{
					GTLINE2("RAM accesser reindex changed!");
					++nRet;
				}
				while(!acc.empty())
				{
					*acc = -*acc;
					++acc;
				}
				if(!acc.index(0))
				{
					GTLINE2("RAM accesser reindex2 failed!");
					++nRet;
				}
				if(acc.index() != 0)
				{
					GTLINE2("RAM accesser reindex2 changed!");
					++nRet;
				}
				__AccType::_datatype tt = 0;
				while(!acc.empty())
				{
					if(acc.index() >= t / 2)
					{
						if(*acc != -tt)
						{
							GTLINE2("RAM accesser write or read data failed!");
							++nRet;
							break;
						}
					}
					else
					{
						if(*acc != +tt)
						{
							GTLINE2("RAM accesser write or read data failed!");
							++nRet;
							break;
						}
					}
					++tt;
					++acc;
				}
				if(!!acc)
				{
					GTLINE2("RAM accesser operator ! failed!");
					++nRet;
				}
				if(acc.index() != t)
				{
					GTLINE2("RAM accesser last index error!");
					++nRet;
				}
				acc.index(0);
				__AccType acc1 = acc;
				acc1 += 50;
				if(acc1 - acc != 50)
				{
					GTLINE2("RAM accesser operator - failed!");
					++nRet;
				}
				acc1 -= 10;
				acc += 20;
				if(acc1 - acc != 20)
				{
					GTLINE2("RAM accesser operator -= or += or - failed!");
					++nRet;
				}
				if(!(acc1 > acc) ||
					acc1 < acc ||
					acc1 <= acc ||
					acc1 == acc ||
					!(acc1 >= acc) ||
					!(acc1 != acc))
				{
					GTLINE2("RAM accesser compare operator failed!");
					++nRet;
				}
				__AccType acc2 = acc + 20;
				if(acc2 != acc1)
				{
					GTLINE2("RAM accesser operator + failed!");
					++nRet;
				}
			}
		}

		/* File based accesser test. */
		{
			/* Accesser pointer operator test. */
			{
				typedef GAIA::N16 __DataType;
				typedef GAIA::CONTAINER::Accesser<__DataType, GAIA::NM> __AccType;
				__AccType acc;
				GAIA::FILESYSTEM::File accfile;
				if(!accfile.Open("../accesser_file",
					GAIA::FILESYSTEM::File::OPEN_TYPE_READ |
					GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE |
					GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS))
				{
					GTLINE2("Create accesser bind file failed!");
					++nRet;
				}
				accfile.Resize(ACCESS_ELEMENT_COUNT);
				if(!acc.bind(accfile, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE))
				{
					GTLINE2("File accesser bind a file failed!");
					++nRet;
				}
				if(!acc.offset(100))
				{
					GTLINE2("File accesser offset failed!");
					++nRet;
				}
				if(acc.offset() != 100)
				{
					GTLINE2("File accesser offset changed!");
					++nRet;
				}
				if(!acc.stride(sizeof(__DataType) + 1))
				{
					GTLINE2("File accesser stride failed!");
					++nRet;
				}
				if(acc.stride() != sizeof(__DataType) + 1)
				{
					GTLINE2("File accesser stride changed!");
					++nRet;
				}
				if(!acc.index(0))
				{
					GTLINE2("File accesser index failed!");
					++nRet;
				}
				if(acc.index() != 0)
				{
					GTLINE2("File accesser index changed!");
					++nRet;
				}
				__AccType::_datatype t = 0;
				while(!acc.empty())
				{
					*acc = t;
					++t;
					++acc;
				}
				if(t != (ACCESS_ELEMENT_COUNT - 100) / 3)
				{
					GTLINE2("File accesser _DataType write times error!");
					++nRet;
				}
				if(!acc.index(t / 2))
				{
					GTLINE2("File accesser reindex failed!");
					++nRet;
				}
				if(acc.index() != t / 2)
				{
					GTLINE2("File accesser reindex changed!");
					++nRet;
				}
				while(!acc.empty())
				{
					*acc = -*acc;
					++acc;
				}
				if(!acc.index(0))
				{
					GTLINE2("File accesser reindex2 failed!");
					++nRet;
				}
				if(acc.index() != 0)
				{
					GTLINE2("File accesser reindex2 changed!");
					++nRet;
				}
				__AccType::_datatype tt = 0;
				while(!acc.empty())
				{
					if(acc.index() >= t / 2)
					{
						if(*acc != -tt)
						{
							GTLINE2("File accesser write or read data failed!");
							++nRet;
							break;
						}
					}
					else
					{
						if(*acc != +tt)
						{
							GTLINE2("File accesser write or read data failed!");
							++nRet;
							break;
						}
					}
					++tt;
					++acc;
				}
				if(!!acc)
				{
					GTLINE2("File accesser operator ! failed!");
					++nRet;
				}
				if(acc.index() != t)
				{
					GTLINE2("File accesser last index error!");
					++nRet;
				}
				acc.index(0);
				__AccType acc1 = acc;
				acc1 += 50;
				if(acc1 - acc != 50)
				{
					GTLINE2("File accesser operator - failed!");
					++nRet;
				}
				acc1 -= 10;
				acc += 20;
				if(acc1 - acc != 20)
				{
					GTLINE2("File accesser operator -= or += or - failed!");
					++nRet;
				}
				if(!(acc1 > acc) ||
					acc1 < acc ||
					acc1 <= acc ||
					acc1 == acc ||
					!(acc1 >= acc) ||
					!(acc1 != acc))
				{
					GTLINE2("File accesser compare operator failed!");
					++nRet;
				}
				__AccType acc2 = acc + 20;
				if(acc2 != acc1)
				{
					GTLINE2("File accesser operator + failed!");
					++nRet;
				}
			}
		}

		return nRet;
	}
};

#endif
