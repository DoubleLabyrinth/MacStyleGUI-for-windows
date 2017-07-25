#include "RoundRectButton.h"
#include "../../GlobalDefine.h"

namespace MacStyleGUI::Controls::Button {

	RoundRectButton::RoundRectButton(FLOAT X, 
									 FLOAT Y, 
									 UINT Width, 
									 UINT Height, 
									 const D2D1_COLOR_F& NormalColor,
									 const D2D1_COLOR_F& FocusedColor,
									 const D2D1_COLOR_F& PressedColor) :
		m_CornerRadius(5),
		m_ShadowStandardDeviation(5.f),
		m_bg_ShadowLayer(nullptr),
		m_ButtonCanvas(nullptr) { 

		m_UIComponent_X = X;
		m_UIComponent_Y = Y;
		m_UIComponent_Width = Width;
		m_UIComponent_Height = Height;

		m_Button_NormalColor = NormalColor;
		m_Button_FocusedColor = FocusedColor;
		m_Button_PressedColor = PressedColor;
		
		Events.AddHandler(WM_CREATE, RoundRectButton::OnCreate);
		Events.AddHandler(WM_PAINT, RoundRectButton::OnPaint);
		Events.AddHandler(MacStyleGUI_EVENT_MOUSEIN, RoundRectButton::OnMouseIn);
		Events.AddHandler(MacStyleGUI_EVENT_MOUSEOUT, RoundRectButton::OnMouseOut);
	}

	BOOL RoundRectButton::SetPosX(FLOAT newX) {
		HRESULT hr = S_OK;
		if (FAILED(
			hr = m_UIComponent_RootVisual->SetOffsetX(newX)
		)) {
			m_UIComponent_LastError = hr;
			return FALSE;
		}

		if (FAILED(hr = MacStyleGUI::Graphics::Global_D2DFactory->
				   CreateRoundedRectangleGeometry(
					   D2D1::RoundedRect(
						   D2D1::RectF(m_UIComponent_X + MacStyleGUI_RESERVED_WIDTH,
									   m_UIComponent_Y + MacStyleGUI_RESERVED_WIDTH,
									   m_UIComponent_X + m_UIComponent_Width - MacStyleGUI_RESERVED_WIDTH,
									   m_UIComponent_Y + m_UIComponent_Height - MacStyleGUI_RESERVED_WIDTH),
						   m_CornerRadius,
						   m_CornerRadius),
					   m_EventGeometry.ReleaseAndGetAddressOf())
		)) {
			m_UIComponent_LastError = hr;
			return FALSE;
		}
		
		m_UIComponent_X = newX;
		return TRUE;
	}

	BOOL RoundRectButton::SetPosY(FLOAT newY) {
		HRESULT hr = S_OK;
		if (FAILED(
			hr = m_UIComponent_RootVisual->SetOffsetY(newY)
		)) {
			m_UIComponent_LastError = hr;
			return FALSE;
		}

		if (FAILED(
			hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreateRoundedRectangleGeometry(
				D2D1::RoundedRect(
					D2D1::RectF(m_UIComponent_X + MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_Y + MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_X + m_UIComponent_Width - MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_Y + m_UIComponent_Height - MacStyleGUI_RESERVED_WIDTH),
					m_CornerRadius,
					m_CornerRadius),
				m_EventGeometry.ReleaseAndGetAddressOf())
		)) {
			m_UIComponent_LastError = hr;
			return FALSE;
		}

		m_UIComponent_Y = newY;
		return TRUE;
	}

