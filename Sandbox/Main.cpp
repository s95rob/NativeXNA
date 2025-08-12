#include "NativeXNA/Game.hpp"
#include "NativeXNA/Graphics.hpp"

using namespace NativeXNA;

class MyGame : public Game {
public:
    MyGame() {
        graphics = MakeRef<GraphicsDeviceManager>(this);
    }

    ~MyGame() {
        graphics->Dispose();
    }

    Ref<GraphicsDeviceManager> graphics;
};

int main(int argc, char** argv) {
    MyGame game;
    game.Run();

    return 0;
}