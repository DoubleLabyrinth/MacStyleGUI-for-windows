#pragma once
#include "../../Graphics/Canvas/Canvas.h"

namespace MacStyleGUI::Controls::Group {

	class WindowPanel {
		WindowPanel(const WindowPanel&) = delete;
		WindowPanel& operator=(const WindowPanel&) = delete;
	protected:
		FLOAT m_UIComponent_X;
		FLOAT m_UIComponent_Y;
		UINT m_UIComponent_Width;
		UINT m_UIComponent_Height;

		FLOAT m_WndPanel_CornerRadius;
		FLOAT m_WndPanel_ShadowStandardDeviation;

		D2D1_COLOR_F m_WndPanel_ThemeColor;

		Microsoft::WRL::ComPtr<IDCompositionVisual2> m_RootVisual;
		MacStyleGUI::Graphics::Canvas* m_WndPanel_ShadowLayer;
		MacStyleGUI::Graphics::Canvas* m_WndPanel_PanelCanvas;
		Microsoft::WRL::ComPtr<IDCompositionRectangleClip> m_WndPanel_ValidArea;

		//resource
		Microsoft::WRL::ComPtr<IDCompositionShadowEffect> m_WndPanel_RES_ShadowEffect;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_WndPanel_RES_ShadowLayer_SolidBrush;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_WndPanel_RES_Canvas_SolidBrush;
	public:
		WindowPanel(FLOAT X,
					FLOAT Y,
					UINT UIComponentWidth,
					UINT UIComponentHeight,
					const D2D1_COLOR_F& ThemeColor);

		virtual IDCompositionVisual2* GetRootVisual() CONST;
		virtual IDCompositionVisual2* GetPanelVisual() CONST;

		virtual VOID Resize(UINT newUIComponentWidth, UINT newUIComponentHeight);

		virtual LRESULT OnCreate(VOID* args, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnPaint(VOID* args, WPARAM wParam, LPARAM lParam);
	};
}