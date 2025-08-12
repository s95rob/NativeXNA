#include "NativeXNA/Graphics.hpp"
#include "NativeXNA/Game.hpp"

namespace NativeXNA {

    GraphicsDeviceManager::GraphicsDeviceManager(Game* pGame) 
        : m_pGame(pGame) {
        pGame->Services.AddService<GraphicsDeviceManager>(this);
        CreateDevice();
    }

    void GraphicsDeviceManager::CreateDevice() {
        PresentationParameters params = {};
        params.BackBufferCount = 2;
        params.DeviceWindowHandle = m_pGame->Window->GetHandle();

        m_GraphicsDevice = MakeRef<GraphicsDevice>(params);
    }

}