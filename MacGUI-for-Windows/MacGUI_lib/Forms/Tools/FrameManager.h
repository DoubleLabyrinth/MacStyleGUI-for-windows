#pragma once
#pragma comment(lib, "d2d1.lib")

#include <windows.h>
#include <d2d1.h>

#define WINDOW_FRAME_MANAGER_LEFT_UP_CORNER ((unsigned char)1)
#define WINDOW_FRAME_MANAGER_RIGHT_UP_CORNER ((unsigned char)2)
#define WINDOW_FRAME_MANAGER_LEFT_DOWN_CORNER ((unsigned char)4)
#define WINDOW_FRAME_MANAGER_RIGHT_DOWN_CORNER ((unsigned char)8)
#define WINDOW_FRAME_MANAGER_LEFT_RECT ((unsigned char)16)
#define WINDOW_FRAME_MANAGER_TOP_RECT ((unsigned char)32)
#define WINDOW_FRAME_MANAGER_RIGHT_RECT ((unsigned char)64)
#define WINDOW_FRAME_MANAGER_BOTTOM_RECT ((unsigned char)128)

namespace MacGUI::Forms::Tools {

	class FrameManager {
	private:
		ID2D1Factory* parentD2D_Factory;

		HWND AssociatedHwnd;
		FLOAT CornerRadius;

		ID2D1PathGeometry* LeftUpCornerArea;
		ID2D1PathGeometry* RightUpCornerArea;
		ID2D1PathGeometry* LeftDownCornerArea;
		ID2D1PathGeometry* RightDownCornerArea;

		ID2D1PathGeometry* LeftRectArea;
		ID2D1PathGeometry* TopRectArea;
		ID2D1PathGeometry* RightRectArea;
		ID2D1PathGeometry* BottomRectArea;

		FrameManager(const FrameManager&) = delete;
		FrameManager& operator=(const FrameManager&) = delete;

		HRESULT UpdateLeftUpCorner(ID2D1PathGeometry* srcDetectArea);
		HRESULT UpdateRightUpCorner(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect);
		HRESULT UpdateLeftDownCorner(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect);
		HRESULT UpdateRightDownCorner(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect);
		HRESULT UpdateLeftRect(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect);
		HRESULT UpdateTopRect(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect);
		HRESULT UpdateRightRect(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect);
		HRESULT UpdateBottomRect(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect);

		VOID DestroyAllAreas();
		HRESULT CreateArea();
	public:
		FrameManager(_In_ ID2D1Factory* pD2DFactory);
		~FrameManager();
		VOID SetParentFactory(_In_ ID2D1Factory* pD2DFactory);

		HRESULT UpdateArea();
		
		VOID BindHwnd(HWND srcHwnd);

		VOID SetCornerRadius(FLOAT srcRadiusm, BOOL Update);
		FLOAT GetCornerRadius() const;
		
		BYTE GetHitArea(const D2D1_POINT_2F& CursorPos);
		LPCTSTR GetCursorID(const D2D1_POINT_2F& CursorPos);
	};
}