#include "Platform/D3D11/D3D11Graphics.hpp"

namespace NativeXNA {

    D3D11GraphicsDevice::GraphicsDevice(const PresentationParameters& presentationParameters) {
        // Create the device, context and swapchain
        DXGI_SWAP_CHAIN_DESC scd = {};
        scd.BufferCount = presentationParameters.BackBufferCount;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // TODO: should really be polled
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.OutputWindow = (HWND)presentationParameters.DeviceWindowHandle;
        scd.SampleDesc.Count = 1;
        scd.Windowed = true;    // TODO: add params
        scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // TODO: add params

        UINT deviceFlags = 0;

        #ifdef NATIVEXNA_DEBUG
            deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        #endif

        HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr,
            D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags, nullptr, 0,
            D3D11_SDK_VERSION, &scd, &m_PlatformData->pSwapchain, 
            &m_PlatformData->pDevice, nullptr, &m_PlatformData->pContext);

        NATIVEXNA_ASSERT(result == S_OK);

        // Create the backbuffer view
		ID3D11Texture2D* backbuffer = nullptr;
		result = m_PlatformData->pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
		NATIVEXNA_ASSERT(result == S_OK);

		result = m_PlatformData->pDevice->CreateRenderTargetView(backbuffer, nullptr, &m_PlatformData->pBackbufferView);
		backbuffer->Release();
		NATIVEXNA_ASSERT(result == S_OK);
    }

    void D3D11GraphicsDevice::Dispose() {
		if (m_PlatformData->pBackbufferView)
			m_PlatformData->pBackbufferView->Release();
        m_PlatformData->pSwapchain->Release();
        m_PlatformData->pContext->Release();
        m_PlatformData->pDevice->Release();
    }

	void D3D11GraphicsDevice::Clear(const Color& color) {
		// TODO: check for bound backbuffer or render targets
		m_PlatformData->pContext->ClearRenderTargetView(m_PlatformData->pBackbufferView,
			reinterpret_cast<const float*>(&color));
	}

	bool D3D11GraphicsDeviceManager::BeginDraw() {
        // Bind the backbuffer
		m_GraphicsDevice->GetPlatformData().pContext->OMSetRenderTargets(1, &m_GraphicsDevice->GetPlatformData().pBackbufferView, nullptr);
        return true;
	}


    void D3D11GraphicsDeviceManager::EndDraw() {
        // Present the swapchain
        m_GraphicsDevice->GetPlatformData().pSwapchain->Present(1, 0);
    }

}