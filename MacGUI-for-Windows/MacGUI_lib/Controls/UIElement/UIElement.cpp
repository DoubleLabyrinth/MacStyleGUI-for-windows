#include "UIElement.h"

namespace MDGUI::DrawingTools {

	UIElement::UIElement() {
		Initialized = FALSE;
		m_UISwapChain = nullptr;
		m_UICanvas = nullptr;

		m_UISize.width = 0;
		m_UISize.height = 0;
	}

	UIElement::~UIElement() {
		Destroy();
	}

	HRESULT UIElement::Initialize(_In_ IDXGIDevice* srcDXGIDevice,
								  _In_ IDXGIFactory2* srcDXGIFactory,
								  _In_ ID2D1DeviceContext2* srcD2DDeviceContext,
								  _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc,
								  _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps) {

		if (Initialized) return S_OK;

		m_UISwapChain = new CompositionSwapChain(srcDXGIDevice, srcDXGIFactory, srcSwapChainDesc);
		if (m_UISwapChain == nullptr) return E_OUTOFMEMORY;
		
		m_UICanvas = new SurfaceCanvas(m_UISwapChain, srcD2DDeviceContext, srcCanvasProps);
		if (m_UICanvas == nullptr) return E_OUTOFMEMORY;

		HRESULT hr = S_OK;

		m_UISwapChain->SetSize(m_UISize.width, m_UISize.height);

		hr = m_UISwapChain->CreateSwapChain();
		if (FAILED(hr)) return hr;

		hr = m_UICanvas->ObtainSurface();
		if (FAILED(hr)) return hr;

		hr = m_UICanvas->CreateCanvas();
		if (FAILED(hr)) return hr;

		Initialized = TRUE;

		return hr;
	}

	VOID UIElement::Destroy() {
		if (Initialized == FALSE) return;
		
		while (m_UICanvas->ReleaseCanvas());
		while (m_UICanvas->ReleaseSurface());
		delete m_UICanvas;
		m_UICanvas = nullptr;

		while (m_UISwapChain->ReleaseSwapChain());
		m_UISwapChain = nullptr;

		Initialized = FALSE;
	}

	CompositionSwapChain* UIElement::GetSwapChain() {
		return m_UISwapChain;
	}

	SurfaceCanvas* UIElement::GetCanvas() {
		return m_UICanvas;
	}
}