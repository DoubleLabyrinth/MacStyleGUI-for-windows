#include "MacForm.h"

namespace MacGUI::Forms {

	MacForm::~MacForm() {

	}

	HRESULT MacForm::InitialDirectX() {
		HRESULT hr = S_OK;

		hr = DCompositionCreateDevice3(Global::DXGI_Device, IID_PPV_ARGS(&CompositionDevice));
		if (FAILED(hr)) return hr;

		hr = CompositionDevice->QueryInterface(IID_PPV_ARGS(&AssistantCompositionDevice));
		if (FAILED(hr)) return hr;

		hr = CompositionDevice->CreateTargetForHwnd(m_Hwnd, TRUE, &CompositionTarget);
		if (FAILED(hr)) return hr;

		hr = CompositionDevice->CreateVisual(&RootVisual);
		if (FAILED(hr)) return hr;
		hr = CompositionDevice->CreateVisual(&BackgroundVisual);
		if (FAILED(hr)) return hr;
		hr = CompositionDevice->CreateVisual(&BackgroundPanel);
		if (FAILED(hr)) return hr;

		hr = RootVisual->AddVisual(BackgroundVisual, TRUE, nullptr);
		if (FAILED(hr)) return hr;
		hr = RootVisual->AddVisual(BackgroundPanel, TRUE, BackgroundVisual);
		if (FAILED(hr)) return hr;

		hr = CompositionTarget->SetRoot(RootVisual);
		if (FAILED(hr)) return hr;

		hr = Global::D2D_Factory->CreateDevice(Global::DXGI_Device, &FormDevice);
		if (FAILED(hr)) return hr;

		hr = FormDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
											 &FormDeviceContext);
		if (FAILED(hr)) return hr;

		hr = AssistantCompositionDevice->CreateShadowEffect(&shadow);
		if (FAILED(hr)) return hr;

		hr = shadow->SetStandardDeviation(2.5f);
		if (FAILED(hr)) return hr;

		hr = BackgroundVisual->SetEffect(shadow);
		if (FAILED(hr)) return hr;

		BackgroundSwapChain = new Graphics::CompositionSwapChain(Global::DXGI_Device, Global::DXGI_Factory);
		if (BackgroundSwapChain == nullptr) return E_OUTOFMEMORY;

		GetWindowRect(m_Hwnd, &WindowRect);
		BackgroundSwapChain->SetSize(WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top);
		hr = BackgroundSwapChain->CreateSwapChain();
		if (FAILED(hr)) return hr;

		BackgroundCanvas = new Graphics::SurfaceCanvas(BackgroundSwapChain, FormDeviceContext);
		if (BackgroundCanvas == nullptr) return E_OUTOFMEMORY;

		hr = BackgroundCanvas->ObtainSurface();
		if (FAILED(hr)) return hr;

		hr = BackgroundCanvas->CreateCanvas();
		if (FAILED(hr)) return hr;

		hr = BackgroundVisual->SetContent(BackgroundSwapChain->GetSwapChianInstance());
		if (FAILED(hr)) return hr;

		hr = BackgroundPanel->SetContent(BackgroundSwapChain->GetSwapChianInstance());
		if (FAILED(hr)) return hr;

		FormDeviceContext->SetTarget(BackgroundCanvas->GetCanvasInstance());

