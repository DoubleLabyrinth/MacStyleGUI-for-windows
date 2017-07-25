#pragma once
#include "../Global.h"

namespace MacStyleGUI::Graphics {

	class Canvas {
	private:
		Canvas(const Canvas&) = delete;
		Canvas& operator=(const Canvas&) = delete;
	protected:
		UINT m_CanvasWidth;
		UINT m_CanvasHeight;

		Microsoft::WRL::ComPtr<IDCompositionVirtualSurface> m_VirtualSurcace;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDCompositionVisual2> m_Visual;
	public:
		Canvas(_In_ UINT init_Width, _In_ UINT init_Height);
		
		UINT GetCanvasWidth() CONST;
		UINT GetCanvasHeight() CONST;
		ID2D1DeviceContext* GetDeviceContext() CONST;
		IDCompositionVisual2* GetVisual() CONST;

		HRESULT BeginDraw(CONST RECT* updateRect, POINT* out_Offset);
		HRESULT SuspendDraw();
		HRESULT ResumeDraw();
		HRESULT EndDraw();

		HRESULT Trim(const RECT *rectangles, UINT count);
		HRESULT Scoll(_In_opt_ const RECT *scrollRect,
					  _In_opt_ const RECT *clipRect,
					  _In_ int offsetX,
					  _In_ int offsetY);

		HRESULT Resize(_In_ UINT newWidth, _In_ UINT newHeight);
	};

}
