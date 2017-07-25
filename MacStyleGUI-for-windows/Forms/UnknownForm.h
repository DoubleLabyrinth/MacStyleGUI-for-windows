#pragma once
#include <windows.h>
#include "../EventSystem/EventHandler.h"

namespace MacStyleGUI::Forms {

	class UnknownForm {
	private:
		UnknownForm(const UnknownForm&) = delete;
		UnknownForm* operator=(const UnknownForm&) = delete;

		static volatile UnknownForm* s_CurrentCreatingForm;
	protected:
		HWND m_UnknownForm_Hwnd;

		INT m_UnknownForm_Hwnd_X;
		INT m_UnknownForm_Hwnd_Y;
		UINT m_UnknownForm_Hwnd_Width;
		UINT m_UnknownForm_Hwnd_Height;
	public:
		static UnknownForm* GetFormByHwnd(HWND hwnd) {
			UnknownForm* ret = reinterpret_cast<UnknownForm*>(GetWindowLongPtr(hwnd, 0));

			if (ret == nullptr)
				return const_cast<UnknownForm*>(s_CurrentCreatingForm);
			else
				return ret;
		}

		UnknownForm(int init_X, int init_Y, int init_HwndWidth, int init_HwndHeight):
			m_UnknownForm_Hwnd(NULL),
			m_UnknownForm_Hwnd_X(init_X),
			m_UnknownForm_Hwnd_Y(init_Y),
			m_UnknownForm_Hwnd_Width(init_HwndWidth),
			m_UnknownForm_Hwnd_Height(init_HwndHeight) { }

		HWND GetHwnd() CONST { return m_UnknownForm_Hwnd; }
		INT GetHwndPosX() CONST { return m_UnknownForm_Hwnd_X; }
		INT GetHwndPosY() CONST { return m_UnknownForm_Hwnd_Y; }
		UINT GetHwndWidth() CONST { return m_UnknownForm_Hwnd_Width; }
		UINT GetHwndHeight() CONST { return m_UnknownForm_Hwnd_Height; }

		virtual BOOL SetHwndPos(int newX, int newY) {
			m_UnknownForm_Hwnd_X = newX;
			m_UnknownForm_Hwnd_Y = newY;
			return TRUE;
		}

		virtual BOOL SetHwndSize(UINT newWidth, UINT newHeight) {
			m_UnknownForm_Hwnd_Width = newWidth;
			m_UnknownForm_Hwnd_Height = newHeight;
			return TRUE;
		}

		virtual BOOL CreateForm(VOID* args) = 0;
		virtual BOOL DestroyForm(VOID* args) = 0;

		virtual LRESULT ReceiveMessage(MSG Msg) = 0;
	};

	volatile UnknownForm* UnknownForm::s_CurrentCreatingForm = nullptr;
}