		return hr;
	}

	LRESULT MacForm::OnCreate(WPARAM wParam, LPARAM lParam) {
		HRESULT hr = InitialDirectX();
		if (FAILED(hr)) throw;
		return 0;
	}

	LRESULT MacForm::OnPaint(WPARAM wParam, LPARAM lParam) {
		HRESULT hr;
		FormDeviceContext->BeginDraw();
		FormDeviceContext->Clear();
		ID2D1SolidColorBrush* brush0 = nullptr;

		hr = FormDeviceContext->CreateSolidColorBrush(D2D1::ColorF(0xFFFFFF), &brush0);
		D2D1_SIZE_U CanvasSize = FormDeviceContext->GetPixelSize();
		FormDeviceContext->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(5.0f, 5.0f, CanvasSize.width - 5.0f, CanvasSize.height - 5.0f), 5.0f, 5.0f), brush0);
		brush0->SetColor(D2D1::ColorF(0xf46251));
		FormDeviceContext->FillEllipse(D2D1::Ellipse(D2D1::Point2F(25.0f, 21.0f), 8.0f, 8.0f), brush0);
		brush0->SetColor(D2D1::ColorF(0xf8b83f));
		FormDeviceContext->FillEllipse(D2D1::Ellipse(D2D1::Point2F(50.0f, 21.0f), 8.0f, 8.0f), brush0);
		brush0->SetColor(D2D1::ColorF(0x30c64e));
		FormDeviceContext->FillEllipse(D2D1::Ellipse(D2D1::Point2F(75.0f, 21.0f), 8.0f, 8.0f), brush0);
		if (Contains) {
			brush0->SetColor(D2D1::ColorF(0xff0000));
		} else {
			brush0->SetColor(D2D1::ColorF(0x808080));
		}

		//FormDeviceContext->FillGeometry(FormFrame, brush0);
		hr = FormDeviceContext->EndDraw();

		hr = BackgroundSwapChain->GetSwapChianInstance()->Present(1, 0);
		hr = CompositionDevice->Commit();

		brush0->Release();
		ValidateRect(m_Hwnd, nullptr);
		return 0;
	}

	LRESULT MacForm::OnDestroy(WPARAM wParam, LPARAM lParam) {
		PostQuitMessage(0);
		return 0;
	}

	LRESULT MacForm::OnSizing(WPARAM wParam, LPARAM lParam) {
		//GetWindowRect(hWnd, &WindowRect);
		return OnSize(wParam, lParam);
	}

	LRESULT MacForm::OnSize(WPARAM wParam, LPARAM lParam) {
		GetWindowRect(m_Hwnd, &WindowRect);
		HRESULT hr = S_OK;
		FormDeviceContext->SetTarget(nullptr);

		hr = BackgroundCanvas->ResizeCanvas(WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top);
		FormDeviceContext->SetTarget(BackgroundCanvas->GetCanvasInstance());

		ID2D1RoundedRectangleGeometry* OutsideBound = nullptr;
		ID2D1RoundedRectangleGeometry* InsideBound = nullptr;

		Global::D2D_Factory->CreateRoundedRectangleGeometry(D2D1::RoundedRect(D2D1::RectF(5.0f, 5.0f, WindowRect.right - WindowRect.left - 5.0f, WindowRect.bottom - WindowRect.top - 5.0f), 5.0f, 5.0f), &OutsideBound);
		Global::D2D_Factory->CreateRoundedRectangleGeometry(D2D1::RoundedRect(D2D1::RectF(10.0f, 10.0f, WindowRect.right - WindowRect.left - 10.0f, WindowRect.bottom - WindowRect.top - 10.0f), 5.0f, 5.0f), &InsideBound);
		Global::D2D_Factory->CreatePathGeometry(&FormFrame);
		
		ID2D1GeometrySink* CombinedSink = nullptr;
		FormFrame->Open(&CombinedSink);
		hr = OutsideBound->CombineWithGeometry(InsideBound, D2D1_COMBINE_MODE_EXCLUDE, nullptr, CombinedSink);
		CombinedSink->Close();
		CombinedSink->Release();
		CombinedSink = nullptr;
		OutsideBound->Release();
		InsideBound->Release();
		return 0;
	}

	LRESULT MacForm::OnNonClientPaint(WPARAM wParam, LPARAM lParam) {
		return DefWindowProc(m_Hwnd, WM_NCPAINT, wParam, lParam);
	}

	LRESULT MacForm::OnLeftMouseButtonDown(WPARAM wParam, LPARAM lParam) {
		SetCapture(m_Hwnd);

		FormFrame->FillContainsPoint(D2D1::Point2F(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), nullptr, &Contains);
		if (Contains) {
			GetWindowRect(m_Hwnd, &OldWindowRect);
			OldCursorPos.x = GET_X_LPARAM(lParam);
			OldCursorPos.y = GET_Y_LPARAM(lParam);
			ChangeSize = TRUE;
			InvalidateRect(m_Hwnd, nullptr, FALSE);
		}

		return TRUE;
	}

	LRESULT MacForm::OnLeftMouseButtonUp(WPARAM wParam, LPARAM lParam) {
		ChangeSize = FALSE;
		Contains = FALSE;
		InvalidateRect(m_Hwnd, NULL, FALSE);
		ReleaseCapture();
		return TRUE;
		return 0;
	}

	LRESULT MacForm::OnMouseMove(WPARAM wParam, LPARAM lParam) {
		FormFrame->FillContainsPoint(D2D1::Point2F(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), nullptr, &Contains);
		if (ChangeSize) {
			MoveWindow(m_Hwnd,
					   OldWindowRect.left,
					   OldWindowRect.top,
					   OldWindowRect.right - OldWindowRect.left + GET_X_LPARAM(lParam) - OldCursorPos.x,
					   OldWindowRect.bottom - OldWindowRect.top, TRUE);
		}
		//SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return TRUE;
	}

	LRESULT MacForm::OnSetCursor(WPARAM wParam, LPARAM lParam) {
		if (Contains) {
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		} else {
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		return TRUE;
	}
}