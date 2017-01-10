#ifndef		__GAIA_UI_MESSAGE_H__
#define		__GAIA_UI_MESSAGE_H__

namespace GAIA
{
	namespace UI
	{
		class Message : public GAIA::Base
		{
		public:
			GAIA_ENUM_BEGIN(TYPE)
				/* Canvas message. */
				TYPE_CREATE, // No parameter.
				TYPE_DESTROY, // No parameter.
				TYPE_SHOW, // No parameter.
				TYPE_HIDE, // No parameter.
				TYPE_MOVE, // Param0 is the new position(const GAIA::UI::Canvas::__PosType*). When the message sent, the canvas position is not changed.
				TYPE_MOVED, // Param0 is the new position(const GAIA::UI::Canvas::__PosType*). When the message sent, the canvas position is changed.
				TYPE_RESIZE, // Param0 is the new size(const GAIA::UI::Canvas::__SizeType*). When the message sent, the canvas size is not changed.
				TYPE_RESIZED, // Param0 is the new size(const GAIA::UI::Canvas::__SizeType*). When the message sent, the canvas size is changed.
				TYPE_ACTIVE, // No parameter.
				TYPE_INACTIVE, // No parameter.
				/* Cursor message. */
				TYPE_CURSORDOWN, // Param0 is the cursor position in canvas coordinate(const GAIA::UI::Canvas::__PosType*). Param1 is the key id(GAIA::INPUT::KEY).
				TYPE_CURSORUP, // Param0 is the cursor position in canvas coordinate(const GAIA::UI::Canvas::__PosType*). Param1 is the key id(GAIA::INPUT::KEY).
				TYPE_CURSORMOVE, // Param0 is the new cursor position in canvas coordinate(const GAIA::UI::Canvas::__PosType*). When the message sent, the cursor's position is not changed.
				TYPE_CURSORMOVEIN, // Param0 is the cursor position in canvas coordinate(const GAIA::UI::Canvas::__PosType*).
				TYPE_CURSORMOVEOUT, // Param0 is the cursor position in canvas coordinate(const GAIA::UI::Canvas::__PosType*).
				/* Keyboard message. */
				TYPE_KEYDOWN, // Param0 is the key's ansi character(GAIA::N32)(if is 0 means a pure virtual key), Param1 is the key id(GAIA::INPUT::KEY).
				TYPE_KEYUP, // Param0 is the key's ansi character(GAIA::N32)(if is 0 means a pure virtual key), Param1 is the key id(GAIA::INPUT::KEY).
				/* Character message. */
				TYPE_CHAR, // Param 0 is the key's ansi character.
			GAIA_ENUM_END(TYPE)
		public:
			GINL GAIA::GVOID reset()
			{
				m_type = TYPE_INVALID;
				for(GAIA::SIZE x = 0; x < sizeofarray(m_v); ++x)
					m_v[x].reset();
			}
			GINL GAIA::BL check()
			{
				if(m_type == TYPE_INVALID)
					return GAIA::False;
				return GAIA::True;
			}
			GINL GAIA::GVOID SetMsgType(GAIA::UI::Message::TYPE type){m_type = type;}
			GINL GAIA::UI::Message::TYPE GetMsgType() const{return m_type;}
			GINL GAIA::GVOID SetParam(const GAIA::SIZE& index, const GAIA::CTN::Vari& v){GAIA_AST(index < sizeofarray(m_v)); m_v[index] = v;}
			GINL const GAIA::CTN::Vari& GetParam(const GAIA::SIZE& index) const{GAIA_AST(index < sizeofarray(m_v)); return m_v[index];}
		private:
			GAIA::CTN::Vari m_v[2];
			TYPE m_type;
		};
	};
};

#endif