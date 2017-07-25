#include "WindowPanel.h"
#include "../../GlobalDefine.h"

namespace MacStyleGUI::Controls::Group {

	WindowPanel::WindowPanel(FLOAT X,
							 FLOAT Y,
							 UINT UIComponentWidth,
							 UINT UIComponentHeight,
							 const D2D1_COLOR_F& ThemeColor) :
		m_UIComponent_X(X),
		m_UIComponent_Y(Y),
		m_UIComponent_Width(UIComponentWidth),
		m_UIComponent_Height(UIComponentHeight),
		m_WndPanel_CornerRadius(8.f),
		m_WndPanel_ShadowStandardDeviation(3.f),
		m_WndPanel_ThemeColor(ThemeColor),
		m_WndPanel_ShadowLayer(nullptr),
		m_WndPanel_PanelCanvas(nullptr) { }

	IDCompositionVisual2* WindowPanel::GetRootVisual() CONST { return m_RootVisual.Get(); }
	IDCompositionVisual2* WindowPanel::GetPanelVisual() CONST { return m_WndPanel_PanelCanvas->GetVisual(); }

	VOID WindowPanel::Resize(UINT newUIComponentWidth, UINT newUIComponentHeight) {
		m_WndPanel_ShadowLayer->Resize(newUIComponentWidth, newUIComponentHeight);
		m_WndPanel_PanelCanvas->Resize(static_cast<UINT>(newUIComponentWidth - 2 * MacStyleGUI_RESERVED_WIDTH),
									   static_cast<UINT>(newUIComponentHeight - 2 * MacStyleGUI_RESERVED_WIDTH));
		
		m_UIComponent_Width = newUIComponentWidth;
		m_UIComponent_Height = newUIComponentHeight;

		m_WndPanel_ValidArea->SetLeft(0.f);
		m_WndPanel_ValidArea->SetTop(0.f);
		m_WndPanel_ValidArea->SetRight(m_UIComponent_Width - 2.f * MacStyleGUI_RESERVED_WIDTH);
		m_WndPanel_ValidArea->SetBottom(m_UIComponent_Height - 2.f * MacStyleGUI_RESERVED_WIDTH);
// 		m_WndPanel_ValidArea->SetTopLeftRadiusX(m_WndPanel_CornerRadius);
// 		m_WndPanel_ValidArea->SetTopLeftRadiusY(m_WndPanel_CornerRadius);
// 		m_WndPanel_ValidArea->SetTopRightRadiusX(m_WndPanel_CornerRadius);
// 		m_WndPanel_ValidArea->SetTopRightRadiusX(m_WndPanel_CornerRadius);
// 		m_WndPanel_ValidArea->SetBottomRightRadiusX(m_WndPanel_CornerRadius);
// 		m_WndPanel_ValidArea->SetBottomRightRadiusY(m_WndPanel_CornerRadius);
// 		m_WndPanel_ValidArea->SetBottomLeftRadiusX(m_WndPanel_CornerRadius);
// 		m_WndPanel_ValidArea->SetBottomLeftRadiusY(m_WndPanel_CornerRadius);
		//m_WndPanel_PanelCanvas->GetVisual()->SetClip(m_WndPanel_ValidArea.Get());

		OnPaint(nullptr, 0, 0);
	}

