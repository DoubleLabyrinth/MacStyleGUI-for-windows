#include "Canvas.h"

namespace MacGUI::Graphics {

	Canvas::Canvas(_In_ UINT nWidth, _In_ UINT nHeight, 
				   _In_ ID2D1DeviceContext2* srcD2DDeviceContext,
				   _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc/* = nullptr */,
				   _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps /* = nullptr */) {

		parentD2DDeviceContext = srcD2DDeviceContext;

		m_SwapChain = nullptr;

		m_SwapChainDescription.Scaling = DXGI_SCALING_STRETCH;					// Must be "DXGI_SCALING_STRETCH". Described at https://msdn.microsoft.com/zh-cn/library/windows/apps/hh404528.aspx
		m_SwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// Must be "DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL". Described at https://msdn.microsoft.com/zh-cn/library/windows/apps/hh404528.aspx
		m_SwapChainDescription.Stereo = FALSE;									// We do not use full-screen mode. So set it FALSE.
		m_SwapChainDescription.Width = nWidth;									// Specified by the argument "nWidth".
		m_SwapChainDescription.Height = nHeight;								// Specified by the argument "nHeight".
		if (srcSwapChainDesc == nullptr) {			// Use default SwapChainDesc.
			m_SwapChainDescription.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;		// We use default value. Enable alpha color tunnel.
			m_SwapChainDescription.BufferCount = 2;									// We use default value. Use double buffer.
			m_SwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			m_SwapChainDescription.Flags = 0;										// We use default value. Nothing should be specified.
			m_SwapChainDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// We use default value.
			m_SwapChainDescription.SampleDesc.Count = 1;							// We use default value.
			m_SwapChainDescription.SampleDesc.Quality = 0;							// We use default value.
		} else {
			m_SwapChainDescription.AlphaMode = srcSwapChainDesc->AlphaMode;
			m_SwapChainDescription.BufferCount = srcSwapChainDesc->BufferCount;
			m_SwapChainDescription.BufferUsage = srcSwapChainDesc->BufferUsage;
			m_SwapChainDescription.Flags = srcSwapChainDesc->Flags;
			m_SwapChainDescription.Format = srcSwapChainDesc->Format;
			m_SwapChainDescription.SampleDesc = srcSwapChainDesc->SampleDesc;
		}

		m_Surface = nullptr;
		m_BitmapCanvas = nullptr;

		m_BitmapCanvasProps.dpiX = MacGUI::Global::Desktop_DpiX;
		m_BitmapCanvasProps.dpiY = MacGUI::Global::Desktop_DpiY;
		if (srcCanvasProps == nullptr) {
			m_BitmapCanvasProps.bitmapOptions = D2D1_BITMAP_OPTIONS_CANNOT_DRAW | D2D1_BITMAP_OPTIONS_TARGET;
			m_BitmapCanvasProps.colorContext = nullptr;
			m_BitmapCanvasProps.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
			m_BitmapCanvasProps.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
		} else {
			m_BitmapCanvasProps.bitmapOptions = srcCanvasProps->bitmapOptions;
			m_BitmapCanvasProps.colorContext = srcCanvasProps->colorContext;
			m_BitmapCanvasProps.pixelFormat = srcCanvasProps->pixelFormat;
		}
	}

	Canvas::~Canvas() {
		while (m_BitmapCanvas->Release());
		while (m_Surface->Release());
		while (m_SwapChain->Release());
	}

	HRESULT Canvas::ChangeD2DDeviceContext(_In_ ID2D1DeviceContext2* newD2DDeviceContext) {
		if (newD2DDeviceContext == nullptr) return E_POINTER;

		HRESULT hr = S_OK;

		if (m_BitmapCanvas) {
			while (m_BitmapCanvas->Release());
			m_BitmapCanvas = nullptr;
		}

		parentD2DDeviceContext = newD2DDeviceContext;

		hr = parentD2DDeviceContext->CreateBitmapFromDxgiSurface(m_Surface, m_BitmapCanvasProps, &m_BitmapCanvas);
		if (FAILED(hr)) {
			DisposeCanvas();
			return hr;
		}

		return hr;
	}

	const DXGI_SWAP_CHAIN_DESC1 Canvas::GetSwapChainDesc() const {
		return m_SwapChainDescription;
	}

