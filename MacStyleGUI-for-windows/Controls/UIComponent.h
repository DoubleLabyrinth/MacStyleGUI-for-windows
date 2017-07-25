#pragma once
#include <windows.h>
#include "../Graphics/Global.h"
#include "../EventSystem/EventHandler.h"

namespace MacStyleGUI::Controls {

	class UIConponent {
	protected:
		FLOAT m_UIComponent_X;
		FLOAT m_UIComponent_Y;
		UINT m_UIComponent_Width;
		UINT m_UIComponent_Height;

		UINT m_UIComponent_LastError;

		Microsoft::WRL::ComPtr<IDCompositionVisual2> m_UIComponent_RootVisual;
	public:
		MacStyleGUI::EventSystem::EventHandler Events;

		UIConponent() :
			m_UIComponent_X(0.f),
			m_UIComponent_Y(0.f),
			m_UIComponent_Width(0),
			m_UIComponent_Height(0),
			m_UIComponent_LastError(0) 
		{
			HRESULT hr = S_OK;
			if (FAILED(
				hr = MacStyleGUI::Graphics::Global_DCompoDesktopDevice->CreateVisual(m_UIComponent_RootVisual.ReleaseAndGetAddressOf())
			)) throw hr;
		}

		virtual FLOAT GetPosX() CONST { return m_UIComponent_X; };
		virtual FLOAT GetPosY() CONST { return m_UIComponent_Y; }
		virtual BOOL SetPosX(FLOAT newX) { m_UIComponent_X = newX; return TRUE; }
		virtual BOOL SetPosY(FLOAT newY) { m_UIComponent_Y = newY; return TRUE; }

		virtual UINT GetWidth() CONST { return m_UIComponent_Width; }
		virtual UINT GetHeight() CONST { return m_UIComponent_Height; }
		virtual BOOL Resize(UINT newWidth, UINT newHeight) {
			m_UIComponent_Width = newWidth;
			m_UIComponent_Height = newHeight;
			return TRUE; 
		}

		virtual UINT GetLastError() CONST { return m_UIComponent_LastError; }

		virtual ID2D1Geometry* GetEventGeometry() CONST = 0;
		virtual IDCompositionVisual2* GetRootVisual() CONST { return m_UIComponent_RootVisual.Get(); }
	};
}