#ifndef		__GAIA_INPUT_INPUTSTATE_H__
#define		__GAIA_INPUT_INPUTSTATE_H__

namespace GAIA
{
	namespace INPUT
	{
		GAIA_ENUM_BEGIN(KEY)
			/* Cursor key. */
			KEY_LBTN,
			KEY_RBTN,
			KEY_MBTN,
			/* Function key. */
			KEY_CTRL,
			KEY_ALT,
			KEY_SHIFT,
			KEY_ESC,
			/* Format input key. */
			KEY_SPACE,
			KEY_TAB,
			KEY_ENTER,
			KEY_BACKSPACE,
			KEY_DELETE,
			/* Move key. */
			KEY_LEFT,
			KEY_RIGHT,
			KEY_UP,
			KEY_DOWN,
			KEY_HOME,
			KEY_END,
			KEY_PAGEUP,
			KEY_PAGEDOWN,
			/* Function key. */
			KEY_F1,
			KEY_F2,
			KEY_F3,
			KEY_F4,
			KEY_F5,
			KEY_F6,
			KEY_F7,
			KEY_F8,
			KEY_F9,
			KEY_F10,
			KEY_F11,
			KEY_F12,
			/* Number key. */
			KEY_0,
			KEY_1,
			KEY_2,
			KEY_3,
			KEY_4,
			KEY_5,
			KEY_6,
			KEY_7,
			KEY_8,
			KEY_9,
			/* Extenal number key. */
			KEY_NUM0,
			KEY_NUM1,
			KEY_NUM2,
			KEY_NUM3,
			KEY_NUM4,
			KEY_NUM5,
			KEY_NUM6,
			KEY_NUM7,
			KEY_NUM8,
			KEY_NUM9,
		GAIA_ENUM_END(KEY)

		class InputState : public GAIA::FWORK::Instance
		{
		public:
			GINL InputState(){}
			GINL ~InputState(){}
			GINL GAIA::BL IsKeyPressed(GAIA::INPUT::KEY key) const;
		private:
		};
	};
};

#endif