#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d2d1.lib")

#include <dxgi1_5.h>
#include <d2d1_3.h>

namespace MacGUI::Graphics {

	class CompositionSwapChain {
	private:
		CompositionSwapChain(const CompositionSwapChain&) = delete;
		CompositionSwapChain& operator=(const CompositionSwapChain&) = delete;
	protected:
		IDXGIFactory2* parentDXGIFactory;
		IDXGIDevice* parentDXGIDevice;

		IDXGISwapChain1* m_SwapChain;
		DXGI_SWAP_CHAIN_DESC1 m_SwapChainDescription;
	public:
		CompositionSwapChain(_In_ IDXGIDevice* srcDXGIDevice,
							 _In_ IDXGIFactory2* srcDXGIFactory,
							 _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc = nullptr);

		~CompositionSwapChain();

		HRESULT CreateSwapChain(_In_opt_ IDXGIOutput* pRestrictToOutput = nullptr);
		ULONG ReleaseSwapChain();

		// Setter.
		// But only available when IDXGISwapChain1 is not created or destroyed, in other words, when m_SwapChain is a null pointer.
		BOOL SetAlphaMode(_In_ DXGI_ALPHA_MODE newAlphaMode);
		BOOL SetBufferCount(_In_ UINT newBufferCount);
		BOOL SetBufferUsage(_In_ DXGI_USAGE newBufferUsage);
		BOOL SetFlags(_In_ DXGI_SWAP_CHAIN_FLAG newFlags);
		BOOL SetFormat(_In_ DXGI_FORMAT newFormat);
		BOOL SetSampleDesc(_In_ UINT newSampleCount, _In_ UINT newSampleQuality);
		BOOL SetStereo(_In_ BOOL newStereo);
		BOOL SetSize(_In_ UINT newWidth, _In_ UINT newHeight);
		BOOL ChangeDXGIFactory(_In_ IDXGIFactory2* newDXGIFactory);
		BOOL ChangeDXGIDevice(_In_ IDXGIDevice* newDXGIDevice);

		HRESULT ResizeAllBuffers(_In_ UINT newWidth, _In_ UINT newHeight);

		IDXGISwapChain1* GetSwapChianInstance();
		const DXGI_SWAP_CHAIN_DESC1& GetSwapChainDescription() const;
	};

	class SurfaceCanvas {
	private:
		SurfaceCanvas(const SurfaceCanvas&) = delete;
		SurfaceCanvas& operator=(const SurfaceCanvas&) = delete;

		CompositionSwapChain* parentSwapChain;
		ID2D1DeviceContext2* parentD2DDeviceContext;

		IDXGISurface2* m_Surface;
		ID2D1Bitmap1* m_BitmapCanvas;
		D2D1_BITMAP_PROPERTIES1 m_BitmapCanvasProps;
	public:
		SurfaceCanvas(_In_ CompositionSwapChain* srcSwapChain,
					  _In_ ID2D1DeviceContext2* srcD2DDeviceContext,
					  _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps = nullptr);

		~SurfaceCanvas();

		BOOL SetCanvasBitmapOptions(_In_ D2D1_BITMAP_OPTIONS newOptions);
		BOOL SetCanvasColorContext(_In_ ID2D1ColorContext* newColorContext);
		BOOL SetCanvasDpi(_In_ FLOAT newDpiX, _In_ FLOAT newDpiY);
		BOOL SetCanvasPixelFormat(D2D1_ALPHA_MODE newAlphaMode, DXGI_FORMAT newFormat);

		HRESULT ObtainSurface();
		HRESULT CreateCanvas();
		ID2D1Bitmap1* GetCanvasInstance();
		ULONG ReleaseCanvas();
		ULONG ReleaseSurface();

		HRESULT ResizeCanvas(UINT newWidth, UINT newHeight);
	};
	
}
