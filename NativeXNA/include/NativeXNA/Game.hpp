#pragma once

#include "NativeXNA/Runtime.hpp"
#include "NativeXNA/Framework.hpp"

#include <any>
#include <typeindex>

namespace NativeXNA {

    class Game;

    class GameChild {
    public:
        virtual ~GameChild() = default;

        Game* GetGame() { return m_pGame; }
        const Game* GetGame() const { return m_pGame; }

    protected:
        GameChild(Game* pGame)
            : m_pGame(pGame) {}

    protected:
        Game* m_pGame;
    };

    struct GameTime {
        float ElapsedTime;
    };

    class NATIVEXNA_API GameWindow : public GameChild {
    public:
        GameWindow(Game* pGame, std::string_view title, int width, int height);
        ~GameWindow();

        // Sets the title of the system window
        void SetTitle(std::string_view title);

        std::string GetTitle() const;

        Rectangle GetClientBounds() const;

        // @returns Platform-specific GameWindow handle. 
        IntPtr GetHandle() const { return m_Handle; }

        // Raised when the GameWindow is about to close.
        EventHandler<EventArgs> Closed;

        // Raised when the size of the GameWindow changes.
        EventHandler<EventArgs> ClientSizeChanged;

    private:
        IntPtr m_Handle;
    };

    class NATIVEXNA_API GameServiceContainer {
    public:
        GameServiceContainer() = default;

        template <typename T>
        void AddService(T* provider) { m_ServiceMap[typeid(T)] = provider; }
        
        template <typename T>
        void RemoveService() { m_ServiceMap.erase(typeid(T)); }

        template <typename T>
        T* GetService() { return std::any_cast<T*>(m_ServiceMap.at(typeid(T))); }

    private:
        std::unordered_map<std::type_index, std::any> m_ServiceMap;
    };

    class NATIVEXNA_API Game {
    public:
        Game();
        virtual ~Game() = default;

        void Run();
        void Exit();
        void Tick();

        GameServiceContainer Services;
        Ref<GameWindow> Window;

        // Raised when the game gains focus.
        EventHandler<EventArgs> Activated;

        // Raised when the game loses focus. 
        EventHandler<EventArgs> Deactivated;

        // Rasied when the game is exiting.
        EventHandler<EventArgs> Exiting;

    protected:
        virtual void Initialize() {}
        virtual void LoadContent() {}

        virtual void BeginDraw();
        virtual void BeginRun() {}
        virtual void Draw(GameTime gameTime) {}
        virtual void EndDraw();

        virtual void Update(GameTime gameTime) {}

    private:
        bool m_IsRunning;
    };

}