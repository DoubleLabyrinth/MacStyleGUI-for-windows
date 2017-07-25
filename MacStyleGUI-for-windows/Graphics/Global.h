#pragma once
#include <wrl.h>
#include <windows.h>
#include <d3d11.h>
#include <d2d1_3.h>
#include <dcomp.h>

namespace MacStyleGUI::Graphics {
	extern Microsoft::WRL::ComPtr<ID3D11Device> Global_D3DDevice;
	extern Microsoft::WRL::ComPtr<IDXGIDevice2> Global_DXGIDevice;
	extern Microsoft::WRL::ComPtr<ID2D1Device2> Global_D2DDevice;
	extern Microsoft::WRL::ComPtr<IDCompositionDesktopDevice> Global_DCompoDesktopDevice;
	extern Microsoft::WRL::ComPtr<IDCompositionDevice3> Global_DCompoDevice;

	extern Microsoft::WRL::ComPtr<ID2D1Factory3> Global_D2DFactory;

	HRESULT Initialize();
}