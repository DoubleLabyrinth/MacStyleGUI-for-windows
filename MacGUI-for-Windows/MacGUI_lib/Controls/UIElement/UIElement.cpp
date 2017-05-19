#include "UIElement.h"

namespace MacGUI::Controls {

	UIElement::UIElement(_In_ UINT nWidth, _In_ UINT nHeight,
						 _In_ ID2D1DeviceContext2* srcD2DDeviceContext/* = nullptr*/,
						 _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc/* = nullptr*/,
						 _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps/* = nullptr*/) : Canvas(nWidth, nHeight, 
																								  srcD2DDeviceContext, 
																								  srcSwapChainDesc, 
																								  srcCanvasProps){

		Initialized = FALSE;

		m_Width = nWidth;
		m_Height = nHeight;

		OffsetX = 0.0f;
		OffsetY = 0.0f;

	}

	UINT UIElement::Width() const {
		return m_Width;
	}

	UINT UIElement::Height() const {
		return m_Height;
	}
}