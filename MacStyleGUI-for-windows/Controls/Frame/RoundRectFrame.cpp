#include "RoundRectFrame.h"
#include "../../GlobalDefine.h"

namespace MacStyleGUI::Controls::Frame {

	VOID RoundRectFrame::UpdateFrameAreas(VOID* args) {
		UpdateFrameAreas_fnArgs _args = *reinterpret_cast<UpdateFrameAreas_fnArgs*>(args);
		HRESULT hr = S_OK;
		Microsoft::WRL::ComPtr<ID2D1GeometrySink> sink;

		//update left up corner------------------------------------------------------------------------------------------------------
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreatePathGeometry(m_RRF_FrameAreas[FrameArea::LeftUpCorner].ReleaseAndGetAddressOf());
		if (FAILED(hr)) 
			throw hr;

		hr = m_RRF_FrameAreas[FrameArea::LeftUpCorner]->Open(sink.ReleaseAndGetAddressOf());
		if (FAILED(hr)) 
			throw hr;

		sink->BeginFigure(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, 0.f), D2D1_FIGURE_BEGIN_FILLED);
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(0.f, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius),
									  D2D1::SizeF(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius),
									  90.f,
									  D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
									  D2D1_ARC_SIZE_SMALL));
		sink->AddLine(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius));
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, MacStyleGUI_RESERVED_WIDTH),
									  D2D1::SizeF(_args.CornerRadius, _args.CornerRadius),
									  90.f,
									  D2D1_SWEEP_DIRECTION_CLOCKWISE,
									  D2D1_ARC_SIZE_SMALL));
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		sink->Close();

		//update right up corner-----------------------------------------------------------------------------------------------------
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreatePathGeometry(m_RRF_FrameAreas[FrameArea::RightUpCorner].ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = m_RRF_FrameAreas[FrameArea::RightUpCorner]->Open(sink.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		sink->BeginFigure(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius, 0.f), D2D1_FIGURE_BEGIN_FILLED);
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(_args.HwndWidth, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius),
									  D2D1::SizeF(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius),
									  90.f,
									  D2D1_SWEEP_DIRECTION_CLOCKWISE,
									  D2D1_ARC_SIZE_SMALL));
		sink->AddLine(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius));
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius, MacStyleGUI_RESERVED_WIDTH),
									  D2D1::SizeF(_args.CornerRadius, _args.CornerRadius),
									  90.f,
									  D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
									  D2D1_ARC_SIZE_SMALL));
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		sink->Close();

		//update right down corner-------------------------------------------------------------------------------------------------
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreatePathGeometry(m_RRF_FrameAreas[FrameArea::RightDownCorner].ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = m_RRF_FrameAreas[FrameArea::RightDownCorner]->Open(sink.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		sink->BeginFigure(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius, _args.HwndHeight), D2D1_FIGURE_BEGIN_FILLED);
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(_args.HwndWidth, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius),
									  D2D1::SizeF(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius),
									  90.f,
									  D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
									  D2D1_ARC_SIZE_SMALL));
		sink->AddLine(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius));
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH),
									  D2D1::SizeF(_args.CornerRadius, _args.CornerRadius),
									  90.f,
									  D2D1_SWEEP_DIRECTION_CLOCKWISE,
									  D2D1_ARC_SIZE_SMALL));
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		sink->Close();

		//update left down corner-------------------------------------------------------------------------------------------------
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreatePathGeometry(m_RRF_FrameAreas[FrameArea::LeftDownCorner].ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = m_RRF_FrameAreas[FrameArea::LeftDownCorner]->Open(sink.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		sink->BeginFigure(D2D1::Point2F(0.f, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius), D2D1_FIGURE_BEGIN_FILLED);
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, _args.HwndHeight),
									  D2D1::SizeF(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius),
									  90.f,
									  D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
									  D2D1_ARC_SIZE_SMALL));
		sink->AddLine(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH));
		sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius),
									  D2D1::SizeF(_args.CornerRadius, _args.CornerRadius),
									  90.f,
									  D2D1_SWEEP_DIRECTION_CLOCKWISE,
									  D2D1_ARC_SIZE_SMALL));
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		sink->Close();

		//update left rect----------------------------------------------------------------------------------------
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreatePathGeometry(m_RRF_FrameAreas[FrameArea::LeftRect].ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = m_RRF_FrameAreas[FrameArea::LeftRect]->Open(sink.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		sink->BeginFigure(D2D1::Point2F(0.f, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius), D2D1_FIGURE_BEGIN_FILLED);
		sink->AddLine(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius));
		sink->AddLine(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius));
		sink->AddLine(D2D1::Point2F(0.f, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius));
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		sink->Close();

		//update top rect--------------------------------------------------------------------------------------------
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreatePathGeometry(m_RRF_FrameAreas[FrameArea::TopRect].ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = m_RRF_FrameAreas[FrameArea::TopRect]->Open(sink.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		sink->BeginFigure(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, 0.f), D2D1_FIGURE_BEGIN_FILLED);
		sink->AddLine(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius, 0.f));
		sink->AddLine(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius, MacStyleGUI_RESERVED_WIDTH));
		sink->AddLine(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, MacStyleGUI_RESERVED_WIDTH));
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		sink->Close();

		//update right rect--------------------------------------------------------------------------------------------
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreatePathGeometry(m_RRF_FrameAreas[FrameArea::RightRect].ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = m_RRF_FrameAreas[FrameArea::RightRect]->Open(sink.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		sink->BeginFigure(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius), D2D1_FIGURE_BEGIN_FILLED);
		sink->AddLine(D2D1::Point2F(_args.HwndWidth, MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius));
		sink->AddLine(D2D1::Point2F(_args.HwndWidth, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius));
		sink->AddLine(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius));
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		sink->Close();

		//update bottom rect--------------------------------------------------------------------------------------------
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreatePathGeometry(m_RRF_FrameAreas[FrameArea::BottomRect].ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = m_RRF_FrameAreas[FrameArea::BottomRect]->Open(sink.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		sink->BeginFigure(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH), D2D1_FIGURE_BEGIN_FILLED);
		sink->AddLine(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius, _args.HwndHeight - MacStyleGUI_RESERVED_WIDTH));
		sink->AddLine(D2D1::Point2F(_args.HwndWidth - MacStyleGUI_RESERVED_WIDTH - _args.CornerRadius, _args.HwndHeight));
		sink->AddLine(D2D1::Point2F(MacStyleGUI_RESERVED_WIDTH + _args.CornerRadius, _args.HwndHeight));
		sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		sink->Close();
	}

	INT RoundRectFrame::GetHitArea(const POINT& CurrentCursorPos) {
		BOOL contain = FALSE;

		FrameArea sequence[8] = {
			FrameArea::RightDownCorner,
			FrameArea::RightRect,
			FrameArea::BottomRect,
			FrameArea::RightUpCorner,
			FrameArea::LeftDownCorner,
			FrameArea::LeftRect,
			FrameArea::TopRect,
			FrameArea::LeftUpCorner
		};

		for (auto& i : sequence) {
			if (m_RRF_FrameAreas[i].Get() != nullptr)
				m_RRF_FrameAreas[i]->FillContainsPoint(
					D2D1::Point2F(CurrentCursorPos.x, CurrentCursorPos.y), 
					nullptr, 
					&contain);
			if (contain)
				return i;
		}

		return FrameArea::NoArea;
	}

	LPCTSTR RoundRectFrame::GetCursorID(INT HitArea) {
		switch (HitArea) {
			case FrameArea::LeftUpCorner:
			case FrameArea::RightDownCorner:
				return IDC_SIZENWSE;
			case FrameArea::TopRect:
			case FrameArea::BottomRect:
				return IDC_SIZENS;
			case FrameArea::RightUpCorner:
			case FrameArea::LeftDownCorner:
				return IDC_SIZENESW;
			case FrameArea::LeftRect:
			case FrameArea::RightRect:
				return IDC_SIZEWE;
			default:
				return IDC_ARROW;
		}
	}

	VOID RoundRectFrame::StartResize(INT _HitArea, 
									 CONST POINT& _OldCursorPos, 
									 CONST RECT& _OldWindowRect) {
		CursorHitArea = _HitArea;
		OldCursorPos = _OldCursorPos;
		OldWindowRect = _OldWindowRect;
		IsResizing = TRUE;
	}

	BOOL RoundRectFrame::ResizeWindow(HWND targetHwnd, CONST POINT& CursorPos) {
		if (!IsResizing || targetHwnd == NULL)
			return FALSE;

		switch (CursorHitArea) {
			case LeftUpCorner:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  OldWindowRect.right - OldWindowRect.left - CursorPos.x + OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top - CursorPos.y + OldCursorPos.y,
								  TRUE);
			case RightDownCorner:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  TRUE);
			case TopRect:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  OldWindowRect.right - OldWindowRect.left,
								  OldWindowRect.bottom - OldWindowRect.top - CursorPos.y + OldCursorPos.y,
								  TRUE);
			case BottomRect:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left,
								  OldWindowRect.bottom - OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  TRUE);
			case RightUpCorner:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left,
								  OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  OldWindowRect.right - OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top - CursorPos.y + OldCursorPos.y,
								  TRUE);
			case LeftDownCorner:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left - CursorPos.x + OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top + CursorPos.y - OldCursorPos.y,
								  TRUE);
			case LeftRect:
				return MoveWindow(targetHwnd,
								  OldWindowRect.left + CursorPos.x - OldCursorPos.x,
								  OldWindowRect.top,
								  OldWindowRect.right - OldWindowRect.left - CursorPos.x + OldCursorPos.x,
								  OldWindowRect.bottom - OldWindowRect.top,
								  TRUE);
			case RightRect:
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

	VOID RoundRectFrame::EndResize() {
		IsResizing = FALSE;
	}
}