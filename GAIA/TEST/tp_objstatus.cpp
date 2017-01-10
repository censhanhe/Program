#include "preheader.h"
#include "t_header.h"

namespace GAIA_TEST
{
	extern GAIA::N32 tp_objstatus(GAIA::FSYS::File& file, GAIA::STREAM::StreamBase& stm)
	{
		GAIA::N32 nRet = 0;

		GAIA::STREAM::StringStream s;

		s << "[BASE OBJECT SIZE]\r\n";
		s << "GAIA::Base size = " << sizeof(GAIA::Base) << "\r\n";
		s << "GAIA::Entity size = " << sizeof(GAIA::Entity) << "\r\n";
		s << "GAIA::Object size = " << sizeof(GAIA::Object) << "\r\n";
		s << "GAIA::RefObject size = " << sizeof(GAIA::RefObject) << "\r\n";
		s << "GAIA::FWORK::Instance size = " << sizeof(GAIA::FWORK::Instance) << "\r\n";

		s << "\r\n[CONTAINER SIZE]\r\n";
		s << "GAIA::CTN::Array<GAIA::CH, 1> size = " << sizeof(GAIA::CTN::Array<GAIA::CH, 1>) << "\r\n";
		s << "GAIA::CTN::Vector<GAIA::CH> size = " << sizeof(GAIA::CTN::Vector<GAIA::CH>) << "\r\n";
		s << "GAIA::CTN::TString size = " << sizeof(GAIA::CTN::TString) << "\r\n";

		s << "\r\n[MATH SIZE]\r\n";
		s << "GAIA::MATH::VEC2<GAIA::F32> size = " << sizeof(GAIA::MATH::VEC2<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::VEC3<GAIA::F32> size = " << sizeof(GAIA::MATH::VEC3<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::VEC4<GAIA::F32> size = " << sizeof(GAIA::MATH::VEC4<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::ARGB<GAIA::F32> size = " << sizeof(GAIA::MATH::ARGB<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::NRGB<GAIA::F32> size = " << sizeof(GAIA::MATH::NRGB<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::AABR<GAIA::F32> size = " << sizeof(GAIA::MATH::AABR<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::AABB<GAIA::F32> size = " << sizeof(GAIA::MATH::AABB<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::MTX44<GAIA::F32> size = " << sizeof(GAIA::MATH::MTX44<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::MTX43<GAIA::F32> size = " << sizeof(GAIA::MATH::MTX43<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::MTX33<GAIA::F32> size = " << sizeof(GAIA::MATH::MTX33<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::MTX32<GAIA::F32> size = " << sizeof(GAIA::MATH::MTX32<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::MTX22<GAIA::F32> size = " << sizeof(GAIA::MATH::MTX22<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::QUA<GAIA::F32> size = " << sizeof(GAIA::MATH::QUA<GAIA::F32>) << "\r\n";
		s << "GAIA::MATH::PLANE<GAIA::F32> size = " << sizeof(GAIA::MATH::PLANE<GAIA::F32>) << "\r\n";

		GAIA::FSYS::File f;
		static const GAIA::TCH* FILENAME = _T("../TESTRES/objstatus.txt");
		if(!f.Open(FILENAME, GAIA::FSYS::File::OPEN_TYPE_CREATEALWAYS | GAIA::FSYS::File::OPEN_TYPE_WRITE))
		{
			GTLINE2("Compiler : open file failed!\n");
			++nRet;
			return nRet;
		}
		f.WriteText(s.GetString());
		f.Close();

		return nRet;
	}
};