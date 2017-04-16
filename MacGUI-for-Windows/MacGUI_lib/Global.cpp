#include "Global.h"

namespace MacGUI::Global {

	IDXGIFactory5* DXGI_Factory = nullptr;
	IDXGIDevice2* DXGI_Device = nullptr;

	ID3D11Device* D3D_Device = nullptr;

	ID2D1Factory3* D2D_Factory = nullptr;

	FLOAT Desktop_DpiX = 0.0f;
	FLOAT Desktop_DpiY = 0.0f;

	HRESULT InitialGlobal() {
		HRESULT hr = S_OK;

		hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&DXGI_Factory));
		MACGUI_IF_FAILED_THEN_RETURN(hr);

		hr = D3D11CreateDevice(nullptr,
							   D3D_DRIVER_TYPE_HARDWARE,
							   NULL,
							   D3D11_CREATE_DEVICE_BGRA_SUPPORT,
							   nullptr,
							   0,
							   D3D11_SDK_VERSION,
							   &D3D_Device, 
							   nullptr, 
							   nullptr);
		MACGUI_IF_FAILED_THEN_RETURN(hr);

		hr = D3D_Device->QueryInterface(IID_PPV_ARGS(&DXGI_Device));
		MACGUI_IF_FAILED_THEN_RETURN(hr);

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2D_Factory);
		MACGUI_IF_FAILED_THEN_RETURN(hr);

		D2D_Factory->GetDesktopDpi(&Desktop_DpiX, &Desktop_DpiY);
		
		return hr;
	}
}