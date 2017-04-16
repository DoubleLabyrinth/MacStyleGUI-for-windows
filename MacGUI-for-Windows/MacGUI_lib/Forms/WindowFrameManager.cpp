#include "WindowFrameManager.h"

namespace MacGUI::Forms {

	WindowFrameManager::WindowFrameManager(_In_ ID2D1Factory* pD2DFactory) {
		AssociatedHwnd = NULL;
		OldWindowRect = { };
		Offset = 0.0f;
		DetectWidth = 0.0f;

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

		if (FAILED(CreateArea())) DestroyAllAreas();
	}

	VOID WindowFrameManager::SetParentFactory(_In_ ID2D1Factory* pD2DFactory) {
		if (pD2DFactory == parentD2D_Factory) return;
		DestroyAllAreas();
		parentD2D_Factory = pD2DFactory;
	}

	HRESULT WindowFrameManager::CreateArea() {
		HRESULT hr = S_OK;
		hr = parentD2D_Factory->CreatePathGeometry(&LeftUpCornerArea);
		if (FAILED(hr)) return hr;

		hr = parentD2D_Factory->CreatePathGeometry(&RightUpCornerArea);
		if (FAILED(hr)) return hr;

		hr = parentD2D_Factory->CreatePathGeometry(&LeftDownCornerArea);
		if (FAILED(hr)) return hr;

		hr = parentD2D_Factory->CreatePathGeometry(&RightDownCornerArea);
		if (FAILED(hr)) return hr;

		hr = parentD2D_Factory->CreatePathGeometry(&LeftRectArea);
		if (FAILED(hr)) return hr;

		hr = parentD2D_Factory->CreatePathGeometry(&TopRectArea);
		if (FAILED(hr)) return hr;

		hr = parentD2D_Factory->CreatePathGeometry(&RightRectArea);
		if (FAILED(hr)) return hr;

		hr = parentD2D_Factory->CreatePathGeometry(&BottomRectArea);
		return hr;
	}

	VOID WindowFrameManager::BindHwnd(HWND srcHwnd) {
		if (srcHwnd == AssociatedHwnd) return;
		DestroyAllAreas();
		AssociatedHwnd = srcHwnd;
	}

	VOID WindowFrameManager::DestroyAllAreas() {
		if (LeftUpCornerArea) {
			while (LeftUpCornerArea->Release());
			LeftUpCornerArea = nullptr;
		}
		
		if (RightUpCornerArea) {
			while (RightUpCornerArea->Release());
			RightUpCornerArea = nullptr;
		}

		if (LeftDownCornerArea) {
			while (LeftDownCornerArea->Release());
			LeftDownCornerArea = nullptr;
		}

		if (RightDownCornerArea) {
			while (RightDownCornerArea->Release());
			RightDownCornerArea = nullptr;
		}

		if (LeftRectArea) {
			while (LeftRectArea->Release());
			LeftRectArea = nullptr;
		}

		if (TopRectArea) {
			TopRectArea->Release();
			TopRectArea = nullptr;
		}

		if (RightRectArea) {
			RightRectArea->Release();
			RightRectArea = nullptr;
		}

		if (BottomRectArea) {
			BottomRectArea->Release();
			BottomRectArea = nullptr;
		}
	}

	HRESULT WindowFrameManager::UpdateArea() {
		if (AssociatedHwnd == NULL) return FALSE;
		if (LeftUpCornerArea == nullptr ||
			RightUpCornerArea == nullptr ||
			LeftDownCornerArea == nullptr ||
			RightDownCornerArea == nullptr ||
			LeftRectArea == nullptr ||
			TopRectArea == nullptr ||
			RightRectArea == nullptr ||
			BottomRectArea == nullptr) return FALSE;

		RECT CurrentRect;
		if (GetWindowRect(AssociatedHwnd, &CurrentRect) == FALSE) return FALSE;

		HRESULT hr = S_OK;

		ID2D1GeometrySink* sink = nullptr;
		hr = LeftUpCornerArea->Open(&sink);
		if (FAILED(hr)) return hr;
		sink->SetFillMode(D2D1_FILL_MODE_WINDING);
		
	}
}