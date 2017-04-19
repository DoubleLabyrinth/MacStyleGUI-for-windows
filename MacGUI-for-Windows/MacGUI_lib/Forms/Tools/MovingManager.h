#pragma once

#include <windows.h>

namespace MacGUI::Forms::Tools {

	class MovingManager {
	private:
		BOOL MovingStatus;
		POINT OldCursorPos;
		RECT OldWindowRect;
	public:
		MovingManager();
		BOOL GetMovingStatus() const;

		VOID MovingStart(const POINT& srcOldCursorPos,
						 const RECT& srcOldWindowRect);
		BOOL MovingWindow(HWND targetHwnd, const POINT& CursorPos, BOOL Repaint);
		VOID MovingEnd();
	};
}