	HRESULT Canvas::ChangeSwapChainDesc(const DXGI_SWAP_CHAIN_DESC1& newDesc, BOOL reCreateCanvas) {
		DisposeCanvas();

		m_SwapChainDescription.AlphaMode = newDesc.AlphaMode;
		m_SwapChainDescription.BufferCount = newDesc.BufferCount;
		m_SwapChainDescription.BufferUsage = newDesc.BufferUsage;
		m_SwapChainDescription.Flags = newDesc.Flags;
		m_SwapChainDescription.Format = newDesc.Format;
		m_SwapChainDescription.SampleDesc = newDesc.SampleDesc;

		if (reCreateCanvas) return CreateCanvas();
		return S_OK;
	}

	const D2D1_BITMAP_PROPERTIES1 Canvas::GetCanvasProps() const {
		return m_BitmapCanvasProps;
	}

	HRESULT Canvas::ChangeCanvasProps(_In_ const D2D1_BITMAP_PROPERTIES1& newProps, _In_ BOOL reCreateCanvas) {
		DisposeCanvas();

		m_BitmapCanvasProps.bitmapOptions = newProps.bitmapOptions;
		m_BitmapCanvasProps.colorContext = newProps.colorContext;
		m_BitmapCanvasProps.pixelFormat = newProps.pixelFormat;
		
		if (reCreateCanvas) return CreateCanvas();
		return S_OK;
	}

	HRESULT Canvas::CreateCanvas() {
		if (m_BitmapCanvas) return S_OK;

		if (MacGUI::Global::DXGIFactory == nullptr ||
			MacGUI::Global::DXGIDevice == nullptr ||
			parentD2DDeviceContext == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		
		hr = MacGUI::Global::DXGIFactory->CreateSwapChainForComposition(MacGUI::Global::DXGIDevice, &m_SwapChainDescription, nullptr, &m_SwapChain);
		if (FAILED(hr)) return hr;

		hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_Surface));
		if (FAILED(hr)) {
			while (m_SwapChain->Release());
			m_SwapChain = nullptr;
			return hr;
		}

		hr = parentD2DDeviceContext->CreateBitmapFromDxgiSurface(m_Surface, m_BitmapCanvasProps, &m_BitmapCanvas);
		if (FAILED(hr)) {
			while (m_Surface->Release());
			m_Surface = nullptr;
			while (m_SwapChain->Release());
			m_SwapChain = nullptr;
			return hr;
		}

		return hr;
	}

	VOID Canvas::DisposeCanvas() {
		if (m_BitmapCanvas) {
			while (m_BitmapCanvas->Release());
			m_BitmapCanvas = nullptr;
		}

		if (m_Surface) {
			while (m_Surface->Release());
			m_Surface = nullptr;
		}

		if (m_SwapChain) {
			while (m_SwapChain->Release());
			m_SwapChain = nullptr;
		}
	}

	IDXGISwapChain1* Canvas::GetSwapChain() {
		return m_SwapChain;
	}

	IDXGISurface2* Canvas::GetSurface() {
		return m_Surface;
	}

	ID2D1Bitmap1* Canvas::GetCanvas() {
		return m_BitmapCanvas;
	}

	HRESULT Canvas::Resize(_In_ UINT newWidth, _In_ UINT newHeight) {
		HRESULT hr = S_OK;

		if (m_BitmapCanvas) {
			while (m_BitmapCanvas->Release());
			m_BitmapCanvas = nullptr;
		}

		if (m_Surface) {
			while (m_Surface->Release());
			m_Surface = nullptr;
		}

		if (m_SwapChain == nullptr) {
			m_SwapChainDescription.Width = newWidth;
			m_SwapChainDescription.Height = newHeight;
			return hr;
		}

		hr = m_SwapChain->ResizeBuffers(m_SwapChainDescription.BufferCount,
										newWidth, newHeight,
										m_SwapChainDescription.Format,
										m_SwapChainDescription.Flags);
		if (FAILED(hr)) {
			while (m_SwapChain->Release());
			m_SwapChain = nullptr;
			return E_UNEXPECTED;
		}
			
		m_SwapChainDescription.Width = newWidth;
		m_SwapChainDescription.Height = newHeight;

		hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_Surface));
		if (FAILED(hr)) {
			while (m_SwapChain->Release());
			m_SwapChain = nullptr;
			return hr;
		}

		hr = parentD2DDeviceContext->CreateBitmapFromDxgiSurface(m_Surface, m_BitmapCanvasProps, &m_BitmapCanvas);
		if (FAILED(hr)) {
			while (m_Surface->Release());
			m_Surface = nullptr;
			while (m_SwapChain->Release());
			m_SwapChain = nullptr;
			return hr;
		}

		return hr;
	}
}