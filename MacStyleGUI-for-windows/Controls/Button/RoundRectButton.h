#pragma once
#include "Button.h"
#include "../../Graphics/Canvas/Canvas.h"

namespace MacStyleGUI::Controls::Button {

	class RoundRectButton : public Button {
	protected:
		UINT m_CornerRadius;
		FLOAT m_ShadowStandardDeviation;
		
		MacStyleGUI::Graphics::Canvas* m_bg_ShadowLayer;
		MacStyleGUI::Graphics::Canvas* m_ButtonCanvas;
		Microsoft::WRL::ComPtr<ID2D1RoundedRectangleGeometry> m_EventGeometry;

		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_bg_ShadowLayer_SolidBrush;
		Microsoft::WRL::ComPtr<IDCompositionShadowEffect> m_bg_ShadowLayer_ShadowEffect;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_ButtonCanvas_SolidBrush;
	public:
		enum MyEventList {

		};

		RoundRectButton(FLOAT X, 
						FLOAT Y, 
						UINT Width, 
						UINT Height, 
						const D2D1_COLOR_F& NormalColor,
						const D2D1_COLOR_F& FocusedColor,
						const D2D1_COLOR_F& PressedColor);

		BOOL SetPosX(FLOAT newX) override;
		BOOL SetPosY(FLOAT newY) override;

		virtual BOOL Resize(UINT newUIComponentWidth, UINT newUIComponentHeight) override;

		virtual ID2D1Geometry* GetEventGeometry() CONST override;
		
		virtual BOOL SetCornerRadius(FLOAT newRadius);

		static LRESULT OnCreate(VOID* EventInfo, VOID* args);
		static LRESULT OnPaint(VOID* EventInfo, VOID* args);
		static LRESULT OnMouseIn(VOID* EventInfo, VOID* args);
		static LRESULT OnMouseOut(VOID* EventInfo, VOID* args);
	};
}

