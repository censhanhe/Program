#ifndef		__GAIA_CONTAINER_VARI_H__
#define		__GAIA_CONTAINER_VARI_H__

namespace GAIA
{
	namespace CTN
	{
		class Vari : public GAIA::Entity
		{
		public:
			GINL Vari(){}
			GINL ~Vari(){}
			GINL GAIA::GVOID invalid(){m_type = GAIA::TYPEID_INVALID;}
			GINL GAIA::BL isinvalid(){return m_type == GAIA::TYPEID_INVALID;}
			GINL Vari& operator = (const Vari& src)
			{
				m_type = src.m_type;
				switch(m_type)
				{
				case GAIA::TYPEID_INVALID:
					break;
				case GAIA::TYPEID_NM:
					m_nm = src.m_nm;
					break;
				case GAIA::TYPEID_UM:
					m_um = src.m_um;
					break;
				case GAIA::TYPEID_BL:
					m_b = src.m_b;
					break;
				case GAIA::TYPEID_N8:
					m_n8 = src.m_n8;
					break;
				case GAIA::TYPEID_N16:
					m_n16 = src.m_n16;
					break;
				case GAIA::TYPEID_N32:
					m_n32 = src.m_n32;
					break;
				case GAIA::TYPEID_N64:
					m_n64 = src.m_n64;
					break;
				case GAIA::TYPEID_U8:
					m_u8 = src.m_u8;
					break;
				case GAIA::TYPEID_U16:
					m_u16 = src.m_u16;
					break;
				case GAIA::TYPEID_U32:
					m_u32 = src.m_u32;
					break;
				case GAIA::TYPEID_U64:
					m_u64 = src.m_u64;
					break;
				case GAIA::TYPEID_F32:
					m_f32 = src.m_f32;
					break;
				case GAIA::TYPEID_F64:
					m_f64 = src.m_f64;
					break;
				case GAIA::TYPEID_POINTER:
					m_p = src.m_p;
					break;
				case GAIA::TYPEID_CONSTPOINTER:
					m_cp = src.m_cp;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
				return *this;
			}
			GINL Vari& operator = (const GAIA::NM& src){m_type = GAIA::TYPEID_NM; m_nm = src; return *this;}
			GINL Vari& operator = (const GAIA::UM& src){m_type = GAIA::TYPEID_UM; m_um = src; return *this;}
			GINL Vari& operator = (GAIA::BL src){m_type = GAIA::TYPEID_BL; m_b = src; return *this;}
			GINL Vari& operator = (GAIA::N8 src){m_type = GAIA::TYPEID_N8; m_n8 = src; return *this;}
			GINL Vari& operator = (GAIA::N16 src){m_type = GAIA::TYPEID_N16; m_n16 = src; return *this;}
			GINL Vari& operator = (GAIA::N32 src){m_type = GAIA::TYPEID_N32; m_n32 = src; return *this;}
			GINL Vari& operator = (const GAIA::N64& src){m_type = GAIA::TYPEID_N64; m_n64 = src; return *this;}
			GINL Vari& operator = (GAIA::U8 src){m_type = GAIA::TYPEID_U8; m_u8 = src; return *this;}
			GINL Vari& operator = (GAIA::U16 src){m_type = GAIA::TYPEID_U16; m_u16 = src; return *this;}
			GINL Vari& operator = (GAIA::U32 src){m_type = GAIA::TYPEID_U32; m_u32 = src; return *this;}
			GINL Vari& operator = (const GAIA::U64& src){m_type = GAIA::TYPEID_U64; m_u64 = src; return *this;}
			GINL Vari& operator = (GAIA::F32 src){m_type = GAIA::TYPEID_F32; m_f32 = src; return *this;}
			GINL Vari& operator = (const GAIA::F64& src){m_type = GAIA::TYPEID_F64; m_f64 = src; return *this;}
			GINL Vari& operator = (GAIA::GVOID* src){m_type = GAIA::TYPEID_POINTER; m_p = src; return *this;}
			GINL Vari& operator = (const GAIA::GVOID* src){m_type = GAIA::TYPEID_CONSTPOINTER; m_cp = src; return *this;}
			GINL operator const GAIA::NM(){GAIA_AST(m_type == GAIA::TYPEID_NM); return m_nm;}
			GINL operator const GAIA::UM(){GAIA_AST(m_type == GAIA::TYPEID_UM); return m_um;}
			GINL operator GAIA::BL(){GAIA_AST(m_type == GAIA::TYPEID_BL); return m_b;}
			GINL operator GAIA::N8(){GAIA_AST(m_type == GAIA::TYPEID_N8); return m_n8;}
			GINL operator GAIA::N16(){GAIA_AST(m_type == GAIA::TYPEID_N16); return m_n16;}
			GINL operator GAIA::N32(){GAIA_AST(m_type == GAIA::TYPEID_N32); return m_n32;}
			GINL operator GAIA::N64(){GAIA_AST(m_type == GAIA::TYPEID_N64); return m_n64;}
			GINL operator GAIA::U8(){GAIA_AST(m_type == GAIA::TYPEID_U8); return m_u8;}
			GINL operator GAIA::U16(){GAIA_AST(m_type == GAIA::TYPEID_U16); return m_u16;}
			GINL operator GAIA::U32(){GAIA_AST(m_type == GAIA::TYPEID_U32); return m_u32;}
			GINL operator GAIA::U64(){GAIA_AST(m_type == GAIA::TYPEID_U64); return m_u64;}
			GINL operator GAIA::F32(){GAIA_AST(m_type == GAIA::TYPEID_F32); return m_f32;}
			GINL operator GAIA::F64(){GAIA_AST(m_type == GAIA::TYPEID_F64); return m_f64;}
			GINL operator GAIA::GVOID*(){GAIA_AST(m_type == GAIA::TYPEID_POINTER); return m_p;}
			GINL operator const GAIA::GVOID*(){GAIA_AST(m_type == GAIA::TYPEID_CONSTPOINTER); return m_cp;}
			GINL GAIA::BL operator == (const Vari& src) const
			{
				if(m_type != src.m_type)
					return GAIA::False;
				switch(m_type)
				{
				case GAIA::TYPEID_INVALID:
					return GAIA::True;
				case GAIA::TYPEID_NM:
					return m_nm == src.m_nm;
				case GAIA::TYPEID_UM:
					return m_um == src.m_um;
				case GAIA::TYPEID_BL:
					return m_b == src.m_b;
				case GAIA::TYPEID_N8:
					return m_n8 == src.m_n8;
				case GAIA::TYPEID_N16:
					return m_n16 == src.m_n16;
				case GAIA::TYPEID_N32:
					return m_n32 == src.m_n32;
				case GAIA::TYPEID_N64:
					return m_n64 == src.m_n64;
				case GAIA::TYPEID_U8:
					return m_u8 == src.m_u8;
				case GAIA::TYPEID_U16:
					return m_u16 == src.m_u16;
				case GAIA::TYPEID_U32:
					return m_u32 == src.m_u32;
				case GAIA::TYPEID_U64:
					return m_u64 == src.m_u64;
				case GAIA::TYPEID_F32:
					return m_f32 == src.m_f32;
				case GAIA::TYPEID_F64:
					return m_f64 == src.m_f64;
				case GAIA::TYPEID_POINTER:
					return m_p == src.m_p;
				case GAIA::TYPEID_CONSTPOINTER:
					return m_cp == src.m_cp;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			GINL GAIA::BL operator != (const Vari& src) const{return !this->operator == (src);}
			GINL GAIA::BL operator >= (const Vari& src) const
			{
				if(m_type < src.m_type)
					return GAIA::False;
				switch(m_type)
				{
				case GAIA::TYPEID_INVALID:
					return GAIA::True;
				case GAIA::TYPEID_NM:
					return m_nm >= src.m_nm;
				case GAIA::TYPEID_UM:
					return m_um >= src.m_um;
				case GAIA::TYPEID_BL:
					return m_b >= src.m_b;
				case GAIA::TYPEID_N8:
					return m_n8 >= src.m_n8;
				case GAIA::TYPEID_N16:
					return m_n16 >= src.m_n16;
				case GAIA::TYPEID_N32:
					return m_n32 >= src.m_n32;
				case GAIA::TYPEID_N64:
					return m_n64 >= src.m_n64;
				case GAIA::TYPEID_U8:
					return m_u8 >= src.m_u8;
				case GAIA::TYPEID_U16:
					return m_u16 >= src.m_u16;
				case GAIA::TYPEID_U32:
					return m_u32 >= src.m_u32;
				case GAIA::TYPEID_U64:
					return m_u64 >= src.m_u64;
				case GAIA::TYPEID_F32:
					return m_f32 >= src.m_f32;
				case GAIA::TYPEID_F64:
					return m_f64 >= src.m_f64;
				case GAIA::TYPEID_POINTER:
					return m_p >= src.m_p;
				case GAIA::TYPEID_CONSTPOINTER:
					return m_cp >= src.m_cp;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			GINL GAIA::BL operator <= (const Vari& src) const
			{
				if(m_type > src.m_type)
					return GAIA::False;
				switch(m_type)
				{
				case GAIA::TYPEID_INVALID:
					return GAIA::True;
				case GAIA::TYPEID_NM:
					return m_nm <= src.m_nm;
				case GAIA::TYPEID_UM:
					return m_um <= src.m_um;
				case GAIA::TYPEID_BL:
					return m_b <= src.m_b;
				case GAIA::TYPEID_N8:
					return m_n8 <= src.m_n8;
				case GAIA::TYPEID_N16:
					return m_n16 <= src.m_n16;
				case GAIA::TYPEID_N32:
					return m_n32 <= src.m_n32;
				case GAIA::TYPEID_N64:
					return m_n64 <= src.m_n64;
				case GAIA::TYPEID_U8:
					return m_u8 <= src.m_u8;
				case GAIA::TYPEID_U16:
					return m_u16 <= src.m_u16;
				case GAIA::TYPEID_U32:
					return m_u32 <= src.m_u32;
				case GAIA::TYPEID_U64:
					return m_u64 <= src.m_u64;
				case GAIA::TYPEID_F32:
					return m_f32 <= src.m_f32;
				case GAIA::TYPEID_F64:
					return m_f64 <= src.m_f64;
				case GAIA::TYPEID_POINTER:
					return m_p <= src.m_p;
				case GAIA::TYPEID_CONSTPOINTER:
					return m_cp <= src.m_cp;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			GINL GAIA::BL operator > (const Vari& src) const{return !this->operator <= (src);}
			GINL GAIA::BL operator < (const Vari& src) const{return !this->operator >= (src);}
		private:
			union
			{
				GAIA::NM m_nm;
				GAIA::UM m_um;
				GAIA::BL m_b;
				GAIA::N8 m_n8;
				GAIA::N16 m_n16;
				GAIA::N32 m_n32;
				GAIA::N64 m_n64;
				GAIA::U8 m_u8;
				GAIA::U16 m_u16;
				GAIA::U32 m_u32;
				GAIA::U64 m_u64;
				GAIA::F32 m_f32;
				GAIA::F64 m_f64;
				GAIA::GVOID* m_p;
				const GAIA::GVOID* m_cp;
			};
			GAIA::TYPEID m_type;
		};
	};
};

#endif
