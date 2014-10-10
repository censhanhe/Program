#ifndef		__T_CONTAINER_ACCESSER_H__
#define		__T_CONTAINER_ACCESSER_H__

namespace GAIA_TEST
{
	GINL GAIA::N32 t_container_accesser(GAIA::FSYS::File& file, GAIA::PRINT::PrintBase& prt)
	{
		GAIA::N32 nRet = 0;

		static const GAIA::N32 ACCESS_ELEMENT_COUNT = 100;

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
				GAIA::TCH szTemp[ACCESS_ELEMENT_COUNT];
				typedef GAIA::CTN::Accesser<GAIA::TCH, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindmem(szTemp, ACCESS_ELEMENT_COUNT, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
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

			/* Expandable accesser bubble sort test. */
			//{
			//	typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
			//	__AccType acc;
			//	acc.expandable(GAIA::True);
			//	acc.bindmem(GNIL, 0, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
			//	for(GAIA::SIZE x = 0; x < 100; ++x)
			//		acc[x] = GAIA::MATH::xrandom();
			//	GAIA::ALGO::bsort(acc, acc + 99);
			//	if(!GAIA::ALGO::issorted(acc, acc + 99))
			//	{
			//		GTLINE2("File accesser bubble sort test failed!");
			//		++nRet;
			//	}
			//	GAIA_MFREE(acc.bindmem());
			//	acc.destroy();
			//}

			/* Accesser write read test. */
			{
				GAIA::SIZE szTemp[ACCESS_ELEMENT_COUNT];
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindmem(szTemp, ACCESS_ELEMENT_COUNT * sizeof(GAIA::SIZE), __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT / sizeof(GAIA::SIZE); ++x)
				{
					if(acc.write(&x, sizeof(x)) != sizeof(x))
					{
						GTLINE2("Accesser write element failed!");
						++nRet;
					}
				}
				acc.index(0);
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT / sizeof(GAIA::SIZE); ++x)
				{
					GAIA::SIZE e;
					if(acc.read(&e, sizeof(e)) != sizeof(e))
					{
						GTLINE2("Accesser read element failed!");
						++nRet;
						break;
					}
					if(e != x)
					{
						GTLINE2("Accesser read element failed!");
						++nRet;
						break;
					}
				}
			}


			/* Accesser write read ovewflow test. */
			{
				GAIA::SIZE szTemp[ACCESS_ELEMENT_COUNT];
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindmem(szTemp, ACCESS_ELEMENT_COUNT * sizeof(GAIA::SIZE), __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				GAIA::CTN::Vector<GAIA::SIZE> listEle;
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT * 2; ++x)
					listEle.push_back(x);
				if(acc.write(listEle.front_ptr(), listEle.size() * sizeof(GAIA::SIZE)) != ACCESS_ELEMENT_COUNT * sizeof(GAIA::SIZE))
				{
					GTLINE2("Accesser write overflow test failed!");
					++nRet;
				}
				acc.index(0);
				listEle.inverse();
				if(acc.read(listEle.front_ptr(), listEle.size() * sizeof(GAIA::SIZE)) != ACCESS_ELEMENT_COUNT * sizeof(GAIA::SIZE))
				{
					GTLINE2("Accesser read overflow test failed!");
					++nRet;
				}
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT / sizeof(GAIA::SIZE); ++x)
				{
					if(listEle[x] != x)
					{
						GTLINE2("Access read overflow content error!");
						++nRet;
						break;
					}
				}
			}

