#include "FrameManager.h"

#define SafeRelease(x) {    \
	if(x != nullptr) {		\
		x->Release();		\
		x = nullptr;		\
	}						\
}

namespace MacGUI::Forms::Tools {

	FrameManager::FrameManager(_In_ ID2D1Factory* pD2DFactory) {
		AssociatedHwnd = NULL;
		CornerRadius = 5.0f;

		LeftUpCornerArea = nullptr;
		RightUpCornerArea = nullptr;
		LeftDownCornerArea = nullptr;
		RightDownCornerArea = nullptr;

		LeftRectArea = nullptr;
		TopRectArea = nullptr;
		RightRectArea = nullptr;
		BottomRectArea = nullptr;

		parentD2D_Factory = pD2DFactory;
		if (parentD2D_Factory == nullptr) return;
	}

	FrameManager::~FrameManager() {
		DestroyAllAreas();
	}

	VOID FrameManager::SetParentFactory(_In_ ID2D1Factory* pD2DFactory) {
		if (pD2DFactory == parentD2D_Factory) return;
		DestroyAllAreas();
		parentD2D_Factory = pD2DFactory;
	}

	HRESULT FrameManager::CreateArea() {
		HRESULT hr = S_OK;
		hr = parentD2D_Factory->CreatePathGeometry(&LeftUpCornerArea);
		if (FAILED(hr)) {
			DestroyAllAreas();
			return hr;
		}

		hr = parentD2D_Factory->CreatePathGeometry(&RightUpCornerArea);
		if (FAILED(hr)) {
			DestroyAllAreas();
			return hr;
		}

		hr = parentD2D_Factory->CreatePathGeometry(&LeftDownCornerArea);
		if (FAILED(hr)) {
			DestroyAllAreas();
			return hr;
		}

		hr = parentD2D_Factory->CreatePathGeometry(&RightDownCornerArea);
		if (FAILED(hr)) {
			DestroyAllAreas();
			return hr;
		}

		hr = parentD2D_Factory->CreatePathGeometry(&LeftRectArea);
		if (FAILED(hr)) {
			DestroyAllAreas();
			return hr;
		}

		hr = parentD2D_Factory->CreatePathGeometry(&TopRectArea);
		if (FAILED(hr)) {
			DestroyAllAreas();
			return hr;
		}

		hr = parentD2D_Factory->CreatePathGeometry(&RightRectArea);
		if (FAILED(hr)) {
			DestroyAllAreas();
			return hr;
		}

		hr = parentD2D_Factory->CreatePathGeometry(&BottomRectArea);
		if (FAILED(hr)) {
			DestroyAllAreas();
			return hr;
		}

		return hr;
	}

