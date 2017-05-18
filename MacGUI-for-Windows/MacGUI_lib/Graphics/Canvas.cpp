#include "Canvas.h"

namespace MacGUI::Graphics {

	CompositionSwapChain::CompositionSwapChain(_In_ UINT nWidth, _In_ UINT nHeight,
											   _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc /* = nullptr */) {

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
	}

	CompositionSwapChain::~CompositionSwapChain() {
		while (ReleaseSwapChain());
	}

	HRESULT CompositionSwapChain::CreateSwapChain() {
		if (m_SwapChain) return S_OK;
		if (MacGUI::Global::DXGIFactory == nullptr || MacGUI::Global::DXGIDevice == nullptr) return E_POINTER;

		return MacGUI::Global::DXGIFactory->CreateSwapChainForComposition(MacGUI::Global::DXGIDevice, &m_SwapChainDescription, nullptr, &m_SwapChain);
	}

	ULONG CompositionSwapChain::ReleaseSwapChain() {
		if (m_SwapChain) {
			ULONG newReferenceCount = m_SwapChain->Release();
			if (newReferenceCount == 0) m_SwapChain = nullptr;
			return newReferenceCount;
		}

		return 0;
	}

	HRESULT CompositionSwapChain::Resize(_In_ UINT newWidth, _In_ UINT newHeight) {
		if (m_SwapChain == nullptr) return E_FAIL;
		HRESULT hr = m_SwapChain->ResizeBuffers(m_SwapChainDescription.BufferCount,
												newWidth,
												newHeight,
												m_SwapChainDescription.Format,
												m_SwapChainDescription.Flags);
		if (SUCCEEDED(hr)) {
			m_SwapChainDescription.Width = newWidth;
			m_SwapChainDescription.Height = newHeight;
		}

		return hr;
	}

	IDXGISwapChain1* CompositionSwapChain::GetSwapChianInstance() {
		return m_SwapChain;
	}

	const DXGI_SWAP_CHAIN_DESC1& CompositionSwapChain::GetSwapChainDescription() const {
		return m_SwapChainDescription;
	}

	BOOL CompositionSwapChain::SetAlphaMode(_In_ DXGI_ALPHA_MODE newAlphaMode) {
		if (m_SwapChain) return FALSE;
		m_SwapChainDescription.AlphaMode = newAlphaMode;
		return TRUE;
	}

	BOOL CompositionSwapChain::SetBufferCount(_In_ UINT newBufferCount) {
		if (m_SwapChain) return FALSE;
		m_SwapChainDescription.BufferCount = newBufferCount;
		return TRUE;
	}

	BOOL CompositionSwapChain::SetBufferUsage(_In_ DXGI_USAGE newBufferUsage) {
		if (m_SwapChain) return FALSE;
		m_SwapChainDescription.BufferUsage = newBufferUsage;
		return TRUE;
	}

	BOOL CompositionSwapChain::SetFlags(_In_ DXGI_SWAP_CHAIN_FLAG newFlags) {
		if (m_SwapChain) return FALSE;
		m_SwapChainDescription.Flags = newFlags;
		return TRUE;
	}

	BOOL CompositionSwapChain::SetFormat(_In_ DXGI_FORMAT newFormat) {
		if (m_SwapChain) return FALSE;
		m_SwapChainDescription.Format = newFormat;
		return TRUE;
	}

	BOOL CompositionSwapChain::SetSampleDesc(_In_ UINT newSampleCount, _In_ UINT newSampleQuality) {
		if (m_SwapChain) return FALSE;
		m_SwapChainDescription.SampleDesc.Count = newSampleCount;
		m_SwapChainDescription.SampleDesc.Quality = newSampleQuality;
		return TRUE;
	}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	SurfaceCanvas::SurfaceCanvas(_In_ CompositionSwapChain* srcSwapChain,
								 _In_ ID2D1DeviceContext2* srcD2DDeviceContext,
								 _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps /* = nullptr */) {
		parentCompositionSwapChain = srcSwapChain;
		parentD2DDeviceContext = srcD2DDeviceContext;

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

	SurfaceCanvas::~SurfaceCanvas() {
		while (m_BitmapCanvas->Release());
		while (m_Surface->Release());
	}

	BOOL SurfaceCanvas::SetCanvasBitmapOptions(_In_ D2D1_BITMAP_OPTIONS newOptions) {
		if (m_BitmapCanvas) return FALSE;
		m_BitmapCanvasProps.bitmapOptions = newOptions;
		return TRUE;
	}

	BOOL SurfaceCanvas::SetCanvasColorContext(_In_ ID2D1ColorContext* newColorContext) {
		if (m_BitmapCanvas) return FALSE;
		m_BitmapCanvasProps.colorContext = newColorContext;
		return TRUE;
	}

	BOOL SurfaceCanvas::SetCanvasPixelFormat(D2D1_ALPHA_MODE newAlphaMode, DXGI_FORMAT newFormat) {
		if (m_BitmapCanvas) return FALSE;
		m_BitmapCanvasProps.pixelFormat.alphaMode = newAlphaMode;
		m_BitmapCanvasProps.pixelFormat.format = newFormat;
		return TRUE;
	}

	HRESULT SurfaceCanvas::ObtainSurface() {
		if (m_Surface) return S_OK;
		if (parentCompositionSwapChain == nullptr) return E_POINTER;
		if (parentCompositionSwapChain->GetSwapChianInstance() == nullptr) return E_POINTER;
		return parentCompositionSwapChain->GetSwapChianInstance()->GetBuffer(0, IID_PPV_ARGS(&m_Surface));
	}

	HRESULT SurfaceCanvas::CreateCanvas() {
		if (m_BitmapCanvas) return S_OK;
		if (m_Surface == nullptr || parentD2DDeviceContext == nullptr) return E_POINTER;
		return parentD2DDeviceContext->CreateBitmapFromDxgiSurface(m_Surface,
					     										   m_BitmapCanvasProps,
																   &m_BitmapCanvas);
	}

	ID2D1Bitmap1* SurfaceCanvas::GetCanvasInstance() {
		return m_BitmapCanvas;
	}

	ULONG SurfaceCanvas::ReleaseCanvas() {
		if (m_BitmapCanvas == nullptr) return 0;
		ULONG newReferenceCount = m_BitmapCanvas->Release();
		if (newReferenceCount == 0) m_BitmapCanvas = nullptr;
		return newReferenceCount;
	}

	ULONG SurfaceCanvas::ReleaseSurface() {
		if (m_Surface == nullptr) return 0;
		ULONG newReferenceCount = m_Surface->Release();
		if (newReferenceCount == 0) m_Surface = nullptr;
		return newReferenceCount;
	}

	HRESULT SurfaceCanvas::Resize(_In_ UINT newWidth, _In_ UINT newHeight) {
		while (ReleaseCanvas());
		while (ReleaseSurface());

		HRESULT hr = parentCompositionSwapChain->Resize(newWidth, newHeight);
		if (FAILED(hr)) return hr;
		
		hr = ObtainSurface();
		if (FAILED(hr)) return hr;

		hr = CreateCanvas();
		/*if (FAILED(hr))*/ return hr;
	}
}