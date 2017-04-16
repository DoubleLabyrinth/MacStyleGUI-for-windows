#define _CRT_SECURE_NO_WARNINGS
#include "BaseForm.h"

namespace MacGUI::Forms {

	WindowClassExHelper BaseForm::WndClsEx = WindowClassExHelper();
	BaseForm* BaseForm::CurrentCreatingFormPtr = nullptr;

	LRESULT BaseForm::MsgProcessor(HWND Hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		// NOTICE:
		// Before CreateWindowEx function returns, messages below will be sent to HWND that function created by order:
		// 1.	WM_GETMINMAXINFO
		// 2.	WM_NCCREATE
		// 3.	WM_NCCALCSIZE
		// 4.	WM_CREATE
		// 5.   WM_Size   (Option)(When dwStyle contains WS_POPUPWINDOW, this one will send.)
		// So five messages below are handled specifically in MsgProcessFunction.

		BaseForm* pForm = reinterpret_cast<BaseForm*>(GetWindowLongPtr(Hwnd, 0));

		switch (msg) {
			case WM_GETMINMAXINFO:
				if (pForm == nullptr) {
					pForm = CurrentCreatingFormPtr;
					pForm->m_Hwnd = Hwnd;
					SetWindowLongPtr(Hwnd, 0, reinterpret_cast<LONG>(pForm));
					return pForm->OnGetMinMaxInfo(wParam, lParam);
				}
				return pForm->OnGetMinMaxInfo(wParam, lParam);
			case WM_CREATE:
				return pForm->OnCreate(wParam, lParam);
			case WM_PAINT:
				return pForm->OnPaint(wParam, lParam);
			case WM_DESTROY:
				return pForm->OnDestroy(wParam, lParam);
			case WM_SIZING:
				return pForm->OnSizing(wParam, lParam);
			case WM_SIZE:
				return pForm->OnSize(wParam, lParam);
			case WM_ERASEBKGND:
				return pForm->OnEraseBackground(wParam, lParam);
			case WM_LBUTTONDOWN:
				return pForm->OnLeftMouseButtonDown(wParam, lParam);
			case WM_LBUTTONUP:
				return pForm->OnLeftMouseButtonUp(wParam, lParam);
			case WM_MOUSEMOVE:
				return pForm->OnMouseMove(wParam, lParam);
			case WM_MOUSELEAVE:
				return pForm->OnMouseLeave(wParam, lParam);
			case WM_SETCURSOR:
				return pForm->OnSetCursor(wParam, lParam);
			default:
				return DefWindowProc(Hwnd, msg, wParam, lParam);
		}
	}

	BaseForm::BaseForm() {
		m_Hwnd = NULL;
		if (WndClsEx.Get_cbWndExtra() == 0) {
			WndClsEx.Set_cbWndExtra(sizeof(BaseForm*));
			WndClsEx.Set_hInstance(GetModuleHandle(nullptr));
			WndClsEx.Set_lpfnWndProc(MsgProcessor);
			WndClsEx.Set_lpszClassName(TEXT("MacBaseForm"));
			WndClsEx.Set_style(CS_VREDRAW | CS_HREDRAW | CS_OWNDC);
			WndClsEx.Set_hCursor((HCURSOR)LoadCursor(NULL, IDC_ARROW), FALSE);
		}
	}

	BOOL BaseForm::CreateInstance(_In_opt_ LPCWSTR lpWindowName,
								  _In_ int X, _In_ int Y,
								  _In_ int nWidth, _In_ int nHeight,
								  _In_opt_ HWND hWndParent /*= NULL*/,
								  _In_opt_ LPVOID lpParam /*= nullptr*/) {

		if (!WndClsEx.IsRegistered()) {
			if (!WndClsEx.Register()) {
				return FALSE;
			}
		}

		while (CurrentCreatingFormPtr != nullptr);  // if CurrentCreatingFormPtr is not null, we should wait.
		CurrentCreatingFormPtr = this;

		// NOTICE:
		// Before CreateWindowEx function returns, messages below will be sent to HWND that function created by order:
		// 1.	WM_GETMINMAXINFO
		// 2.	WM_NCCREATE
		// 3.	WM_NCCALCSIZE
		// 4.	WM_CREATE
		// 5.   WM_Size   (Option)(When dwStyle contains WS_POPUPWINDOW, this one will send.)
		// So five messages above are handled specifically in MsgProcessFunction.
		m_Hwnd = ::CreateWindowEx(WS_EX_NOREDIRECTIONBITMAP,
								  WndClsEx.Get_lpszClassName(),
								  lpWindowName,
								  NULL,
								  X, Y,
								  nWidth, nHeight,
								  hWndParent,
								  NULL,
								  WndClsEx.Get_hInstance(),
								  lpParam);
		CurrentCreatingFormPtr = nullptr;

		if (m_Hwnd == NULL) {
			return FALSE;
		}

		SetWindowLongPtr(m_Hwnd, GWL_STYLE, 0);
		return TRUE;
	}

	HWND BaseForm::Get_Hwnd() const {
		return m_Hwnd;
	}

	BOOL BaseForm::DestroyInstance() {
		if (m_Hwnd == NULL) return FALSE;
		if (DestroyWindow(m_Hwnd)) {
			m_Hwnd = NULL;
			return TRUE;
		}
		return FALSE;
	}


							
	LRESULT BaseForm::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_GETMINMAXINFO, wParam, lParam);
	}

	LRESULT BaseForm::OnCreate(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_CREATE, wParam, lParam);
	}

	LRESULT BaseForm::OnPaint(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_PAINT, wParam, lParam);
	}

	LRESULT BaseForm::OnDestroy(WPARAM wParam, LPARAM lParam) {
		PostQuitMessage(0);
		return DefWindowProc(m_Hwnd, WM_DESTROY, wParam, lParam);
	}

	LRESULT BaseForm::OnSizing(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_SIZING, wParam, lParam);
	}

	LRESULT BaseForm::OnSize(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_SIZE, wParam, lParam);
	}

	LRESULT BaseForm::OnEraseBackground(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_ERASEBKGND, wParam, lParam);
	}

	LRESULT BaseForm::OnLeftMouseButtonDown(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_LBUTTONDOWN, wParam, lParam);
	}

	LRESULT BaseForm::OnLeftMouseButtonUp(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_LBUTTONUP, wParam, lParam);
	}

	LRESULT BaseForm::OnMouseMove(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_MOUSEMOVE, wParam, lParam);
	}

	LRESULT BaseForm::OnMouseLeave(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_MOUSELEAVE, wParam, lParam);
	}

	LRESULT BaseForm::OnSetCursor(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_SETCURSOR, wParam, lParam);
	}
}