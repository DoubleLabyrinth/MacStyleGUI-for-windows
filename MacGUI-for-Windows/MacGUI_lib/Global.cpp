#include "Global.h"



namespace MacGUI::Global {
	std::vector<IDXGIAdapter1*> DXAdapters;

	IDXGIFactory5* DXGIFactory = nullptr;
	ID2D1Factory3* D2DFactory = nullptr;

	IDXGIDevice2* DXGIDevice = nullptr;

	FLOAT Desktop_DpiX = 0.0f;
	FLOAT Desktop_DpiY = 0.0f;

	HRESULT InitialFactories(D2D1_FACTORY_TYPE D2DFactoryType) {
		HRESULT hr = S_OK;

		hr = CreateDXGIFactory(IID_PPV_ARGS(&DXGIFactory));
		if (FAILED(hr)) return hr;

		hr = D2D1CreateFactory(D2DFactoryType, &D2DFactory);
		/*if (FAILED(hr))*/ return hr;
	}

	UINT EnumAllAdapters() {
		if (DXGIFactory == nullptr) return 0xFFFFFFFF;
		if (DXAdapters.size() != 0) return 0xFFFFFFFF - 1;

		UINT ret = 0;
		for ( ; ; ret++) {
			IDXGIAdapter1* tempAdapters = nullptr;
			if (DXGIFactory->EnumAdapters1(ret, &tempAdapters) == DXGI_ERROR_NOT_FOUND) break;
			DXAdapters.push_back(tempAdapters);
		}

		return ret;
	}

	HRESULT InitialDxDevice(IDXGIAdapter* pAdapters, UINT D3D11CreateDeviceFlags) {
		HRESULT hr = S_OK;

		ID3D11Device* tempD3DDevice = nullptr;
		hr = D3D11CreateDevice(pAdapters,					// Specified by the argument "pAdapters".
							   D3D_DRIVER_TYPE_UNKNOWN,		// Must be "D3D_DRIVER_TYPE_UNKNOWN", otherwise fail. Described at https://msdn.microsoft.com/en-us/library/windows/desktop/ff476082(v=vs.85).aspx
							   NULL,						// We do not use software to implement DirectX.
							   D3D11CreateDeviceFlags,		// Specified by the argument "D3D11CreateDeviceFlags".
							   nullptr,						// Use default D3D feature levels.
							   0,							// Use default D3D feature levels.
							   D3D11_SDK_VERSION,			// Must be "D3D11_SDK_VERSION". Described at https://msdn.microsoft.com/en-us/library/windows/desktop/ff476082(v=vs.85).aspx
							   &tempD3DDevice,				// Output D3D device.
							   nullptr,						// Output the first D3D_FEATURE_LEVEL from the pFeatureLevels array which succeeded. But we do not need it.
							   nullptr);					// We do not need D3D device context.
		if (FAILED(hr)) return hr;

		hr = tempD3DDevice->QueryInterface(IID_PPV_ARGS(&DXGIDevice));
		/*if (FAILED(hr))*/ return hr;
	}

	HRESULT InitialOthers() {
		HRESULT hr = S_OK;

		D2DFactory->GetDesktopDpi(&Desktop_DpiX, &Desktop_DpiY);

		return hr;
	}
}