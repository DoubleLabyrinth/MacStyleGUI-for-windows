#include "MacGUI_lib/Global.h"
#include "MacGUI_lib/Forms/MacForm/MacForm.h"

int WINAPI _tWinMain(_In_ HINSTANCE hInstance, 
					 _In_opt_ HINSTANCE hPrevInstance, 
					 _In_ LPTSTR lpCmdLine, 
					 _In_ int nShowCmd) {

	MacGUI::Global::InitialGlobal();

	MacGUI::Forms::MacForm* testForm = new MacGUI::Forms::MacForm();
	testForm->CreateInstance(TEXT("testWindow"),
							 150, 150,
							 500, 600);
	ShowWindow(testForm->Get_Hwnd(), SW_NORMAL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	delete testForm;
	return 0;
}