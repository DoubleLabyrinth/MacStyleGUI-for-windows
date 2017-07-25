#include "MacStyleForm.h"
#include "../../GlobalDefine.h"

namespace MacStyleGUI::Forms {

	CONST TCHAR STR_MacStyleForm[] = TEXT("MacStyleForm");

	MacStyleForm::MacStyleForm(int init_X, int init_Y, int init_HwndWidth, int init_HwndHeight) :
		DCompositionForm(init_X, init_Y, init_HwndWidth, init_HwndHeight),
		m_CornerRadius(8.f),
		testButton(100.f, 100.f, 
				   100, 50, 
				   D2D1::ColorF(D2D1::ColorF::White),
				   D2D1::ColorF(0x18A5D0),
				   D2D1::ColorF(0x0551CB)),
		Panel(0.f, 0.f, init_HwndWidth, init_HwndHeight, D2D1::ColorF(D2D1::ColorF::White)) { }

	LRESULT MacStyleForm::ReceiveMessage(MSG Msg) {
		switch (Msg.message) {
			case WM_CREATE:
				return OnCreate(&Msg.hwnd, Msg.wParam, Msg.lParam);
			case WM_SIZE:
				return OnSize(nullptr, Msg.wParam, Msg.lParam);
			case WM_PAINT:
				return OnPaint(nullptr, Msg.wParam, Msg.lParam);
			case WM_CLOSE:
				return OnClose(nullptr, Msg.wParam, Msg.lParam);
			case WM_DESTROY:
				return OnDestroy(nullptr, Msg.wParam, Msg.lParam);
			case WM_MOUSEMOVE:
				return OnMouseMove(nullptr, Msg.wParam, Msg.lParam);
			case WM_LBUTTONUP:
				return OnLMouseButtonUp(nullptr, Msg.wParam, Msg.lParam);
			case WM_LBUTTONDOWN:
				return OnLMouseButtonDown(nullptr, Msg.wParam, Msg.lParam);
			case WM_MOUSEWHEEL:
				return OnMouseWheel(nullptr, Msg.wParam, Msg.lParam);
			default:
				return DCompositionForm<STR_MacStyleForm>::ReceiveMessage(Msg);
		}
	}

	LRESULT MacStyleForm::OnCreate(VOID* args, WPARAM wParam, LPARAM lParam) {
		DCompositionForm::OnCreate(args, wParam, lParam);

		testButton.Events.HandleEvent(WM_CREATE, nullptr, &testButton);
		Panel.OnCreate(nullptr, wParam, lParam);

		MacStyleGUI::Controls::Frame::RoundRectFrame::UpdateFrameAreas_fnArgs args_to_pass = {
			m_UnknownForm_Hwnd_Width,
			m_UnknownForm_Hwnd_Height,
			m_CornerRadius
		};
		FrameManager.UpdateFrameAreas(&args_to_pass);

		m_RootVisual->AddVisual(Panel.GetRootVisual(), FALSE, nullptr);
		m_RootVisual->AddVisual(testButton.GetRootVisual(), FALSE, nullptr);
		return TRUE;
	}

	LRESULT MacStyleForm::OnSize(VOID* args, WPARAM wParam, LPARAM lParam) {
		
		if (FrameManager.IsResizing) {
			RECT newRect;
			GetWindowRect(m_Hwnd, &newRect);

			m_HwndWidth = newRect.right - newRect.left;
			m_HwndHeight = newRect.bottom - newRect.top;

			Panel.Resize(m_HwndWidth, m_HwndHeight);
		}
		
		return TRUE;
	}

	LRESULT MacStyleForm::OnPaint(VOID* args, WPARAM wParam, LPARAM lParam) {
		Panel.OnPaint(args, wParam, lParam);
		testButton.Events.HandleEvent(WM_PAINT, nullptr, &testButton);

		MacStyleGUI::Graphics::Global_DCompoDesktopDevice->Commit();
		ValidateRect(m_Hwnd, nullptr);
		return TRUE;
	}

	LRESULT MacStyleForm::OnMouseMove(VOID* args, WPARAM wParam, LPARAM lParam) {
		MacStyleGUI::EventSystem::MouseEventInfo mouseinfo(WM_MOUSEMOVE, m_Hwnd, wParam, lParam);
		if (!FrameManager.IsResizing) {
			SetCursor(LoadCursor(NULL, FrameManager.GetCursorID(FrameManager.GetHitArea(mouseinfo.Pos))));

			BOOL In;
			testButton.GetEventGeometry()->FillContainsPoint(D2D1::Point2F(mouseinfo.Pos.x, mouseinfo.Pos.y), nullptr, &In);
			if (testButton.GetButtonState() == MacStyleGUI::Controls::Button::ButtonState::Normal && In) {
				testButton.Events.HandleEvent(MacStyleGUI_EVENT_MOUSEIN, nullptr, &testButton);
			} else if ((testButton.GetButtonState() == MacStyleGUI::Controls::Button::ButtonState::Focused || 
					   testButton.GetButtonState() == MacStyleGUI::Controls::Button::ButtonState::Pressed) && !In) {
				testButton.Events.HandleEvent(MacStyleGUI_EVENT_MOUSEOUT, nullptr, &testButton);
			}
		} else {
			SetCursor(LoadCursor(NULL, FrameManager.GetCursorID(FrameManager.CursorHitArea)));

			POINT CursorPos;
			GetCursorPos(&CursorPos);
			FrameManager.ResizeWindow(m_Hwnd, CursorPos);
		}
		
		return TRUE;
	}

	LRESULT MacStyleForm::OnLMouseButtonUp(VOID* args, WPARAM wParam, LPARAM lParam) {
		static int ClickTimes;
		ClickTimes++;
// 		if (ClickTimes == 10)
// 			SendMessage(m_Hwnd, WM_CLOSE, NULL, NULL);

		if (FrameManager.IsResizing) {
			FrameManager.EndResize();
			MacStyleGUI::Controls::Frame::RoundRectFrame::UpdateFrameAreas_fnArgs args_to_pass = {
				m_HwndWidth,
				m_HwndHeight,
				m_CornerRadius
			};
			FrameManager.UpdateFrameAreas(&args_to_pass);
		}
		
		ReleaseCapture();
		return TRUE;
	}

	LRESULT MacStyleForm::OnLMouseButtonDown(VOID* args, WPARAM wParam, LPARAM lParam) {
		MacStyleGUI::EventSystem::MouseEventInfo mouse_event(WM_LBUTTONDOWN, m_Hwnd, wParam, lParam);
		SetCapture(m_Hwnd);

		//Prepare sizing
		POINT CursorPos;
		GetCursorPos(&CursorPos);
		INT hitArea = FrameManager.GetHitArea(mouse_event.Pos);
		if (hitArea != MacStyleGUI::Controls::Frame::RoundRectFrame::FrameArea::NoArea) {
			RECT oldRect;
			GetWindowRect(m_Hwnd, &oldRect);
			FrameManager.StartResize(hitArea, CursorPos, oldRect);
		}

		return TRUE;
	}

	LRESULT MacStyleForm::OnMouseWheel(VOID* args, WPARAM wParam, LPARAM lParam) {
		int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		m_CornerRadius += zDelta / 120;
		InvalidateRect(m_Hwnd, nullptr, FALSE);
		return TRUE;
	}
}