#pragma once

#include <windows.h>

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