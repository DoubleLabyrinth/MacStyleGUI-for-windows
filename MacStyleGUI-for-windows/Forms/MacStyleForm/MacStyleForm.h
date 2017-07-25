#pragma once
#include "../DCompositionForm.h"
#include "../../Graphics/Canvas/Canvas.h"
#include "../../Controls/Button/RoundRectButton.h"
#include "../../Controls/Group/WindowPanel.h"
#include "../../Controls/Frame/RoundRectFrame.h"

namespace MacStyleGUI::Forms {

	extern CONST TCHAR STR_MacStyleForm[];

	class MacStyleForm : public DCompositionForm<STR_MacStyleForm> {
	private:
		MacStyleForm(const MacStyleForm&) = delete;
		MacStyleForm& operator=(const MacStyleForm&) = delete;
	protected:
		FLOAT m_CornerRadius;
		MacStyleGUI::Controls::Frame::RoundRectFrame FrameManager;
		//MacStyleForm Resource;
		MacStyleGUI::Controls::Button::RoundRectButton testButton;
		MacStyleGUI::Controls::Group::WindowPanel Panel;
	public:
		MacStyleForm(int init_X, int init_Y,
					 int init_Width, int init_Height);

		virtual LRESULT ReceiveMessage(MSG Msg) override;

		virtual LRESULT OnCreate(VOID* args, WPARAM wParam, LPARAM lParam) override;
		virtual LRESULT OnSize(VOID* args, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnPaint(VOID* args, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnMouseMove(VOID* args, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnLMouseButtonUp(VOID* args, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnLMouseButtonDown(VOID* args, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnMouseWheel(VOID* args, WPARAM wParam, LPARAM lParam);
	};
}