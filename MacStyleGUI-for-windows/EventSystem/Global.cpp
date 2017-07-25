#include "Global.h"
#include "../Forms/UnknownForm.h"

namespace MacStyleGUI::EventSystem::Global {

	LRESULT CALLBACK ReceiveMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		POINT pt;
		GetCursorPos(&pt);
		MSG newMsg = { hwnd, message, wParam, lParam, GetMessageTime(), pt };

		MacStyleGUI::Forms::UnknownForm* form = MacStyleGUI::Forms::UnknownForm::GetFormByHwnd(hwnd);
		if (form != nullptr)
			return form->ReceiveMessage(newMsg);
		else
			return -1;
	}
}