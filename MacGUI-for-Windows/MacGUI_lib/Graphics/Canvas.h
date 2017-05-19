#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d2d1.lib")

#include <dxgi1_5.h>
#include <d2d1_3.h>

#include "../Global.h"

namespace MacGUI::Graphics {

	class Canvas {
	private:
		Canvas(const Canvas&) = delete;
		Canvas& operator=(const Canvas&) = delete;
	protected:
		ID2D1DeviceContext2* parentD2DDeviceContext;

		IDXGISwapChain1* m_SwapChain;
		IDXGISurface2* m_Surface;
		ID2D1Bitmap1* m_BitmapCanvas;

		DXGI_SWAP_CHAIN_DESC1 m_SwapChainDescription;
		D2D1_BITMAP_PROPERTIES1 m_BitmapCanvasProps;
	public:
		Canvas(_In_ UINT nWidth, _In_ UINT nHeight,
			   _In_ ID2D1DeviceContext2* srcD2DDeviceContext,
			   _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc = nullptr,
			   _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps = nullptr);

		~Canvas();

		HRESULT ChangeD2DDeviceContext(_In_ ID2D1DeviceContext2* newD2DDeviceContext);
		const DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc() const;
		HRESULT ChangeSwapChainDesc(_In_ const DXGI_SWAP_CHAIN_DESC1& newDesc, _In_ BOOL reCreateCanvas);
		const D2D1_BITMAP_PROPERTIES1 GetCanvasProps() const;
		HRESULT ChangeCanvasProps(_In_ const D2D1_BITMAP_PROPERTIES1& newProps, _In_ BOOL reCreateCanvas);

		HRESULT CreateCanvas();
		VOID DisposeCanvas();

		IDXGISwapChain1* GetSwapChain();
		IDXGISurface2* GetSurface();
		ID2D1Bitmap1* GetCanvas();

		HRESULT Resize(_In_ UINT newWidth, _In_ UINT newHeight);
	};

}