	HRESULT FrameManager::UpdateLeftUpCorner(ID2D1PathGeometry* srcDetectArea) {
		if (srcDetectArea == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		ID2D1RectangleGeometry* ClipRect = nullptr;
		ID2D1GeometrySink* sink = nullptr;

		hr = parentD2D_Factory->CreateRectangleGeometry(D2D1::RectF(
			0.0f,
			0.0f,
			5.0f + CornerRadius,
			5.0f + CornerRadius), &ClipRect);
		if (FAILED(hr)) return hr;

		hr = LeftUpCornerArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(ClipRect);
			return hr;
		}

		hr = srcDetectArea->CombineWithGeometry(ClipRect,
											 D2D1_COMBINE_MODE_INTERSECT,
											 nullptr,
											 sink);
		if (FAILED(hr)) {
			sink->Close();
			SafeRelease(sink);
			SafeRelease(ClipRect);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(ClipRect);

		return hr;
	}

	HRESULT FrameManager::UpdateRightUpCorner(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect) {
		if (srcDetectArea == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		ID2D1RectangleGeometry* ClipRect = nullptr;
		ID2D1GeometrySink* sink = nullptr;

		hr = parentD2D_Factory->CreateRectangleGeometry(D2D1::RectF(
			CurrentRect.right - CurrentRect.left - 5.0f - CornerRadius,
			0.0f,
			CurrentRect.right - CurrentRect.left,
			5.0f + CornerRadius), &ClipRect);
		if (FAILED(hr)) return hr;

		hr = RightUpCornerArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(ClipRect);
			return hr;
		}

		hr = srcDetectArea->CombineWithGeometry(ClipRect,
												D2D1_COMBINE_MODE_INTERSECT,
												nullptr,
												sink);
		if (FAILED(hr)) {
			sink->Close();
			SafeRelease(sink);
			SafeRelease(ClipRect);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(ClipRect);

		return hr;
	}

	HRESULT FrameManager::UpdateLeftDownCorner(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect) {
		if (srcDetectArea == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		ID2D1RectangleGeometry* ClipRect = nullptr;
		ID2D1GeometrySink* sink = nullptr;

		hr = parentD2D_Factory->CreateRectangleGeometry(D2D1::RectF(
			0.0f,
			CurrentRect.bottom - CurrentRect.top - 5.0f - CornerRadius,
			5.0f + CornerRadius,
			CurrentRect.bottom - CurrentRect.top), &ClipRect);
		if (FAILED(hr)) return hr;

		hr = LeftDownCornerArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(ClipRect);
			return hr;
		}

		hr = srcDetectArea->CombineWithGeometry(ClipRect,
												D2D1_COMBINE_MODE_INTERSECT,
												nullptr,
												sink);
		if (FAILED(hr)) {
			sink->Close();
			SafeRelease(sink);
			SafeRelease(ClipRect);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(ClipRect);

		return hr;
	}

	HRESULT FrameManager::UpdateRightDownCorner(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect) {
		if (srcDetectArea == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		ID2D1RectangleGeometry* ClipRect = nullptr;
		ID2D1GeometrySink* sink = nullptr;

		hr = parentD2D_Factory->CreateRectangleGeometry(D2D1::RectF(
			CurrentRect.right - CurrentRect.left - 5.0f - CornerRadius,
			CurrentRect.bottom - CurrentRect.top - 5.0f - CornerRadius,
			CurrentRect.right - CurrentRect.left,
			CurrentRect.bottom - CurrentRect.top), &ClipRect);
		if (FAILED(hr)) return hr;

		hr = RightDownCornerArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(ClipRect);
			return hr;
		}

		hr = srcDetectArea->CombineWithGeometry(ClipRect,
												D2D1_COMBINE_MODE_INTERSECT,
												nullptr,
												sink);
		if (FAILED(hr)) {
			sink->Close();
			SafeRelease(sink);
			SafeRelease(ClipRect);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(ClipRect);

		return hr;
	}

	HRESULT FrameManager::UpdateLeftRect(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect) {
		if (srcDetectArea == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		ID2D1RectangleGeometry* ClipRect = nullptr;
		ID2D1GeometrySink* sink = nullptr;

		hr = parentD2D_Factory->CreateRectangleGeometry(D2D1::RectF(
			0.0f,
			5.0f + CornerRadius,
			5.0f,
			CurrentRect.bottom - CurrentRect.top - 5.0 - CornerRadius), &ClipRect);
		if (FAILED(hr)) return hr;

		hr = LeftRectArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(ClipRect);
			return hr;
		}

		hr = srcDetectArea->CombineWithGeometry(ClipRect,
												D2D1_COMBINE_MODE_INTERSECT,
												nullptr,
												sink);
		if (FAILED(hr)) {
			sink->Close();
			SafeRelease(sink);
			SafeRelease(ClipRect);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(ClipRect);

		return hr;
	}

	HRESULT FrameManager::UpdateTopRect(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect) {
		if (srcDetectArea == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		ID2D1RectangleGeometry* ClipRect = nullptr;
		ID2D1GeometrySink* sink = nullptr;

		hr = parentD2D_Factory->CreateRectangleGeometry(D2D1::RectF(
			5.0f + CornerRadius,
			0.0f,
			CurrentRect.right - CurrentRect.left - 5.0f - CornerRadius,
			5.0f), &ClipRect);
		if (FAILED(hr)) return hr;

		hr = TopRectArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(ClipRect);
			return hr;
		}

		hr = srcDetectArea->CombineWithGeometry(ClipRect,
												D2D1_COMBINE_MODE_INTERSECT,
												nullptr,
												sink);
		if (FAILED(hr)) {
			sink->Close();
			SafeRelease(sink);
			SafeRelease(ClipRect);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(ClipRect);

		return hr;
	}

	HRESULT FrameManager::UpdateRightRect(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect) {
		if (srcDetectArea == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		ID2D1RectangleGeometry* ClipRect = nullptr;
		ID2D1GeometrySink* sink = nullptr;

		hr = parentD2D_Factory->CreateRectangleGeometry(D2D1::RectF(
			CurrentRect.right - CurrentRect.left - 5.0f,
			5.0f + CornerRadius,
			CurrentRect.right - CurrentRect.left,
			CurrentRect.bottom - CurrentRect.top - 5.0f - CornerRadius), &ClipRect);
		if (FAILED(hr)) return hr;

		hr = RightRectArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(ClipRect);
			return hr;
		}

		hr = srcDetectArea->CombineWithGeometry(ClipRect,
												D2D1_COMBINE_MODE_INTERSECT,
												nullptr,
												sink);
		if (FAILED(hr)) {
			sink->Close();
			SafeRelease(sink);
			SafeRelease(ClipRect);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(ClipRect);

		return hr;
	}

	HRESULT FrameManager::UpdateBottomRect(ID2D1PathGeometry* srcDetectArea, const RECT& CurrentRect) {
		if (srcDetectArea == nullptr) return E_POINTER;

		HRESULT hr = S_OK;
		ID2D1RectangleGeometry* ClipRect = nullptr;
		ID2D1GeometrySink* sink = nullptr;

		hr = parentD2D_Factory->CreateRectangleGeometry(D2D1::RectF(
			5.0f + CornerRadius,
			CurrentRect.bottom - CurrentRect.top - 5.0f,
			CurrentRect.right - CurrentRect.left - 5.0f - CornerRadius,
			CurrentRect.bottom - CurrentRect.top), &ClipRect);
		if (FAILED(hr)) return hr;

		hr = BottomRectArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(ClipRect);
			return hr;
		}

		hr = srcDetectArea->CombineWithGeometry(ClipRect,
												D2D1_COMBINE_MODE_INTERSECT,
												nullptr,
												sink);
		if (FAILED(hr)) {
			sink->Close();
			SafeRelease(sink);
			SafeRelease(ClipRect);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(ClipRect);

		return hr;
	}

	HRESULT FrameManager::UpdateArea() {
		if (AssociatedHwnd == NULL) return E_INVALIDARG;
		if (parentD2D_Factory == nullptr) return E_POINTER;

		DestroyAllAreas();

		HRESULT hr = S_OK;
		hr = CreateArea();
		if (FAILED(hr)) return hr;

		ID2D1RoundedRectangleGeometry* outerBorder = nullptr;
		ID2D1RoundedRectangleGeometry* innerBorder = nullptr;

		RECT CurrentRect;
		if (GetWindowRect(AssociatedHwnd, &CurrentRect) == FALSE) return E_FAIL;


		//-------------------Begin update area
		//-------------------------------------------------------Create outBorder
		hr = parentD2D_Factory->CreateRoundedRectangleGeometry(D2D1::RoundedRect(D2D1::RectF(
			0.0f,
			0.0f,
			CurrentRect.right - CurrentRect.left,
			CurrentRect.bottom - CurrentRect.top),
			CornerRadius,
			CornerRadius), &outerBorder);
		if (FAILED(hr)) return hr;


		//-----------------------------------------------------Create innerBorder
		hr = parentD2D_Factory->CreateRoundedRectangleGeometry(D2D1::RoundedRect(D2D1::RectF(
			5.0f,
			5.0f,
			CurrentRect.right - CurrentRect.left - 5.0f,
			CurrentRect.bottom - CurrentRect.top - 5.0f),
			CornerRadius,
			CornerRadius), &innerBorder);
		if (FAILED(hr)) {
			SafeRelease(outerBorder);
			return hr;
		}

		//---------------------------------------------Create total detect area
		ID2D1PathGeometry* DetectArea = nullptr;
		hr = parentD2D_Factory->CreatePathGeometry(&DetectArea);
		if (FAILED(hr)) {
			SafeRelease(outerBorder);
			SafeRelease(innerBorder);
			return hr;
		}

		ID2D1GeometrySink* sink = nullptr;
		hr = DetectArea->Open(&sink);
		if (FAILED(hr)) {
			SafeRelease(outerBorder);
			SafeRelease(innerBorder);
			SafeRelease(DetectArea);
			return hr;
		}

		hr = outerBorder->CombineWithGeometry(innerBorder,
											  D2D1_COMBINE_MODE_EXCLUDE,
											  nullptr, sink);
		if (FAILED(hr)) {
			SafeRelease(outerBorder);
			SafeRelease(innerBorder);
			SafeRelease(DetectArea);
			sink->Close();
			SafeRelease(sink);
			return hr;
		}
		sink->Close();
		SafeRelease(sink);
		SafeRelease(innerBorder);
		SafeRelease(outerBorder);

		//-------------------------------------------------------------------------------------Start to divide area

		hr = UpdateLeftUpCorner(DetectArea);
		if (FAILED(hr)) {
			SafeRelease(DetectArea);
			return hr;
		}

		hr = UpdateRightUpCorner(DetectArea, CurrentRect);
		if (FAILED(hr)) {
			SafeRelease(DetectArea);
			return hr;
		}

		hr = UpdateLeftDownCorner(DetectArea, CurrentRect);
		if (FAILED(hr)) {
			SafeRelease(DetectArea);
			return hr;
		}

		hr = UpdateRightDownCorner(DetectArea, CurrentRect);
		if (FAILED(hr)) {
			SafeRelease(DetectArea);
			return hr;
		}

		hr = UpdateLeftRect(DetectArea, CurrentRect);
		if (FAILED(hr)) {
			SafeRelease(DetectArea);
			return hr;
		}

		hr = UpdateTopRect(DetectArea, CurrentRect);
		if (FAILED(hr)) {
			SafeRelease(DetectArea);
			return hr;
		}

		hr = UpdateRightRect(DetectArea, CurrentRect);
		if (FAILED(hr)) {
			SafeRelease(DetectArea);
			return hr;
		}

		hr = UpdateBottomRect(DetectArea, CurrentRect);
		if (FAILED(hr)) {
			SafeRelease(DetectArea);
			return hr;
		}

		SafeRelease(DetectArea);
		return hr;
	}

	VOID FrameManager::DestroyAllAreas() {
		SafeRelease(LeftUpCornerArea);
		SafeRelease(RightUpCornerArea);
		SafeRelease(LeftDownCornerArea);
		SafeRelease(RightDownCornerArea);

		SafeRelease(LeftRectArea);
		SafeRelease(TopRectArea);
		SafeRelease(RightRectArea);
		SafeRelease(BottomRectArea);
	}

	VOID FrameManager::BindHwnd(HWND srcHwnd) {
		if (srcHwnd == AssociatedHwnd) return;
		DestroyAllAreas();
		AssociatedHwnd = srcHwnd;
	}

	VOID FrameManager::SetCornerRadius(FLOAT srcRadius, BOOL Update) {
		CornerRadius = srcRadius < 0.0f ? 0.0f : srcRadius;
		if(Update) UpdateArea();
	}

	FLOAT FrameManager::GetCornerRadius() const {
		return CornerRadius;
	}

	BYTE FrameManager::GetHitArea(const D2D1_POINT_2F& CursorPos) {
		if (LeftUpCornerArea == nullptr ||
			RightUpCornerArea == nullptr ||
			LeftDownCornerArea == nullptr ||
			RightDownCornerArea == nullptr ||
			LeftRectArea == nullptr ||
			TopRectArea == nullptr ||
			RightRectArea == nullptr ||
			BottomRectArea == nullptr) return 0;

		BOOL contain = FALSE;

		RightDownCornerArea->FillContainsPoint(CursorPos, nullptr, &contain);
		if (contain) return WINDOW_FRAME_MANAGER_RIGHT_DOWN_CORNER;

		RightRectArea->FillContainsPoint(CursorPos, nullptr, &contain);
		if (contain) return WINDOW_FRAME_MANAGER_RIGHT_RECT;

		BottomRectArea->FillContainsPoint(CursorPos, nullptr, &contain);
		if (contain) return WINDOW_FRAME_MANAGER_BOTTOM_RECT;

		RightUpCornerArea->FillContainsPoint(CursorPos, nullptr, &contain);
		if (contain) return WINDOW_FRAME_MANAGER_RIGHT_UP_CORNER;

		LeftDownCornerArea->FillContainsPoint(CursorPos, nullptr, &contain);
		if (contain) return WINDOW_FRAME_MANAGER_LEFT_DOWN_CORNER;

		LeftRectArea->FillContainsPoint(CursorPos, nullptr, &contain);
		if (contain) return WINDOW_FRAME_MANAGER_LEFT_RECT;

		TopRectArea->FillContainsPoint(CursorPos, nullptr, &contain);
		if (contain) return WINDOW_FRAME_MANAGER_TOP_RECT;

		LeftUpCornerArea->FillContainsPoint(CursorPos, nullptr, &contain);
		if (contain) return WINDOW_FRAME_MANAGER_LEFT_UP_CORNER;

		return 0;
	}

	LPCTSTR FrameManager::GetCursorID(const D2D1_POINT_2F& CursorPos) {
		BYTE HitArea = GetHitArea(CursorPos);

		switch (HitArea) {
			case WINDOW_FRAME_MANAGER_LEFT_UP_CORNER:
			case WINDOW_FRAME_MANAGER_RIGHT_DOWN_CORNER:
				return IDC_SIZENWSE;
			case WINDOW_FRAME_MANAGER_TOP_RECT:
			case WINDOW_FRAME_MANAGER_BOTTOM_RECT:
				return IDC_SIZENS;
			case WINDOW_FRAME_MANAGER_RIGHT_UP_CORNER:
			case WINDOW_FRAME_MANAGER_LEFT_DOWN_CORNER:
				return IDC_SIZENESW;
			case WINDOW_FRAME_MANAGER_LEFT_RECT:
			case WINDOW_FRAME_MANAGER_RIGHT_RECT:
				return IDC_SIZEWE;
			default:
				return IDC_ARROW;
		}
	}
}