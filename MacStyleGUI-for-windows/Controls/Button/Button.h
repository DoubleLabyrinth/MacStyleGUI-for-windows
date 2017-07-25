#pragma once
#include "../UIComponent.h"

namespace MacStyleGUI::Controls::Button {

	enum class ButtonState {
		Normal = 0,
		Focused = 1,
		Pressed = 2
	};

	class Button : public MacStyleGUI::Controls::UIConponent {
	protected:
		ButtonState m_ButtonState;

		D2D1_COLOR_F m_Button_NormalColor;
		D2D1_COLOR_F m_Button_FocusedColor;
		D2D1_COLOR_F m_Button_PressedColor;
	public:
		Button() :
			m_ButtonState(ButtonState::Normal),
			m_Button_NormalColor({ }),
			m_Button_FocusedColor({ }),
			m_Button_PressedColor({ }) { }

		virtual ButtonState GetButtonState() CONST { return m_ButtonState; }

		virtual D2D1_COLOR_F GetNormalColor() CONST { return m_Button_NormalColor; }
		virtual D2D1_COLOR_F GetMouseOverColor() CONST { return m_Button_FocusedColor; }
		virtual D2D1_COLOR_F GetMouseDownColor() CONST { return m_Button_PressedColor; }
		virtual VOID SetNormalColor(const D2D1_COLOR_F& newColor) { m_Button_NormalColor = newColor; }
		virtual VOID SetMouseOverColor(const D2D1_COLOR_F& newColor) { m_Button_FocusedColor = newColor; }
		virtual VOID SetMouseDownColor(const D2D1_COLOR_F& newColor) { m_Button_PressedColor = newColor; }
	};
}