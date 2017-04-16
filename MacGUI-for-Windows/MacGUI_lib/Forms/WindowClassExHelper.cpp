#define _CRT_SECURE_NO_WARNINGS
#include "WindowClassExHelper.h"

namespace MacGUI::Forms {

	VOID WindowClassExHelper::SetAsDefault() {
		m_atom = 0;

		cbSize = sizeof(WNDCLASSEX);
		style = 0;
		lpfnWndProc = nullptr;
		cbClsExtra = 0;
		cbWndExtra = 0;
		hInstance = NULL;
		hIcon = NULL;
		hCursor = NULL;
		hbrBackground = NULL;
		lpszClassName = nullptr;
		lpszMenuName = nullptr;
		hIconSm = NULL;
	}

	WindowClassExHelper::WindowClassExHelper() {
		SetAsDefault();
	}

	WindowClassExHelper::WindowClassExHelper(_In_ const WNDCLASSEX& srcWindowClassEx) {
		cbSize = sizeof(WNDCLASSEX);

		if (srcWindowClassEx.lpszClassName == nullptr) {
			lpszClassName = nullptr;
		} else {
			lpszClassName = new TCHAR[_tcslen(srcWindowClassEx.lpszClassName) + 1];
			if (lpszClassName = nullptr) {
				SetAsDefault();
				return;
			}

			_tcscpy(const_cast<LPTSTR>(lpszClassName), srcWindowClassEx.lpszClassName);
		}

		if (srcWindowClassEx.lpszMenuName == nullptr) {
			lpszMenuName = nullptr;
		} else {
			lpszMenuName = new TCHAR[_tcslen(srcWindowClassEx.lpszMenuName) + 1];
			if (lpszMenuName == nullptr) {
				delete[] const_cast<LPTSTR>(lpszClassName);
				lpszClassName = nullptr;
				SetAsDefault();
				return;
			}

			_tcscpy(const_cast<LPTSTR>(lpszMenuName), srcWindowClassEx.lpszMenuName);
		}

		style = srcWindowClassEx.style;
		lpfnWndProc = srcWindowClassEx.lpfnWndProc;
		cbClsExtra = srcWindowClassEx.cbClsExtra;
		cbWndExtra = srcWindowClassEx.cbWndExtra;
		hInstance = srcWindowClassEx.hInstance;
		hIcon = srcWindowClassEx.hIcon;
		hCursor = srcWindowClassEx.hCursor;
		hbrBackground = srcWindowClassEx.hbrBackground;
		hIconSm = srcWindowClassEx.hIconSm;

		m_atom = 0;
	}

// 	WindowClassExHelper::WindowClassExHelper(_In_ const WindowClassExHelper& srcWndClsHelper) {
// 		m_atom = 0;
// 
// 		cbSize = sizeof(WNDCLASSEX);
// 		style = srcWndClsHelper.style;
// 		lpfnWndProc = srcWndClsHelper.lpfnWndProc;
// 		cbClsExtra = srcWndClsHelper.cbClsExtra;
// 		cbWndExtra = srcWndClsHelper.cbWndExtra;
// 		hInstance = srcWndClsHelper.hInstance;
// 		hIcon = srcWndClsHelper.hIcon;
// 		hCursor = srcWndClsHelper.hCursor;
// 		hbrBackground = srcWndClsHelper.hbrBackground;
// 		lpszClassName = ;
// 		lpszMenuName = nullptr;
// 		hIconSm = NULL;
// 	}

	WindowClassExHelper::~WindowClassExHelper() {
		Unregister(TRUE);
		DeleteObject(hIcon);
		DeleteObject(hIconSm);
		DeleteObject(hCursor);
		DeleteObject(hbrBackground);
		delete[] const_cast<LPTSTR>(lpszClassName);
		delete[] const_cast<LPTSTR>(lpszMenuName);
	}

	// Getter


	UINT WindowClassExHelper::Get_style() const {
		return style;
	}

	WNDPROC WindowClassExHelper::Get_lpfnWndProc() const {
		return lpfnWndProc;
	}

	int WindowClassExHelper::Get_cbClsExtra() const {
		return cbClsExtra;
	}

	int WindowClassExHelper::Get_cbWndExtra() const {
		return cbWndExtra;
	}

	HINSTANCE WindowClassExHelper::Get_hInstance() const {
		return hInstance;
	}

	HICON WindowClassExHelper::Get_hIcon() const {
		return hIcon;
	}

	HCURSOR WindowClassExHelper::Get_hCursor() const {
		return hCursor;
	}

	HBRUSH WindowClassExHelper::Get_hbrBackground() const {
		return hbrBackground;
	}

