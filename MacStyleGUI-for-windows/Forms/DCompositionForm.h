#pragma once
#include "UnknownForm.h"
#include "../Graphics/Global.h"
#include "../EventSystem/Global.h"

namespace MacStyleGUI::Forms {

	template<LPCTSTR WindowClassName>
	class DCompositionForm : public UnknownForm {
	private:
		DCompositionForm<WindowClassName>(const DCompositionForm<WindowClassName>&) = delete;
		DCompositionForm<WindowClassName>& operator=(const DCompositionForm<WindowClassName>&) = delete;

		static ATOM WindowClassExInstance;
		static WNDCLASSEX WindowClassEx;
	protected:
		Microsoft::WRL::ComPtr<IDCompositionTarget> m_HwndTarget;
		Microsoft::WRL::ComPtr<IDCompositionVisual2> m_RootVisual;
	public:
		DCompositionForm(int init_X, int init_Y, int init_HwndWidth, int init_HwndHeight) :
			UnknownForm(init_X, init_Y, init_HwndWidth, init_HwndHeight)
		{ 
			//Create Visual
			HRESULT hr = MacStyleGUI::Graphics::Global_DCompoDesktopDevice->
				CreateVisual(m_RootVisual.ReleaseAndGetAddressOf());
			if (FAILED(hr))
				throw hr;
		}

		virtual BOOL CreateForm(VOID* args) override {
			if (WindowClassExInstance == 0) {
				WindowClassEx = {};
				WindowClassEx.style = CS_VREDRAW | CS_HREDRAW;
				WindowClassEx.lpfnWndProc = MacStyleGUI::EventSystem::Global::ReceiveMessage;
				WindowClassEx.cbWndExtra = sizeof(UnknownForm*);
				WindowClassEx.lpszClassName = WindowClassName;

				WindowClassExInstance = RegisterClassEx(&WindowClassEx);
				if (WindowClassExInstance == NULL) return FALSE;
			}

			while (true) {
				if (CurrentCreatingWindow == nullptr)
					break;
			}

			CurrentCreatingWindow = this;
			m_UnknownForm_Hwnd = ::CreateWindowEx(WS_EX_NOREDIRECTIONBITMAP,
									  WindowClassName,
									  WindowClassName,
									  NULL,
									  m_UnknownForm_Hwnd_X, m_UnknownForm_Hwnd_Y,
									  m_UnknownForm_Hwnd_Width, m_UnknownForm_Hwnd_Height,
									  NULL,														// Here we should think about parent Window later.
									  NULL,
									  NULL,
									  NULL);
			CurrentCreatingWindow = nullptr;

			if (m_UnknownForm_Hwnd == NULL) return FALSE;

			SetWindowLongPtr(m_UnknownForm_Hwnd, 0, reinterpret_cast<LONG_PTR>(this));	// This two could not exchange.
			SetWindowLongPtr(m_UnknownForm_Hwnd, GWL_STYLE, NULL);

			return TRUE;
		}

		virtual BOOL DestroyForm(VOID* args) override {
			return TRUE;
		}

		virtual LRESULT ReceiveMessage(MSG Msg) override {
			// NOTICE:
			// Before CreateWindowEx function returns, messages below will be sent to HWND that function created by order:
			// 1.	WM_GETMINMAXINFO
			// 2.	WM_NCCREATE
			// 3.	WM_NCCALCSIZE
			// 4.	WM_CREATE
			// 5.   WM_Size   (Option)(When dwStyle contains WS_POPUPWINDOW, this one will send.)
			// So the first message received in five messages above should be handled specifically, which means you should pass hwnd argument if you will use it.

			switch (Msg.message) {
				case WM_CREATE:
					return OnCreate(&hwnd, wParam, lParam);
				case WM_SIZE:
					return OnSize(nullptr, wParam, lParam);
				case WM_MOVE:
					return OnMove(nullptr, wParam, lParam);
				case WM_CLOSE:
					return OnClose(nullptr, wParam, lParam);
				case WM_DESTROY:
					return OnDestroy(nullptr, wParam, lParam);
				default:
					return DefWindowProc(hwnd, Msg, wParam, lParam);
			}
		}

		virtual LRESULT OnCreate(VOID* args, WPARAM wParam, LPARAM lParam) {
			m_UnknownForm_Hwnd = *reinterpret_cast<HWND*>(args);

			//Create IDCompositionTarget from Hwnd.
			HRESULT hr = MacStyleGUI::Graphics::Global_DCompoDesktopDevice->
				CreateTargetForHwnd(m_UnknownForm_Hwnd, TRUE, m_HwndTarget.ReleaseAndGetAddressOf());
			if (FAILED(hr))
				throw hr;

			hr = m_HwndTarget->SetRoot(m_RootVisual.Get());
			if (FAILED(hr))
				throw hr;

			return 0;
		}
		
		virtual LRESULT OnSize(VOID* args, WPARAM wParam, LPARAM lParam) {
			DCompositionForm::SetHwndSize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}

		virtual LRESULT OnMove(VOID* args, WPARAM wParam, LPARAM lParam) {
			DCompositionForm::SetHwndPos((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam));
			return 0;
		}

		virtual LRESULT OnClose(VOID* args, WPARAM wParam, LPARAM lParam) {
			m_RootVisual->RemoveAllVisuals();
			m_HwndTarget->SetRoot(nullptr);
			m_RootVisual.ReleaseAndGetAddressOf();
			m_HwndTarget.ReleaseAndGetAddressOf();

			DestroyWindow(m_UnknownForm_Hwnd);

			if (FindWindow(WindowClassName, nullptr) == NULL)
				return UnregisterClass(WindowClassName, WindowClassEx.hInstance);

			return 0;
		}

		virtual LRESULT OnDestroy(VOID* args, WPARAM wParam, LPARAM lParam) {
			PostQuitMessage(0);

			return 0;
		}
	};

	template<LPCTSTR WindowClassName> ATOM DCompositionForm<WindowClassName>::WindowClassExInstance = 0;
	template<LPCTSTR WindowClassName> WNDCLASSEX DCompositionForm<WindowClassName>::WindowClassEx = { sizeof(WNDCLASSEX) };
	template<LPCTSTR WindowClassName> volatile DCompositionForm<WindowClassName>* DCompositionForm<WindowClassName>::CurrentCreatingWindow = nullptr;
}