			/* Expandable accesser read write test. */
			{
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindmem(GNIL, 0, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT; ++x)
				{
					if(acc.write(&x, sizeof(x)) != sizeof(x))
					{
						GTLINE2("Accesser write failed!");
						++nRet;
						break;
					}
				}
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT / 10; ++x)
				{
					acc.index(x * 10 + 9);
					GAIA::SIZE t = GINVALID;
					if(acc.write(&t, sizeof(t)) != sizeof(t))
					{
						GTLINE2("Accesser write failed!");
						++nRet;
						break;
					}
				}
				acc.index(0);
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT; ++x)
				{
					GAIA::SIZE t;
					if(acc.read(&t, sizeof(t)) != sizeof(t))
					{
						GTLINE2("Accesser read failed!");
						++nRet;
						break;
					}
					if((x + 1) % 10 == 0)
					{
						if(t != GINVALID)
						{
							GTLINE2("Accesser read content error!");
							++nRet;
							break;
						}
					}
					else
					{
						if(t != x)
						{
							GTLINE2("Accesser read content error!");
							++nRet;
							break;
						}
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
				GAIA::FSYS::File accfile;
				if(!accfile.Open(_T("../TESTRES/accesser_file"),
					GAIA::FSYS::File::OPEN_TYPE_READ |
					GAIA::FSYS::File::OPEN_TYPE_WRITE |
					GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
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
				GAIA::FSYS::File accfile;
				if(!accfile.Open(_T("../TESTRES/accesser_file"),
					GAIA::FSYS::File::OPEN_TYPE_READ |
					GAIA::FSYS::File::OPEN_TYPE_WRITE |
					GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
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
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT; ++x)
					acc[x] = x;
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT; ++x)
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

			/* Expandable accesser bubble sort test. */
			//{
			//	typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
			//	__AccType acc;
			//	acc.expandable(GAIA::True);
			//	acc.bindfile(GNIL, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
			//	for(GAIA::SIZE x = 0; x < 100; ++x)
			//		acc[x] = GAIA::MATH::xrandom();
			//	GAIA::ALGO::bsort(acc, acc + 99);
			//	if(!GAIA::ALGO::issorted(acc, acc + 99))
			//	{
			//		GTLINE2("File accesser bubble sort test failed!");
			//		++nRet;
			//	}
			//	delete acc.bindfile();
			//}

			/* Accesser write test. */
			{
				GAIA::FSYS::File accfile;
				if(!accfile.Open(_T("../TESTRES/accesser_file"),
					GAIA::FSYS::File::OPEN_TYPE_READ |
					GAIA::FSYS::File::OPEN_TYPE_WRITE |
					GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
				{
					GTLINE2("Create accesser bind file failed!");
					++nRet;
				}
				accfile.Resize(ACCESS_ELEMENT_COUNT);
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindfile(&accfile, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT / sizeof(GAIA::SIZE); ++x)
				{
					if(acc.write(&x, sizeof(x)) != sizeof(x))
					{
						GTLINE2("Accesser write element failed!");
						++nRet;
					}
				}
			}

			/* Accesser read test. */
			{
				GAIA::FSYS::File accfile;
				if(!accfile.Open(_T("../TESTRES/accesser_file"),
					GAIA::FSYS::File::OPEN_TYPE_READ))
				{
					GTLINE2("Create accesser bind file failed!");
					++nRet;
				}
				accfile.Resize(ACCESS_ELEMENT_COUNT);
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindfile(&accfile, __AccType::ACCESS_TYPE_READ);
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT / sizeof(GAIA::SIZE); ++x)
				{
					GAIA::SIZE e;
					if(acc.read(&e, sizeof(e)) != sizeof(e))
					{
						GTLINE2("Accesser read element failed!");
						++nRet;
						break;
					}
					if(e != x)
					{
						GTLINE2("Accesser read element failed!");
						++nRet;
						break;
					}
				}
			}

			/* Accesser write ovewflow test. */
			{
				GAIA::FSYS::File accfile;
				if(!accfile.Open(_T("../TESTRES/accesser_file"),
					GAIA::FSYS::File::OPEN_TYPE_READ |
					GAIA::FSYS::File::OPEN_TYPE_WRITE |
					GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS))
				{
					GTLINE2("Create accesser bind file failed!");
					++nRet;
				}
				accfile.Resize(ACCESS_ELEMENT_COUNT);
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindfile(&accfile, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				GAIA::CTN::Vector<GAIA::SIZE> listEle;
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT * 2; ++x)
					listEle.push_back(x);
				if(acc.write(listEle.front_ptr(), listEle.size() * sizeof(GAIA::SIZE)) != ACCESS_ELEMENT_COUNT)
				{
					GTLINE2("Accesser write overflow test failed!");
					++nRet;
				}
			}

			/* Accesser read overflow test. */
			{
				GAIA::FSYS::File accfile;
				if(!accfile.Open(_T("../TESTRES/accesser_file"),
					GAIA::FSYS::File::OPEN_TYPE_READ))
				{
					GTLINE2("Create accesser bind file failed!");
					++nRet;
				}
				accfile.Resize(ACCESS_ELEMENT_COUNT);
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindfile(&accfile, __AccType::ACCESS_TYPE_READ);
				GAIA::CTN::Vector<GAIA::SIZE> listEle;
				listEle.resize(ACCESS_ELEMENT_COUNT / sizeof(GAIA::SIZE) * 2);
				if(acc.read(listEle.front_ptr(), listEle.size() * sizeof(GAIA::SIZE)) != ACCESS_ELEMENT_COUNT)
				{
					GTLINE2("Accesser read overflow test failed!");
					++nRet;
				}
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT / sizeof(GAIA::SIZE); ++x)
				{
					if(listEle[x] != x)
					{
						GTLINE2("Access read overflow content error!");
						++nRet;
						break;
					}
				}
			}

			/* Expandable accesser read write test. */
			{
				typedef GAIA::CTN::Accesser<GAIA::SIZE, GAIA::SIZE, GAIA::ALGO::TwiceSizeIncreaser<GAIA::SIZE> > __AccType;
				__AccType acc;
				acc.bindfile(GNIL, __AccType::ACCESS_TYPE_READ | __AccType::ACCESS_TYPE_WRITE);
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT; ++x)
				{
					if(acc.write(&x, sizeof(x)) != sizeof(x))
					{
						GTLINE2("Accesser write failed!");
						++nRet;
						break;
					}
				}
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT / 10; ++x)
				{
					acc.index(x * 10 + 9);
					GAIA::SIZE t = GINVALID;
					if(acc.write(&t, sizeof(t)) != sizeof(t))
					{
						GTLINE2("Accesser write failed!");
						++nRet;
						break;
					}
				}
				acc.index(0);
				for(GAIA::SIZE x = 0; x < ACCESS_ELEMENT_COUNT; ++x)
				{
					GAIA::SIZE t;
					if(acc.read(&t, sizeof(t)) != sizeof(t))
					{
						GTLINE2("Accesser read failed!");
						++nRet;
						break;
					}
					if((x + 1) % 10 == 0)
					{
						if(t != GINVALID)
						{
							GTLINE2("Accesser read content error!");
							++nRet;
							break;
						}
					}
					else
					{
						if(t != x)
						{
							GTLINE2("Accesser read content error!");
							++nRet;
							break;
						}
					}
				}
				delete acc.bindfile();
			}
		}

		return nRet;
	}
};

#endif
