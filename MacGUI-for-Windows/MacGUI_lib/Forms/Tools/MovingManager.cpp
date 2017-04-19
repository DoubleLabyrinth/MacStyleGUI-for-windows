#include "MovingManager.h"

namespace MacGUI::Forms::Tools {

	MovingManager::MovingManager() {
		MovingStatus = FALSE;
		OldCursorPos = {};
		OldWindowRect = {};
	}

	BOOL MovingManager::GetMovingStatus() const {
		return MovingStatus;
	}

	VOID MovingManager::MovingStart(const POINT& srcOldCursorPos,
									const RECT& srcOldWindowRect) {
		OldCursorPos = srcOldCursorPos;
		OldWindowRect = srcOldWindowRect;
		MovingStatus = TRUE;
	}

	BOOL MovingManager::MovingWindow(HWND targetHwnd, const POINT& CursorPos, BOOL Repaint) {
		if (!MovingStatus || targetHwnd == NULL) return FALSE;

		return MoveWindow(targetHwnd,
						  OldWindowRect.left + CursorPos.x - OldCursorPos.x,
						  OldWindowRect.top + CursorPos.y - OldCursorPos.y,
						  OldWindowRect.right - OldWindowRect.left,
						  OldWindowRect.bottom - OldWindowRect.top,
						  Repaint);
	}

	VOID MovingManager::MovingEnd() {
		MovingStatus = FALSE;
	}
}