#pragma once

#include "WindowClassExHelper.h"

namespace MacGUI::Forms {

	class BaseForm {
	private:
		BaseForm& operator=(const BaseForm&) = delete;
		BaseForm(const BaseForm&) = delete;
	protected:
		HWND m_Hwnd;

		static WindowClassExHelper WndClsEx;
		static LRESULT CALLBACK MsgProcessor(HWND Hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static BaseForm* CurrentCreatingFormPtr;
	public:
		BaseForm();

		BOOL CreateInstance(_In_opt_ LPCWSTR lpWindowName, 
							_In_ int X, _In_ int Y, 
							_In_ int nWidth, _In_ int nHeight, 
							_In_opt_ HWND hWndParent = NULL,
							_In_opt_ LPVOID lpParam = nullptr);

		HWND Get_Hwnd() const;
		
		BOOL DestroyInstance();

		virtual LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnSizing(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnSize(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnEraseBackground(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnLeftMouseButtonDown(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnLeftMouseButtonUp(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);
	};
}