	BOOL RoundRectButton::Resize(UINT newUIComponentWidth, UINT newUIComponentHeight) {
		HRESULT hr = S_OK;

		if (FAILED(
			hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreateRoundedRectangleGeometry(
				D2D1::RoundedRect(
					D2D1::RectF(m_UIComponent_X + MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_Y + MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_X + m_UIComponent_Width - MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_Y + m_UIComponent_Height - MacStyleGUI_RESERVED_WIDTH),
					m_CornerRadius,
					m_CornerRadius),
				m_EventGeometry.ReleaseAndGetAddressOf())
		)) {
			m_UIComponent_LastError = hr;
			return FALSE;
		}

		
		// resize shadow layer
		if (m_bg_ShadowLayer && FAILED(
			hr = m_bg_ShadowLayer->Resize(newUIComponentWidth, newUIComponentHeight)
		)) {
			m_UIComponent_LastError = hr;
			return FALSE;
		}
		// resize button canvas
		if (m_ButtonCanvas && FAILED(
			hr = m_ButtonCanvas->Resize(newUIComponentWidth - 2 * MacStyleGUI_RESERVED_WIDTH,
										newUIComponentHeight - 2 * MacStyleGUI_RESERVED_WIDTH)
		)) {
			m_UIComponent_LastError = hr;
			return FALSE;
		}

		m_UIComponent_Width = newUIComponentWidth;
		m_UIComponent_Height = newUIComponentHeight;
		return TRUE;
	}

	ID2D1Geometry* RoundRectButton::GetEventGeometry() CONST { return m_EventGeometry.Get(); }

	BOOL RoundRectButton::SetCornerRadius(FLOAT newRadius) {
		if (newRadius < 0.f) return FALSE;

		HRESULT hr = S_OK;
		if (FAILED(
			hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreateRoundedRectangleGeometry(
				D2D1::RoundedRect(
					D2D1::RectF(m_UIComponent_X + MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_Y + MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_X + m_UIComponent_Width - MacStyleGUI_RESERVED_WIDTH,
								m_UIComponent_Y + m_UIComponent_Height - MacStyleGUI_RESERVED_WIDTH),
					m_CornerRadius,
					m_CornerRadius),
				m_EventGeometry.ReleaseAndGetAddressOf())
		)) {
			m_UIComponent_LastError = hr;
			return FALSE;
		}

		m_CornerRadius = newRadius;
		return TRUE;
	}

