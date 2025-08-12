#include "NativeXNA/Game.hpp"
#include "NativeXNA/Platform.hpp"
#include "NativeXNA/Graphics.hpp"

namespace NativeXNA {

    Game::Game() {
        Window = MakeRef<GameWindow>("Game", 1280, 720);
        Window->Closed += [&](const EventArgs&) { m_IsRunning = false; };
    }

    void Game::Run() {
        Initialize();
        LoadContent();

        while(m_IsRunning) {
            Platform::ProcessWindowMessages(Window->GetHandle());
            Tick();
        }
    }

    void Game::Tick() {
        // TODO: fill out gameTime struct
        GameTime gameTime = {};
        Update(gameTime);

        BeginDraw();
        Draw(gameTime);
        EndDraw();
    }

    void Game::BeginDraw() {
        auto* graphicsDeviceManager = Services.GetService<GraphicsDeviceManager>();
        if (graphicsDeviceManager)
            graphicsDeviceManager->BeginDraw();
    }

    void Game::EndDraw() {
        auto* graphicsDeviceManager = Services.GetService<GraphicsDeviceManager>();
        if (graphicsDeviceManager)
            graphicsDeviceManager->EndDraw();
    }

}