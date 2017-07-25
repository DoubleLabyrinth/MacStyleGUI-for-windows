#include <tchar.h>
#include <windows.h>

#include "Forms/MacStyleForm/MacStyleForm.h"

// typedef enum _WINDOWCOMPOSITIONATTRIB {
// 	WCA_UNDEFINED = 0,
// 	WCA_NCRENDERING_ENABLED = 1,
// 	WCA_NCRENDERING_POLICY = 2,
// 	WCA_TRANSITIONS_FORCEDISABLED = 3,
// 	WCA_ALLOW_NCPAINT = 4,
// 	WCA_CAPTION_BUTTON_BOUNDS = 5,
// 	WCA_NONCLIENT_RTL_LAYOUT = 6,
// 	WCA_FORCE_ICONIC_REPRESENTATION = 7,
// 	WCA_EXTENDED_FRAME_BOUNDS = 8,
// 	WCA_HAS_ICONIC_BITMAP = 9,
// 	WCA_THEME_ATTRIBUTES = 10,
// 	WCA_NCRENDERING_EXILED = 11,
// 	WCA_NCADORNMENTINFO = 12,
// 	WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
// 	WCA_VIDEO_OVERLAY_ACTIVE = 14,
// 	WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
// 	WCA_DISALLOW_PEEK = 16,
// 	WCA_CLOAK = 17,
// 	WCA_CLOAKED = 18,
// 	WCA_ACCENT_POLICY = 19,
// 	WCA_FREEZE_REPRESENTATION = 20,
// 	WCA_EVER_UNCLOAKED = 21,
// 	WCA_VISUAL_OWNER = 22,
// 	WCA_LAST = 23
// } WINDOWCOMPOSITIONATTRIB;
// 
// typedef struct _WINDOWCOMPOSITIONATTRIBDATA {
// 	WINDOWCOMPOSITIONATTRIB Attrib;
// 	PVOID pvData;
// 	SIZE_T cbData;
// } WINDOWCOMPOSITIONATTRIBDATA;
// 
// typedef enum _ACCENT_STATE {
// 	ACCENT_DISABLED = 0,
// 	ACCENT_ENABLE_GRADIENT = 1,
// 	ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
// 	ACCENT_ENABLE_BLURBEHIND = 3,
// 	ACCENT_INVALID_STATE = 4
// } ACCENT_STATE;
// 
// typedef struct _ACCENT_POLICY {
// 	ACCENT_STATE AccentState;
// 	DWORD AccentFlags;
// 	DWORD GradientColor;
// 	DWORD AnimationId;
// } ACCENT_POLICY;
// 
// typedef BOOL(WINAPI*pfnSetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
// HMODULE hUser = GetModuleHandle(TEXT("user32.dll"));
// pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");

int WINAPI _tWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPTSTR lpCmdLine,
					 _In_ int nShowCmd) {

	MacStyleGUI::Graphics::Initialize();
	MacStyleGUI::Forms::MacStyleForm test(CW_USEDEFAULT, CW_USEDEFAULT, 800, 600);
	test.CreateForm();

// 	if (hUser && setWindowCompositionAttribute) {
// 		ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000000	Unknown
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000001	Unknown
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000002	use specified color
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000004	blur the entire screen, but task bar will not blur, and hwnd area will not change.
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000008	Unknown
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000010	Unknown
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000020	DrawLeftBorder
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000040	DrawTopBorder
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000080	DrawRightBorder
// 		//ACCENT_ENABLE_BLURBEHIND	0x00000100	DrawBottomBorder
// 
// 		WINDOWCOMPOSITIONATTRIBDATA data = { };
// 		data.Attrib = WCA_ACCENT_POLICY;
// 		data.pvData = &accent;
// 		data.cbData = sizeof(accent);
// 		if (setWindowCompositionAttribute(test.GetHwnd(), &data) == FALSE) return GetLastError();
// 	}

	ShowWindow(test.GetHwnd(), nShowCmd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}