	LRESULT RoundRectButton::OnCreate(VOID* EventInfo, VOID* args) {
		HRESULT hr = S_OK;
		RoundRectButton* self = reinterpret_cast<RoundRectButton*>(args);

		hr = MacStyleGUI::Graphics::Global_DCompoDesktopDevice->CreateVisual(self->m_UIComponent_RootVisual.ReleaseAndGetAddressOf());
		if (FAILED(hr)) throw hr;
		hr = MacStyleGUI::Graphics::Global_D2DFactory->
			CreateRoundedRectangleGeometry(
				D2D1::RoundedRect(
					D2D1::RectF(self->m_UIComponent_X + MacStyleGUI_RESERVED_WIDTH,
								self->m_UIComponent_Y + MacStyleGUI_RESERVED_WIDTH,
								self->m_UIComponent_X + self->m_UIComponent_Width - MacStyleGUI_RESERVED_WIDTH,
								self->m_UIComponent_Y + self->m_UIComponent_Height - MacStyleGUI_RESERVED_WIDTH),
					self->m_CornerRadius,
					self->m_CornerRadius),
				self->m_EventGeometry.ReleaseAndGetAddressOf());

		self->m_bg_ShadowLayer = new MacStyleGUI::Graphics::Canvas(self->m_UIComponent_Width, self->m_UIComponent_Height);
		self->m_ButtonCanvas = new MacStyleGUI::Graphics::Canvas(self->m_UIComponent_Width - 2 * MacStyleGUI_RESERVED_WIDTH, self->m_UIComponent_Height - 2 * MacStyleGUI_RESERVED_WIDTH);

		// about shadow
		self->m_bg_ShadowLayer->GetDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), self->m_bg_ShadowLayer_SolidBrush.ReleaseAndGetAddressOf());
		MacStyleGUI::Graphics::Global_DCompoDevice->CreateShadowEffect(self->m_bg_ShadowLayer_ShadowEffect.ReleaseAndGetAddressOf());
		self->m_bg_ShadowLayer_ShadowEffect->SetStandardDeviation(self->m_ShadowStandardDeviation);
		self->m_bg_ShadowLayer_ShadowEffect->SetColor(D2D1::Vector4F(0.f, 0.f, 0.f, 1.f));
		self->m_bg_ShadowLayer->GetVisual()->SetEffect(self->m_bg_ShadowLayer_ShadowEffect.Get());

		// about button canvas
		self->m_ButtonCanvas->GetDeviceContext()->CreateSolidColorBrush(self->m_Button_FocusedColor, self->m_ButtonCanvas_SolidBrush.ReleaseAndGetAddressOf());
		self->m_ButtonCanvas->GetVisual()->SetOffsetX(MacStyleGUI_RESERVED_WIDTH);
		self->m_ButtonCanvas->GetVisual()->SetOffsetY(MacStyleGUI_RESERVED_WIDTH);

		self->m_UIComponent_RootVisual->SetOffsetX(self->m_UIComponent_X);
		self->m_UIComponent_RootVisual->SetOffsetY(self->m_UIComponent_Y);
		self->m_UIComponent_RootVisual->AddVisual(self->m_bg_ShadowLayer->GetVisual(), FALSE, nullptr);
		self->m_UIComponent_RootVisual->AddVisual(self->m_ButtonCanvas->GetVisual(), FALSE, nullptr);
		return TRUE;
	}

	LRESULT RoundRectButton::OnPaint(VOID* EventInfo, VOID* args) {
		HRESULT hr = S_OK;
		RoundRectButton* self = reinterpret_cast<RoundRectButton*>(args);

		//handle background shadow
		POINT offset;
		self->m_bg_ShadowLayer->BeginDraw(nullptr, &offset);
		self->m_bg_ShadowLayer->GetDeviceContext()->Clear();
		self->m_bg_ShadowLayer->GetDeviceContext()->FillRoundedRectangle(
			D2D1::RoundedRect(
				D2D1::RectF(
					offset.x + 1.5 * self->m_ShadowStandardDeviation,
					offset.y + 1.5 * self->m_ShadowStandardDeviation,
					offset.x + self->m_UIComponent_Width - 1.5 * self->m_ShadowStandardDeviation,
					offset.y + self->m_UIComponent_Height - 1.5 * self->m_ShadowStandardDeviation
				),
				MacStyleGUI_RESERVED_WIDTH + self->m_CornerRadius - 1.5 * self->m_ShadowStandardDeviation,
				MacStyleGUI_RESERVED_WIDTH + self->m_CornerRadius - 1.5 * self->m_ShadowStandardDeviation
			),
			self->m_bg_ShadowLayer_SolidBrush.Get()
		);
		self->m_bg_ShadowLayer->EndDraw();

		//handle button canvas
		switch (self->m_ButtonState) {
			case ButtonState::Focused:
				self->m_ButtonCanvas_SolidBrush->SetColor(self->m_Button_FocusedColor);
				break;
			case ButtonState::Pressed:
				self->m_ButtonCanvas_SolidBrush->SetColor(self->m_Button_PressedColor);
				break;
			default:
				self->m_ButtonCanvas_SolidBrush->SetColor(self->m_Button_NormalColor);
		}
		self->m_ButtonCanvas->BeginDraw(nullptr, &offset);
		self->m_ButtonCanvas->GetDeviceContext()->Clear();
		self->m_ButtonCanvas->GetDeviceContext()->FillRoundedRectangle(
			D2D1::RoundedRect(
				D2D1::RectF(
					offset.x,
					offset.y,
					offset.x + self->m_ButtonCanvas->GetCanvasWidth(),
					offset.y + self->m_ButtonCanvas->GetCanvasHeight()
				),
				self->m_CornerRadius,
				self->m_CornerRadius
			),
			self->m_ButtonCanvas_SolidBrush.Get()
		);

		self->m_ButtonCanvas->EndDraw();

		MacStyleGUI::Graphics::Global_DCompoDesktopDevice->Commit();
		return TRUE;
	}

	LRESULT RoundRectButton::OnMouseIn(VOID* EventInfo, VOID* args) {
		RoundRectButton* self = reinterpret_cast<RoundRectButton*>(args);

		self->m_ButtonState = ButtonState::Focused;
		OnPaint(nullptr, args);

		return TRUE;
	}

	LRESULT RoundRectButton::OnMouseOut(VOID* EventInfo, VOID* args) {
		RoundRectButton* self = reinterpret_cast<RoundRectButton*>(args);

		self->m_ButtonState = ButtonState::Normal;
		OnPaint(nullptr, args);

		return TRUE;
	}
}