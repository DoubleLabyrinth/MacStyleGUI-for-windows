#pragma once
#define MacStyleGUI_RESERVED_WIDTH 5

#define MacStyleGUI_EVENT_MOUSEIN (/*WM_USER*/0x0400 + 1)
#define MacStyleGUI_EVENT_MOUSEOUT (/*WM_USER*/0x0400 + 2)
#define MacStyleGUI_EVENT_LBUTTONCLICK (/*WM_USER*/0x0400 + 3)
#define MacStyleGUI_EVENT_MBUTTONCLICK (/*WM_USER*/0x0400 + 3)
#define MacStyleGUI_EVENT_RBUTTONCLICK (/*WM_USER*/0x0400 + 3)
#define MacStyleGUI_EVENT_XBUTTONCLICK (/*WM_USER*/0x0400 + 3)

#define MacStyleGUI_ERROR_UILAYER_NO_UI_FOUND 0xE0000000 //11 1 0 0000000000000000000000000000