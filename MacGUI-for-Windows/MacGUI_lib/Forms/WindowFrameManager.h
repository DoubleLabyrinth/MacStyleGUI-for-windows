#pragma once
#pragma comment(lib, "d2d1.lib")

#include <windows.h>
#include <d2d1.h>

namespace MacGUI::Forms {

	class WindowFrameManager {
	private:
		ID2D1Factory* parentD2D_Factory;

		HWND AssociatedHwnd;
		RECT OldWindowRect;
		FLOAT Offset;
		FLOAT DetectWidth;

		ID2D1PathGeometry* LeftUpCornerArea;
		ID2D1PathGeometry* RightUpCornerArea;
		ID2D1PathGeometry* LeftDownCornerArea;
		ID2D1PathGeometry* RightDownCornerArea;

		ID2D1PathGeometry* LeftRectArea;
		ID2D1PathGeometry* TopRectArea;
		ID2D1PathGeometry* RightRectArea;
		ID2D1PathGeometry* BottomRectArea;

		WindowFrameManager(const WindowFrameManager&) = delete;
		WindowFrameManager& operator=(const WindowFrameManager&) = delete;
	public:
		WindowFrameManager(_In_ ID2D1Factory* pD2DFactory);
		VOID SetParentFactory(_In_ ID2D1Factory* pD2DFactory);

		HRESULT CreateArea();
		
		VOID BindHwnd(HWND srcHwnd);
		HRESULT UpdateArea();

		VOID DestroyAllAreas();

		
	};
}