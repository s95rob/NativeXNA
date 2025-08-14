#pragma once

#include "NativeXNA/Graphics.hpp"
#include "D3D11Include.hpp"

namespace NativeXNA {

    using D3D11GraphicsDevice = GraphicsDevice;

    template <>
    struct NATIVEXNA_API PlatformData<D3D11GraphicsDevice> {
        ID3D11Device* pDevice;
        ID3D11DeviceContext* pContext;
        IDXGISwapChain* pSwapchain;
        ID3D11RenderTargetView* pBackbufferView;
    };

	using D3D11GraphicsDeviceManager = GraphicsDeviceManager;

}