#pragma once
#include <windows.h>

namespace MacStyleGUI::Controls::Frame {
	
	class Frame {
	public:
		BOOL IsResizing;
		INT CursorHitArea;
		POINT OldCursorPos;
		RECT OldWindowRect;

		virtual VOID UpdateFrameAreas(VOID* args) = 0;
		virtual INT GetHitArea(CONST POINT& CurrentCursorPos) = 0;
		virtual LPCTSTR GetCursorID(INT HitArea) = 0;

		virtual VOID StartResize(INT _HitArea, 
								 CONST POINT& _OldCursorPos,
								 CONST RECT& _OldWindowRect) = 0;
		virtual BOOL ResizeWindow(HWND targetHwnd, CONST POINT& CursorPos) = 0;
		virtual VOID EndResize() = 0;
	};
}