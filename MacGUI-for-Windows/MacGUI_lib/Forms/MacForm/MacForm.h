#pragma once

#include "../../Global.h"
#include "../BaseForm.h"
#include "../../Graphics/Canvas.h"

#pragma comment(lib, "dcomp.lib")
#pragma comment(lib, "dxguid.lib")
#include <dcomp.h>
#include <d2d1effects_2.h>

namespace MacGUI::Forms {
	class MacForm : public BaseForm {
	private:
		IDCompositionDesktopDevice* CompositionDevice = nullptr;
		IDCompositionDevice3* AssistantCompositionDevice = nullptr;
		IDCompositionTarget* CompositionTarget = nullptr;
		IDCompositionVisual2* RootVisual = nullptr;
		IDCompositionVisual2* BackgroundVisual = nullptr;
		IDCompositionVisual2* BackgroundPanel = nullptr;

		IDCompositionShadowEffect* shadow = nullptr;

		ID2D1Device2* FormDevice = nullptr;
		ID2D1DeviceContext2* FormDeviceContext = nullptr;

		ID2D1PathGeometry1* FormFrame = nullptr;

		Graphics::CompositionSwapChain* BackgroundSwapChain = nullptr;
		Graphics::SurfaceCanvas* BackgroundCanvas = nullptr;

		RECT WindowRect;
		BOOL LeftMouseButtonDown = FALSE;
		RECT OldWindowRect;
		D2D1_POINT_2F OldCursorPos;

		BOOL Contains = FALSE;
		BOOL ChangeSize = FALSE;
	public:
		MacForm() = default;
		~MacForm();
		HRESULT InitialDirectX();
		virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnSize(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnSizing(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnNonClientPaint(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnLeftMouseButtonDown(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnLeftMouseButtonUp(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam); 
		virtual LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);
	};
}