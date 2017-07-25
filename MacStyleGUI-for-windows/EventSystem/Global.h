#pragma once
#include <windows.h>

namespace MacStyleGUI::EventSystem::Global {

	LRESULT CALLBACK ReceiveMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
}