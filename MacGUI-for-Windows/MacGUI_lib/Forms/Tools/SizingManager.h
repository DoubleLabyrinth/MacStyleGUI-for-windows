#pragma once
#pragma comment(lib, "d2d1.lib")

#include <windows.h>
#include <d2d1.h>

namespace MacGUI::Forms::Tools {

	class SizingManager {
	private:
		BOOL SizingStaus;
		BYTE HitArea;
		POINT OldCursorPos;
		RECT OldWindowRect;
	public:
		SizingManager();
		BOOL GetSizingStatus() const;

		VOID SizingStart(const BYTE& srcHitArea, 
						 const POINT& srcOldCursorPos, 
						 const RECT& srcOldWindowRect);
		BOOL SizingWindow(HWND targetHwnd, const POINT& CursorPos);
		VOID SizingEnd();
	};
}