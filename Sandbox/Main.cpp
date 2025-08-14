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

    virtual void Draw(GameTime gameTime) override {
        graphics->GetGraphicsDevice()->Clear(Color(1.0f, 0.0f, 1.0f, 1.0f));
    }

    Ref<GraphicsDeviceManager> graphics;
};

int main(int argc, char** argv) {
    MyGame game;
    game.Run();

    return 0;
}