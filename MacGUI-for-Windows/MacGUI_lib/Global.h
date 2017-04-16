#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <d2d1_3.h>
#include <d3d11_4.h>
#include <dxgi1_5.h>

#define MACGUI_IF_FAILED_THEN_RETURN(x) if(FAILED(x)) return x

namespace MacGUI::Global {
		extern IDXGIFactory5* DXGI_Factory;
		extern IDXGIDevice2* DXGI_Device;

		extern ID3D11Device* D3D_Device;
		
		extern ID2D1Factory3* D2D_Factory;

		extern FLOAT Desktop_DpiX;
		extern FLOAT Desktop_DpiY;

		extern HRESULT InitialGlobal();
}