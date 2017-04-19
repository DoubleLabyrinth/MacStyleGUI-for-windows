#include "SizingManager.h"

#define WINDOW_FRAME_MANAGER_LEFT_UP_CORNER ((unsigned char)1)
#define WINDOW_FRAME_MANAGER_RIGHT_UP_CORNER ((unsigned char)2)
#define WINDOW_FRAME_MANAGER_LEFT_DOWN_CORNER ((unsigned char)4)
#define WINDOW_FRAME_MANAGER_RIGHT_DOWN_CORNER ((unsigned char)8)
#define WINDOW_FRAME_MANAGER_LEFT_RECT ((unsigned char)16)
#define WINDOW_FRAME_MANAGER_TOP_RECT ((unsigned char)32)
#define WINDOW_FRAME_MANAGER_RIGHT_RECT ((unsigned char)64)
#define WINDOW_FRAME_MANAGER_BOTTOM_RECT ((unsigned char)128)

namespace MacGUI::Forms::Tools {

	SizingManager::SizingManager() {
		SizingStaus = FALSE;
		OldCursorPos = {};
		OldWindowRect = {};
	}

	BOOL SizingManager::GetSizingStatus() const {
		return SizingStaus;
	}

	VOID SizingManager::SizingStart(const BYTE& srcHitArea,
									const POINT& srcOldCursorPos,
									const RECT& srcOldWindowRect) {
		HitArea = srcHitArea;
		OldCursorPos = srcOldCursorPos;
		OldWindowRect = srcOldWindowRect;
		SizingStaus = TRUE;
	}

	BOOL SizingManager::SizingWindow(HWND targetHwnd, const POINT& CursorPos) {
		if (!SizingStaus || targetHwnd == NULL) return FALSE;

		switch (HitArea) {
			case WINDOW_FRAME_MANAGER_LEFT_UP_CORNER:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  OldWindowRect.right - OldWindowRect.left - CursorPos.x + OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top - CursorPos.y + OldCursorPos.y,
								  TRUE);
			case WINDOW_FRAME_MANAGER_RIGHT_DOWN_CORNER:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  TRUE);
			case WINDOW_FRAME_MANAGER_TOP_RECT:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  OldWindowRect.right - OldWindowRect.left,
								  OldWindowRect.bottom - OldWindowRect.top - CursorPos.y + OldCursorPos.y,
								  TRUE);
			case WINDOW_FRAME_MANAGER_BOTTOM_RECT:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left,
								  OldWindowRect.bottom - OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  TRUE);
			case WINDOW_FRAME_MANAGER_RIGHT_UP_CORNER:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  OldWindowRect.right - OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top - CursorPos.y + OldCursorPos.y,
								  TRUE);
			case WINDOW_FRAME_MANAGER_LEFT_DOWN_CORNER:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left - CursorPos.x + OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  TRUE);
			case WINDOW_FRAME_MANAGER_LEFT_RECT:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left - CursorPos.x + OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top,
								  TRUE);
			case WINDOW_FRAME_MANAGER_RIGHT_RECT:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top,
								  TRUE);
			default:
				return FALSE;
		}
	}

	VOID SizingManager::SizingEnd() {
		SizingStaus = FALSE;
	}
}