	LPCTSTR WindowClassExHelper::Get_lpszClassName() const {
		return lpszClassName;
	}

	LPCTSTR WindowClassExHelper::Get_lpszMenuName() const {
		return lpszMenuName;
	}

	HICON WindowClassExHelper::Get_hIconSm() const {
		return hIconSm;
	}


	// Setter


	BOOL WindowClassExHelper::Set_style(_In_ UINT new_style) {
		if (m_atom != 0) return FALSE;
		style = new_style;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_lpfnWndProc(_In_ WNDPROC new_lpfnWndProc) {
		if (m_atom != 0) return FALSE;
		lpfnWndProc = new_lpfnWndProc;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_cbClsExtra(_In_ int new_cbClsExtra) {
		if (m_atom != 0) return FALSE;
		cbClsExtra = new_cbClsExtra;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_cbWndExtra(_In_ int new_cbWndExtra) {
		if (m_atom != 0) return FALSE;
		cbWndExtra = new_cbWndExtra;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_hInstance(_In_ HINSTANCE new_hInstance) {
		if (m_atom != 0) return FALSE;
		hInstance = new_hInstance;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_hIcon(_In_ HICON new_hIcon, 
										_In_opt_ BOOL DeletePrevious /* = TRUE */) {
		if (m_atom != 0) return FALSE;
		if (DeletePrevious) DeleteObject(hIcon);
		hIcon = new_hIcon;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_hCursor(_In_ HCURSOR new_hCursor, 
										  _In_opt_ BOOL DeletePrevious /* = TRUE */) {
		if (m_atom != 0) return FALSE;
		if (DeletePrevious) DeleteObject(hCursor);
		hCursor = new_hCursor;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_hbrBackground(_In_ HBRUSH new_hbrBackground, 
												_In_opt_ BOOL DeletePrevious /* = TRUE */) {
		if (m_atom != 0) return FALSE;
		if (DeletePrevious) DeleteObject(hbrBackground);
		hbrBackground = new_hbrBackground;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_lpszClassName(_In_ LPCTSTR new_lpszClassName) {
		if (m_atom != 0) return FALSE;

		if (new_lpszClassName == nullptr) {
			delete[] const_cast<LPTSTR>(lpszClassName);
			lpszClassName = nullptr;
			return TRUE;
		}

		LPTSTR temp = new TCHAR[_tcslen(new_lpszClassName) + 1]();
		if (temp == nullptr) return FALSE;
		_tcscpy(temp, new_lpszClassName);

		delete[] const_cast<LPTSTR>(lpszClassName);
		lpszClassName = temp;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_lpszMenuName(_In_ LPCTSTR new_lpszMenuName) {
		if (m_atom != 0) return FALSE;

		if (new_lpszMenuName == nullptr) {
			delete[] const_cast<LPTSTR>(lpszMenuName);
			lpszMenuName = nullptr;
			return TRUE;
		}

		LPTSTR temp = new TCHAR[_tcslen(new_lpszMenuName) + 1]();
		if (temp == nullptr) return FALSE;
		_tcscpy(temp, new_lpszMenuName);

		delete[] const_cast<LPTSTR>(lpszMenuName);
		lpszMenuName = temp;
		return TRUE;
	}

	BOOL WindowClassExHelper::Set_hIconSm(_In_ HICON new_hIconSm, 
										  _In_opt_ BOOL DeletePrevious /* = TRUE */) {
		if (m_atom != 0) return FALSE;
		if (DeletePrevious) DeleteObject(hIconSm);
		hIconSm = new_hIconSm;
		return TRUE;
	}

	BOOL WindowClassExHelper::IsRegistered() const {
		return m_atom != 0 ? TRUE : FALSE;
	}

	BOOL WindowClassExHelper::Register() {
		if (m_atom != 0) return FALSE;

		m_atom = ::RegisterClassEx(this);

		return m_atom != 0 ? TRUE : FALSE;
	}

	BOOL WindowClassExHelper::Unregister(_In_ BOOL ForceToDestroyAllHwnd) {
		if (m_atom == 0) return FALSE;

		if (ForceToDestroyAllHwnd) {
			HWND HwndToDestroy = NULL;
			do {                              // Destroy all windows.
				HwndToDestroy = FindWindow(lpszClassName, nullptr);
				if (HwndToDestroy == NULL) break;
				DestroyWindow(HwndToDestroy);
			} while (TRUE);
		}

		if (::UnregisterClass(lpszClassName, hInstance) == TRUE) {
			m_atom = 0;
			return TRUE;
		}

		return FALSE;
	}
}

