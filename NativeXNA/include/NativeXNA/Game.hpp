#pragma once

#include "NativeXNA/Runtime.hpp"
#include "NativeXNA/Framework.hpp"

namespace NativeXNA {

    struct GameTime {
        float ElapsedTime;
    };

    class NATIVEXNA_API GameWindow {
    public:
        GameWindow(std::string_view title, int width, int height);
        ~GameWindow();

        // Sets the title of the system window
        void SetTitle(std::string_view pszTitle);

        std::string GetTitle() const;

        Rectangle GetClientBounds() const;

        // @returns Platform-specific GameWindow handle. 
        IntPtr GetHandle() const { return m_Handle; }

        // Raised when the GameWindow is about to close.
        Event<> Closed;

        // Raised when the size of the GameWindow changes.
        Event<> ClientSizeChanged;

    private:
        IntPtr m_Handle;
    };

    class NATIVEXNA_API Game {
    public:
        Game() = default;
        virtual ~Game() = default;

        void Run();
        void Exit() { m_IsRunning = false; }
        void Tick();

        Ref<GameWindow> Window;

    protected:
        virtual void Update(GameTime gameTime) {}
        virtual void Draw(GameTime gameTime) {}

    private:
        bool m_IsRunning;
    };

}