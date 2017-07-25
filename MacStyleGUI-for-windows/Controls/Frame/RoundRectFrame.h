#pragma once
#include "Frame.h"
#include "../../Graphics/Global.h"

namespace MacStyleGUI::Controls::Frame {

	class RoundRectFrame : public Frame {
	protected:
		Microsoft::WRL::ComPtr<ID2D1PathGeometry> m_RRF_FrameAreas[8];
	public:
		enum FrameArea {
			LeftUpCorner = 0,
			RightUpCorner = 1,
			RightDownCorner = 2,
			LeftDownCorner = 3,
			LeftRect = 4,
			TopRect = 5,
			RightRect = 6,
			BottomRect = 7,
			NoArea = -1
		};

		struct UpdateFrameAreas_fnArgs {
			UINT HwndWidth;
			UINT HwndHeight;
			FLOAT CornerRadius;
		};

		virtual VOID UpdateFrameAreas(VOID* args) override;
		virtual INT GetHitArea(CONST POINT& CurrentCursorPos) override;
		virtual LPCTSTR GetCursorID(INT HitArea)  override;

		virtual VOID StartResize(INT _HitArea,
								 CONST POINT& _OldCursorPos,
								 CONST RECT& _OldWindowRect) override;
		virtual BOOL ResizeWindow(HWND targetHwnd, CONST POINT& CursorPos) override;
		virtual VOID EndResize() override;
	};
}