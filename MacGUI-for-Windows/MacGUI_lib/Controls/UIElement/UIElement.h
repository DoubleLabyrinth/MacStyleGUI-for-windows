#pragma once

#include "../Canvas.h"

namespace MDGUI::DrawingTools {

	class UIElement {
	private:
		BOOL Initialized;
	protected:
		CompositionSwapChain* m_UISwapChain;
		SurfaceCanvas* m_UICanvas;

		D2D1_SIZE_U m_UISize;
	public:
		UIElement();

		~UIElement();

		HRESULT Initialize(_In_ IDXGIDevice* srcDXGIDevice,
						   _In_ IDXGIFactory2* srcDXGIFactory,
						   _In_ ID2D1DeviceContext2* srcD2DDeviceContext,
						   _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc = nullptr,
						   _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps = nullptr);

		VOID Destroy();

		CompositionSwapChain* GetSwapChain();
		SurfaceCanvas* GetCanvas();


		virtual HRESULT OnPaint() = 0;
	};
}