#include "Group.h"
#include "../GlobalDefine.h"

namespace MacStyleGUI::Groups {

	Group::Group() :
		m_Group_OffsetX(0.f),
		m_Group_OffsetY(0.f),
		m_Group_MouseFocused(nullptr),
		m_Group_KeyboardFocused(nullptr),
		m_Group_LastError(0)
	{
		HRESULT hr = S_OK;
		if (FAILED(
			hr = MacStyleGUI::Graphics::Global_DCompoDesktopDevice->CreateVisual(m_UILayer_Layer.ReleaseAndGetAddressOf())
		)) {
			throw hr;
		}

		if (FAILED(
			hr = MacStyleGUI::Graphics::Global_DCompoDesktopDevice->CreateRectangleClip(m_UILayer_Cliper.ReleaseAndGetAddressOf())
		)) {
			throw hr;
		}
	}

	BOOL Group::SetOffsetX(FLOAT newX) {
		HRESULT hr = m_Group_Layer->SetOffsetX(newX);
		if (FAILED(hr)) {
			m_Group_LastError = hr;
			return FALSE;
		}
		m_Group_OffsetX = newX;
		return TRUE;
	}

	BOOL Group::SetOffsetY(FLOAT newY) {
		HRESULT hr = m_Group_Layer->SetOffsetY(newY);
		if (FAILED(hr)) {
			m_Group_LastError = hr;
			return FALSE;
		}
		m_Group_OffsetY = newY;
		return TRUE;
	}

	BOOL Group::AddControl(MacStyleGUI::Controls::UIConponent* newControl, 
						   BOOL InsertAbove, 
						   MacStyleGUI::Controls::UIConponent* referenceUI) {
		if (newControl == nullptr) {
			m_Group_LastError = E_POINTER;
			return FALSE;
		}

		HRESULT hr = S_OK;
		if (referenceUI == nullptr) {
			hr = m_Group_Layer->AddVisual(newControl->GetRootVisual(), FALSE, nullptr);
			if (FAILED(hr)) {
				m_Group_LastError = hr;
				return FALSE;
			}

			m_Group_Controls.emplace_back(newControl);
			return TRUE;
		} else {
			auto it_referenceUI = find(m_Group_Controls.begin(), m_Group_Controls.end(), referenceUI);
			if (it_referenceUI == m_Group_Controls.end()) {
				m_Group_LastError = MacStyleGUI_ERROR_UILAYER_NO_UI_FOUND;
				return FALSE;
			}

			hr = m_Group_Layer->AddVisual(newControl->GetRootVisual(), InsertAbove, referenceUI->GetRootVisual());
			if (FAILED(hr)) {
				m_Group_LastError = hr;
				return FALSE;
			}

			m_Group_Controls.insert(InsertAbove ? it_referenceUI + 1 : it_referenceUI, newControl);
			return TRUE;
		}
	}

	BOOL Group::RemoveControl(MacStyleGUI::Controls::UIConponent* ControlToRemove) {
		auto it_ControlToRemove = find(m_Group_Controls.begin(), m_Group_Controls.end(), ControlToRemove);
		if (it_ControlToRemove == m_Group_Controls.end()) {
			m_Group_LastError = MacStyleGUI_ERROR_UILAYER_NO_UI_FOUND;
			return FALSE;
		}

		HRESULT hr = S_OK;
		hr = m_Group_Layer->RemoveVisual(ControlToRemove->GetRootVisual());
		if (FAILED(hr)) {
			m_Group_LastError = hr;
			return FALSE;
		}

		m_Group_Controls.erase(it_ControlToRemove);
		return TRUE;
	}

	HRESULT Group::EnableRectClip(BOOL enable) {
		if (m_Group_RectClip.Get() && enable == FALSE) {
			m_Group_RectClip.ReleaseAndGetAddressOf();
			return S_OK;
		} else if (m_Group_RectClip.Get() == nullptr && enable) {
			return MacStyleGUI::Graphics::Global_DCompoDesktopDevice->
				CreateRectangleClip(m_Group_RectClip.ReleaseAndGetAddressOf());
		}

		return E_FAIL;
	}

	LRESULT Group::ReceiveMessage(MSG Msg) {
		Events.HandleEvent(Msg.message, Msg, nullptr);

		Msg.pt.x -= m_Group_OffsetX;
		Msg.pt.y -= m_Group_OffsetY;

		//find current focused control
		auto it_focused_ui = m_Group_Controls.rbegin();
		BOOL contain = FALSE;
		for (; it_focused_ui != m_Group_Controls.rend(); ++it_focused_ui) {
			if (*it_focused_ui &&
				(*it_focused_ui)->GetEventGeometry() &&
				SUCCEEDED((*it_focused_ui)->GetEventGeometry()->FillContainsPoint(D2D1::Point2F(Msg.pt.x, Msg.pt.y), nullptr, &contain))) {
				if (contain) break;
			}
		}
		
		if (it_focused_ui != m_Group_Controls.rend()) {	//if found
			if (m_Group_MouseFocused == *it_focused_ui)	// if still last focused control
				(*it_focused_ui)->Events.HandleEvent(Msg.message, Msg, nullptr);
			else {
				auto temp_Msg = Msg;
				temp_Msg.message = MacStyleGUI_EVENT_MOUSEOUT;
				m_Group_MouseFocused->Events.HandleEvent(MacStyleGUI_EVENT_MOUSEOUT, temp_Msg, nullptr);
				temp_Msg.message = MacStyleGUI_EVENT_MOUSEIN;
				(*it_focused_ui)->Events.HandleEvent(MacStyleGUI_EVENT_MOUSEIN, temp_Msg, nullptr);
				(*it_focused_ui)->Events.HandleEvent(temp_Msg.message, Msg, nullptr);
			}
		}

		return 0;
	}
}