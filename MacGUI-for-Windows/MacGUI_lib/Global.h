#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include <vector>
#include <windows.h>
#include <d2d1_3.h>
#include <d3d11_4.h>
#include <dxgi1_5.h>


namespace MacGUI::Global {
	extern std::vector<IDXGIAdapter1*> DXAdapters;

	extern IDXGIFactory5* DXGIFactory;
	extern IDXGIDevice2* DXGIDevice;
		
	extern ID2D1Factory3* D2DFactory;

	extern FLOAT Desktop_DpiX;
	extern FLOAT Desktop_DpiY;

	extern HRESULT InitialFactories(D2D1_FACTORY_TYPE D2DFactoryType);
	extern UINT EnumAllAdapters();
	extern HRESULT InitialDxDevice(IDXGIAdapter* pAdapters, UINT D3D11CreateDeviceFlags);
	extern HRESULT InitialOthers();
}