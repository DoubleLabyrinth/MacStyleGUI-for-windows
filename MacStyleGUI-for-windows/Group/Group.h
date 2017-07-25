#pragma once
#include <deque>
#include "../Graphics/Global.h"
#include "../Controls/UIComponent.h"

namespace MacStyleGUI::Groups {

	class Group {
		Group(const Group&) = delete;
		Group& operator=(const Group&) = delete;
	protected:
		FLOAT m_Group_OffsetX;
		FLOAT m_Group_OffsetY;

		Microsoft::WRL::ComPtr<IDCompositionVisual2> m_Group_Layer;
		Microsoft::WRL::ComPtr<IDCompositionRectangleClip> m_Group_RectClip;
		std::deque<MacStyleGUI::Controls::UIConponent*> m_Group_Controls;

		MacStyleGUI::Controls::UIConponent* m_Group_MouseFocused;
		MacStyleGUI::Controls::UIConponent* m_Group_KeyboardFocused;

		UINT m_Group_LastError;
	public:
		MacStyleGUI::EventSystem::EventHandler Events;
		Group();
		
		virtual BOOL SetOffsetX(FLOAT newX);
		virtual BOOL SetOffsetY(FLOAT newY);

		virtual FLOAT GetOffsetX() CONST { return m_Group_OffsetX; }
		virtual FLOAT GetOffsetY() CONST { return m_Group_OffsetY; }

		virtual BOOL AddControl(MacStyleGUI::Controls::UIConponent* newControl, 
								BOOL InsertAbove, 
								MacStyleGUI::Controls::UIConponent* referenceUI);
		virtual BOOL RemoveControl(MacStyleGUI::Controls::UIConponent* ControlToRemove);

		virtual HRESULT EnableRectClip(BOOL enable);

		virtual LRESULT ReceiveMessage(MSG Msg);
	};
}