#ifndef		__T_CONTAINER_ACCESSER_H__
#define		__T_CONTAINER_ACCESSER_H__

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
				typedef GAIA::CTN::Accesser<__DataType, GAIA::NM, GAIA::ALGO::TwiceSizeIncreaser<GAIA::NM> > __AccType;
				__AccType acc;
				__DataType arr[ACCESS_ELEMENT_COUNT];
				if(!acc.bindmem(arr, ACCESS_ELEMENT_COUNT, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE))
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

			/* Make accesser work as a string pointer. */
			{
				GAIA::TCH szTemp[1024];
				typedef GAIA::CTN::Accesser<GAIA::TCH, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindmem(szTemp, 1024, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				GAIA::ALGO::strcpy(acc, "HelloWorld");
				if(GAIA::ALGO::strcmp(acc, "HelloWorld") != 0)
				{
					GTLINE2("RAM accesser can't used as a string pointer!");
					++nRet;
				}
			}

			/* Expandable accesser test. */
			{
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.expandable(GAIA::True);
				acc.bindmem(GNIL, 0, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				for(GAIA::SIZE x = 0; x < 100; ++x)
					acc[x] = x;
				for(GAIA::SIZE x = 0; x < 100; ++x)
				{
					if(acc[x] != x)
					{
						GTLINE2("RAM accesser bind NULL test failed!");
						++nRet;
						break;
					}
				}
				GAIA_MFREE(acc.bindmem());
				acc.destroy();
			}
		}

		/* File based accesser test. */
		{
			/* Accesser pointer operator test. */
			{
				typedef GAIA::N16 __DataType;
				typedef GAIA::CTN::Accesser<__DataType, GAIA::NM, GAIA::ALGO::TwiceSizeIncreaser<GAIA::NM> > __AccType;
				__AccType acc;
				GAIA::FILESYSTEM::File accfile;
				if(!accfile.Open(_T("../TESTRES/accesser_file"),
					GAIA::FILESYSTEM::File::OPEN_TYPE_READ |
					GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE |
					GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS))
				{
					GTLINE2("Create accesser bind file failed!");
					++nRet;
				}
				accfile.Resize(ACCESS_ELEMENT_COUNT);
				if(!acc.bindfile(&accfile, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE))
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

			/* Make accesser work as a string pointer. */
			{
				GAIA::FILESYSTEM::File accfile;
				if(!accfile.Open(_T("../accesser_file"),
					GAIA::FILESYSTEM::File::OPEN_TYPE_READ |
					GAIA::FILESYSTEM::File::OPEN_TYPE_WRITE |
					GAIA::FILESYSTEM::File::OPEN_TYPE_CREATEALWAYS))
				{
					GTLINE2("Create accesser bind file failed!");
					++nRet;
				}
				accfile.Resize(ACCESS_ELEMENT_COUNT);
				typedef GAIA::CTN::Accesser<GAIA::TCH, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindfile(&accfile, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				GAIA::ALGO::strcpy(acc, "HelloWorld");
				if(GAIA::ALGO::strcmp(acc, "HelloWorld") != 0)
				{
					GTLINE2("File accesser can't used as a string pointer!");
					++nRet;
				}
			}

			/* Expandable accesser test. */
			{
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.expandable(GAIA::True);
				acc.bindfile(GNIL, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				for(GAIA::SIZE x = 0; x < 100; ++x)
					acc[x] = x;
				for(GAIA::SIZE x = 0; x < 100; ++x)
				{
					if(acc[x] != x)
					{
						GTLINE2("File accesser bind NULL test failed!");
						++nRet;
						break;
					}
				}
				delete acc.bindfile();
			}
		}

		return nRet;
	}
};

#endif
