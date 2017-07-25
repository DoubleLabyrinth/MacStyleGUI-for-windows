#include "Global.h"
#include "..\EventSystem\Global.h"

namespace MacStyleGUI::Graphics {

	Microsoft::WRL::ComPtr<ID3D11Device> Global_D3DDevice;
	Microsoft::WRL::ComPtr<IDXGIDevice2> Global_DXGIDevice;
	Microsoft::WRL::ComPtr<ID2D1Device2> Global_D2DDevice;
	Microsoft::WRL::ComPtr<IDCompositionDesktopDevice> Global_DCompoDesktopDevice;
	Microsoft::WRL::ComPtr<IDCompositionDevice3> Global_DCompoDevice;

	Microsoft::WRL::ComPtr<ID2D1Factory3> Global_D2DFactory;

	HRESULT Initialize() {
		HRESULT hr = S_OK;

// 		typedef enum D3D11_CREATE_DEVICE_FLAG {
// 			D3D11_CREATE_DEVICE_SINGLETHREADED = 0x1,
// 			D3D11_CREATE_DEVICE_DEBUG = 0x2,			
// 			D3D11_CREATE_DEVICE_SWITCH_TO_REF = 0x4,
// 			D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,
// 			D3D11_CREATE_DEVICE_BGRA_SUPPORT = 0x20,
// 			D3D11_CREATE_DEVICE_DEBUGGABLE = 0x40,
// 			D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY = 0x80,
// 			D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT = 0x100,
// 			D3D11_CREATE_DEVICE_VIDEO_SUPPORT = 0x800
// 		} D3D11_CREATE_DEVICE_FLAG;
		hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE,		// Use default hardware adapter
							   NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT,	// No software module, support BGRA
							   nullptr, 0,								// Use default feature levels.
							   D3D11_SDK_VERSION, Global_D3DDevice.ReleaseAndGetAddressOf(), nullptr, nullptr);
		if (FAILED(hr)) 
			return hr;

		hr = Global_D3DDevice.As(&Global_DXGIDevice);
		if (FAILED(hr)) 
			return hr;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, Global_D2DFactory.ReleaseAndGetAddressOf());
		if (FAILED(hr)) 
			return hr;

		hr = Global_D2DFactory->CreateDevice(Global_DXGIDevice.Get(), Global_D2DDevice.ReleaseAndGetAddressOf());
		if (FAILED(hr)) 
			return hr;

		hr = DCompositionCreateDevice3(Global_D2DDevice.Get(), __uuidof(Global_DCompoDesktopDevice),
									   reinterpret_cast<void**>(Global_DCompoDesktopDevice.ReleaseAndGetAddressOf()));
		if (FAILED(hr)) return hr;
		
		hr = Global_DCompoDesktopDevice.As(&Global_DCompoDevice);

		return hr;
	}
}
