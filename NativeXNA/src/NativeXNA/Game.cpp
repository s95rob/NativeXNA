#include "NativeXNA/Game.hpp"
#include "NativeXNA/Platform.hpp"

namespace NativeXNA {

    void Game::Run() {
        Window = MakeRef<GameWindow>("Game", 1280, 720);
        Window->Closed += [&]() { m_IsRunning = false; };

        while(m_IsRunning) {
            Platform::ProcessWindowMessages(Window->GetHandle());
            Tick();
        }
    }

    void Game::Tick() {
        // TODO: fill out gameTime struct
        GameTime gameTime = {};
        Update(gameTime);
        Draw(gameTime);
    }

}