	LRESULT WindowPanel::OnCreate(VOID* args, WPARAM wParam, LPARAM lParam) {
		MacStyleGUI::Graphics::Global_DCompoDesktopDevice->CreateVisual(m_RootVisual.ReleaseAndGetAddressOf());

		MacStyleGUI::Graphics::Global_DCompoDevice->CreateShadowEffect(m_WndPanel_RES_ShadowEffect.ReleaseAndGetAddressOf());
		m_WndPanel_RES_ShadowEffect->SetStandardDeviation(m_WndPanel_ShadowStandardDeviation);
		m_WndPanel_RES_ShadowEffect->SetColor(D2D1::Vector4F(0.f, 0.f, 0.f, 1.f));

		MacStyleGUI::Graphics::Global_DCompoDesktopDevice->CreateRectangleClip(m_WndPanel_ValidArea.ReleaseAndGetAddressOf());

		// create shadow layer
		m_WndPanel_ShadowLayer = new MacStyleGUI::Graphics::Canvas(m_UIComponent_Width, m_UIComponent_Height);
		m_WndPanel_ShadowLayer->
			GetDeviceContext()->
			CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black), 
				m_WndPanel_RES_ShadowLayer_SolidBrush.ReleaseAndGetAddressOf()
			);
		
		if (m_UIComponent_Width - 2 * MacStyleGUI_RESERVED_WIDTH < 0 ||
			m_UIComponent_Height - 2 * MacStyleGUI_RESERVED_WIDTH < 0)
			throw;
		m_WndPanel_PanelCanvas = new MacStyleGUI::Graphics::Canvas(static_cast<UINT>(m_UIComponent_Width - 2 * MacStyleGUI_RESERVED_WIDTH),
																   static_cast<UINT>(m_UIComponent_Height - 2 * MacStyleGUI_RESERVED_WIDTH));
		m_WndPanel_PanelCanvas->
			GetDeviceContext()->
			CreateSolidColorBrush(
				m_WndPanel_ThemeColor, 
				m_WndPanel_RES_Canvas_SolidBrush.ReleaseAndGetAddressOf()
			);

		m_WndPanel_ShadowLayer->GetVisual()->SetEffect(m_WndPanel_RES_ShadowEffect.Get());
		m_RootVisual->AddVisual(m_WndPanel_ShadowLayer->GetVisual(), FALSE, nullptr);
		m_RootVisual->AddVisual(m_WndPanel_PanelCanvas->GetVisual(), FALSE, nullptr);

		//Apply Property
		m_RootVisual->SetOffsetX(m_UIComponent_X);
		m_RootVisual->SetOffsetY(m_UIComponent_Y);
		m_WndPanel_PanelCanvas->GetVisual()->SetOffsetX(MacStyleGUI_RESERVED_WIDTH);
		m_WndPanel_PanelCanvas->GetVisual()->SetOffsetY(MacStyleGUI_RESERVED_WIDTH);

		m_WndPanel_ValidArea->SetLeft(0.f);
		m_WndPanel_ValidArea->SetTop(0.f);
		m_WndPanel_ValidArea->SetRight(m_UIComponent_Width - 2.f * MacStyleGUI_RESERVED_WIDTH);
		m_WndPanel_ValidArea->SetBottom(m_UIComponent_Height - 2.f * MacStyleGUI_RESERVED_WIDTH);
		m_WndPanel_ValidArea->SetTopLeftRadiusX(m_WndPanel_CornerRadius);
		m_WndPanel_ValidArea->SetTopLeftRadiusY(m_WndPanel_CornerRadius);
		m_WndPanel_ValidArea->SetTopRightRadiusX(m_WndPanel_CornerRadius);
		m_WndPanel_ValidArea->SetTopRightRadiusX(m_WndPanel_CornerRadius);
		m_WndPanel_ValidArea->SetBottomRightRadiusX(m_WndPanel_CornerRadius);
		m_WndPanel_ValidArea->SetBottomRightRadiusY(m_WndPanel_CornerRadius);
		m_WndPanel_ValidArea->SetBottomLeftRadiusX(m_WndPanel_CornerRadius);
		m_WndPanel_ValidArea->SetBottomLeftRadiusY(m_WndPanel_CornerRadius);
		m_WndPanel_PanelCanvas->GetVisual()->SetClip(m_WndPanel_ValidArea.Get());

		return TRUE;
	}

	LRESULT WindowPanel::OnPaint(VOID* args, WPARAM wParam, LPARAM lParam) {
		POINT offset;
		m_WndPanel_ShadowLayer->BeginDraw(nullptr, &offset);
		m_WndPanel_ShadowLayer->GetDeviceContext()->Clear();
		m_WndPanel_ShadowLayer->GetDeviceContext()->
			FillRoundedRectangle(
				D2D1::RoundedRect(
					D2D1::RectF(
						offset.x + 1.5f * m_WndPanel_ShadowStandardDeviation,
						offset.y + 1.5f * m_WndPanel_ShadowStandardDeviation,
						offset.x + m_WndPanel_ShadowLayer->GetCanvasWidth() - 1.5f * m_WndPanel_ShadowStandardDeviation,
						offset.y + m_WndPanel_ShadowLayer->GetCanvasHeight() - 1.5f * m_WndPanel_ShadowStandardDeviation
					),
					m_WndPanel_CornerRadius,
					m_WndPanel_CornerRadius),
				m_WndPanel_RES_ShadowLayer_SolidBrush.Get());
		m_WndPanel_ShadowLayer->EndDraw();

		m_WndPanel_PanelCanvas->BeginDraw(nullptr, &offset);
		m_WndPanel_PanelCanvas->GetDeviceContext()->Clear();
		m_WndPanel_PanelCanvas->GetDeviceContext()->
			FillRoundedRectangle(
				D2D1::RoundedRect(
					D2D1::RectF(
						offset.x,
						offset.y,
						offset.x + m_WndPanel_PanelCanvas->GetCanvasWidth(),
						offset.y + m_WndPanel_PanelCanvas->GetCanvasHeight()
					),
					m_WndPanel_CornerRadius,
					m_WndPanel_CornerRadius),
				m_WndPanel_RES_Canvas_SolidBrush.Get());
		m_WndPanel_PanelCanvas->EndDraw();

		MacStyleGUI::Graphics::Global_DCompoDesktopDevice->Commit();
		return TRUE;
	}
}