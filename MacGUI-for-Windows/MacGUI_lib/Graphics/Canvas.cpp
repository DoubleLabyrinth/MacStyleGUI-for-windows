#include "Canvas.h"

#define MDGUI_RENDER_BUFFER_COUNT 2
#define MDGUI_SWAPCHAIN_SAMPLE_COUNT 1
#define MDGUI_SWAPCHAIN_SAMPLE_QUALITY 0

namespace MacGUI::Graphics {

	CompositionSwapChain::CompositionSwapChain(_In_ IDXGIDevice* srcDXGIDevice,
											   _In_ IDXGIFactory2* srcDXGIFactory,
											   _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc /* = nullptr */) {
		parentDXGIDevice = srcDXGIDevice;
		parentDXGIFactory = srcDXGIFactory;

		if (srcSwapChainDesc == nullptr) {
			m_SwapChainDescription.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
			m_SwapChainDescription.BufferCount = MDGUI_RENDER_BUFFER_COUNT;
			m_SwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			m_SwapChainDescription.Flags = 0;
			m_SwapChainDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			m_SwapChainDescription.Height = 0;
			m_SwapChainDescription.SampleDesc.Count = MDGUI_SWAPCHAIN_SAMPLE_COUNT;
			m_SwapChainDescription.SampleDesc.Quality = MDGUI_SWAPCHAIN_SAMPLE_QUALITY;
			m_SwapChainDescription.Scaling = DXGI_SCALING_STRETCH;   // it must be this
			m_SwapChainDescription.Stereo = FALSE;
			m_SwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;  // it must be this;
			m_SwapChainDescription.Width = 0;
		} else {
			m_SwapChainDescription = *srcSwapChainDesc;
		}
	}

	CompositionSwapChain::~CompositionSwapChain() {
		while (ReleaseSwapChain());
	}

	HRESULT CompositionSwapChain::CreateSwapChain(_In_opt_ IDXGIOutput* pRestrictToOutput /* = nullptr */) {
		if (m_SwapChain) return S_OK;
		if (parentDXGIFactory == nullptr) return E_POINTER;
		return parentDXGIFactory->CreateSwapChainForComposition(parentDXGIDevice, &m_SwapChainDescription, pRestrictToOutput, &m_SwapChain);
	}

	ULONG CompositionSwapChain::ReleaseSwapChain() {
		if (m_SwapChain) {
			ULONG newReferenceCount = m_SwapChain->Release();
			if (newReferenceCount == 0) m_SwapChain = nullptr;
			return newReferenceCount;
		}
		return 0;
	}

	BOOL CompositionSwapChain::ChangeDXGIFactory(IDXGIFactory2* newDXGIFactory) {
		if (newDXGIFactory == nullptr) return FALSE;
		if (m_SwapChain) return FALSE;

		parentDXGIFactory = newDXGIFactory;

		return TRUE;
	}

	BOOL CompositionSwapChain::ChangeDXGIDevice(IDXGIDevice* newDXGIDevice) {
		if (newDXGIDevice == nullptr) return FALSE;
		if (m_SwapChain) return FALSE;

		parentDXGIDevice = newDXGIDevice;

		return TRUE;
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

	BOOL CompositionSwapChain::SetStereo(_In_ BOOL newStereo) {
		if (m_SwapChain) return FALSE;
		m_SwapChainDescription.Stereo = newStereo;
		return TRUE;
	}

	BOOL CompositionSwapChain::SetSize(_In_ UINT newWidth, _In_ UINT newHeight) {
		if (m_SwapChain) return FALSE;
		m_SwapChainDescription.Width = newWidth;
		m_SwapChainDescription.Height = newHeight;
		return TRUE;
	}

	HRESULT CompositionSwapChain::ResizeAllBuffers(_In_ UINT newWidth, _In_ UINT newHeight) {
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SurfaceCanvas::SurfaceCanvas(_In_ CompositionSwapChain* srcSwapChain,
								 _In_ ID2D1DeviceContext2* srcD2DDeviceContext,
								 _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps /* = nullptr */) {
		parentSwapChain = srcSwapChain;
		parentD2DDeviceContext = srcD2DDeviceContext;

		m_Surface = nullptr;
		m_BitmapCanvas = nullptr;

		if (srcCanvasProps == nullptr) {
			m_BitmapCanvasProps.bitmapOptions = D2D1_BITMAP_OPTIONS_CANNOT_DRAW | D2D1_BITMAP_OPTIONS_TARGET;
			m_BitmapCanvasProps.colorContext = nullptr;
			m_BitmapCanvasProps.dpiX = 0.0f;
			m_BitmapCanvasProps.dpiY = 0.0f;
			m_BitmapCanvasProps.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
			m_BitmapCanvasProps.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
		} else {
			m_BitmapCanvasProps = *srcCanvasProps;
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

	BOOL SurfaceCanvas::SetCanvasDpi(_In_ FLOAT newDpiX, _In_ FLOAT newDpiY) {
		if (m_BitmapCanvas) return FALSE;
		m_BitmapCanvasProps.dpiX = newDpiX;
		m_BitmapCanvasProps.dpiY = newDpiY;
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
		if (parentSwapChain == nullptr) return E_POINTER;
		if (parentSwapChain->GetSwapChianInstance() == nullptr) return E_POINTER;
		return parentSwapChain->GetSwapChianInstance()->GetBuffer(0, IID_PPV_ARGS(&m_Surface));
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

	HRESULT SurfaceCanvas::ResizeCanvas(UINT newWidth, UINT newHeight) {
		while (ReleaseCanvas());
		while (ReleaseSurface());

		HRESULT hr = parentSwapChain->ResizeAllBuffers(newWidth, newHeight);
		if (FAILED(hr)) return hr;
		
		hr = ObtainSurface();
		if (FAILED(hr)) return hr;

		hr = CreateCanvas();
		return hr;
	}
}