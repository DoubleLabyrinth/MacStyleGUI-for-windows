#pragma once

#include <tchar.h>
#include <windows.h>

namespace MacGUI::Forms {
	
	class WindowClassExHelper : private WNDCLASSEX {
		friend ATOM RegisterClassEx(_In_ CONST WNDCLASSEX*);
	private:
		ATOM m_atom;

		VOID SetAsDefault();
	public:
		WindowClassExHelper();
		WindowClassExHelper(_In_ const WNDCLASSEX& srcWindowClassEx);
		WindowClassExHelper(_In_ const WindowClassExHelper& srcWndClsHelper);
		~WindowClassExHelper();

		// Getter
		UINT Get_style() const;
		WNDPROC Get_lpfnWndProc() const;
		int Get_cbClsExtra() const;
		int Get_cbWndExtra() const;
		HINSTANCE Get_hInstance() const;
		HICON Get_hIcon() const;
		HCURSOR Get_hCursor() const;
		HBRUSH Get_hbrBackground() const;
		LPCTSTR Get_lpszClassName() const;
		LPCTSTR Get_lpszMenuName() const;
		HICON Get_hIconSm() const;

		// Setter
		BOOL Set_style(_In_ UINT new_style);
		BOOL Set_lpfnWndProc(_In_ WNDPROC new_lpfnWndProc);
		BOOL Set_cbClsExtra(_In_ int new_cbClsExtra);
		BOOL Set_cbWndExtra(_In_ int new_cbWndExtra);
		BOOL Set_hInstance(_In_ HINSTANCE new_hInstance);
		BOOL Set_hIcon(_In_ HICON new_hIcon, _In_opt_ BOOL DeletePrevious = TRUE);
		BOOL Set_hCursor(_In_ HCURSOR new_hCursor, _In_opt_ BOOL DeletePrevious = TRUE);
		BOOL Set_hbrBackground(_In_ HBRUSH new_hbrBackground, _In_opt_ BOOL DeletePrevious = TRUE);
		BOOL Set_lpszClassName(_In_ LPCTSTR new_lpszClassName);
		BOOL Set_lpszMenuName(_In_ LPCTSTR new_lpszMenuName);
		BOOL Set_hIconSm(_In_ HICON new_hIconSm, _In_opt_ BOOL DeletePrevious = TRUE);


		BOOL IsRegistered() const;
		BOOL Register();
		BOOL Unregister(_In_ BOOL ForceToDestroyAllHwnd);
	};
}