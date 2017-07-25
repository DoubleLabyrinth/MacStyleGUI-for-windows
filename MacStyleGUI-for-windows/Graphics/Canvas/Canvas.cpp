#include "Canvas.h"

namespace MacStyleGUI::Graphics {
	Canvas::Canvas(_In_ UINT init_Width, _In_ UINT init_Height) {
		HRESULT hr = Global_DCompoDesktopDevice->
			CreateVirtualSurface(init_Width,
								 init_Height,
								 DXGI_FORMAT_B8G8R8A8_UNORM,
								 DXGI_ALPHA_MODE_PREMULTIPLIED,
								 m_VirtualSurcace.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = Global_DCompoDesktopDevice->CreateVisual(m_Visual.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;
								
		hr = Global_D2DDevice->
			CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
								m_DeviceContext.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;

		hr = m_Visual->SetContent(m_VirtualSurcace.Get());
		if (FAILED(hr)) throw hr;

		m_CanvasWidth = init_Width;
		m_CanvasHeight = init_Height;
	}

	HRESULT Canvas::Resize(_In_ UINT new_Width, _In_ UINT new_Height) {
		HRESULT hr = m_VirtualSurcace->Resize(new_Width, new_Height);
		if (FAILED(hr)) return hr;

		m_CanvasWidth = new_Width;
		m_CanvasHeight = new_Height;
		return hr;
	}

	UINT Canvas::GetCanvasWidth() const {
		return m_CanvasWidth;
	}

	UINT Canvas::GetCanvasHeight() const {
		return m_CanvasHeight;
	}

	HRESULT Canvas::BeginDraw(CONST RECT* updateRect, POINT* out_Offset) {
		return m_VirtualSurcace->BeginDraw(updateRect, __uuidof(m_DeviceContext),
										 reinterpret_cast<void**>(m_DeviceContext.GetAddressOf()), out_Offset);
	}

	HRESULT Canvas::EndDraw() {
		return m_VirtualSurcace->EndDraw();
	}

	HRESULT Canvas::SuspendDraw() {
		return m_VirtualSurcace->SuspendDraw();
	}

	HRESULT Canvas::ResumeDraw() {
		return m_VirtualSurcace->ResumeDraw();
	}

	HRESULT Canvas::Trim(const RECT *rectangles, UINT count) {
		return m_VirtualSurcace->Trim(rectangles, count);
	}

	HRESULT Canvas::Scoll(_In_opt_ const RECT *scrollRect,
						  _In_opt_ const RECT *clipRect,
						  _In_ int offsetX,
						  _In_ int offsetY) {
		return m_VirtualSurcace->Scroll(scrollRect, clipRect, offsetX, offsetY);
	}

	ID2D1DeviceContext* Canvas::GetDeviceContext() CONST {
		return m_DeviceContext.Get();
	}

	IDCompositionVisual2* Canvas::GetVisual() CONST {
		return m_Visual.Get();
	}
}