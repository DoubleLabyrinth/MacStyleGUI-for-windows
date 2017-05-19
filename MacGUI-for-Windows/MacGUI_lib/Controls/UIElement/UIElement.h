#pragma once
#include "../../Graphics/Canvas.h"

namespace MacGUI::Controls {

	class UIElement : public MacGUI::Graphics::Canvas {
	private:
		BOOL Initialized;
	protected:
		UINT m_Width;
		UINT m_Height;
	public:
		FLOAT OffsetX;
		FLOAT OffsetY;

		UIElement(_In_ UINT nWidth, _In_ UINT nHeight,
				  _In_opt_ ID2D1DeviceContext2* srcD2DDeviceContext = nullptr,
				  _In_opt_ DXGI_SWAP_CHAIN_DESC1* srcSwapChainDesc = nullptr,
				  _In_opt_ D2D1_BITMAP_PROPERTIES1* srcCanvasProps = nullptr);

		UINT Width() const;
		UINT Height() const;
		
		virtual HRESULT OnPaint() = 0;
	};
}