#pragma once

#include "NativeXNA/Runtime.hpp"

namespace NativeXNA {

    struct PresentationParameters {
        int BackBufferCount;
        IntPtr DeviceWindowHandle;
    };

    class NATIVEXNA_API GraphicsDevice : public PlatformImplementation<GraphicsDevice>, public IDisposable {
    public:
        GraphicsDevice(const PresentationParameters& presentationParameters);

        virtual void Dispose() override;
    };

    class IGraphicsDeviceService {
    public:
        virtual ~IGraphicsDeviceService() = default;

        virtual Ref<GraphicsDevice> GetGraphicsDevice() const = 0;
    };

    class IGraphicsDeviceManager {
    public:
        virtual ~IGraphicsDeviceManager() = default;

        virtual void CreateDevice() = 0;
        virtual bool BeginDraw() = 0;
        virtual void EndDraw() = 0;
    };

    class Game;
    
    class NATIVEXNA_API GraphicsDeviceManager : public IGraphicsDeviceService, public IDisposable, public IGraphicsDeviceManager {
    public:
        GraphicsDeviceManager(Game* pGame);

        virtual void CreateDevice() override;
        virtual bool BeginDraw() override { return true; }
        virtual void EndDraw() override;

        virtual void Dispose() override { m_GraphicsDevice->Dispose(); }

        virtual Ref<GraphicsDevice> GetGraphicsDevice() const override { return m_GraphicsDevice; }

    private:
        Game* m_pGame;
        Ref<GraphicsDevice> m_GraphicsDevice;
    };

}