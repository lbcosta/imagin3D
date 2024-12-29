#include "engine/Engine.h"

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;

int main()
{
    auto engine = Engine(WINDOW_WIDTH, WINDOW_HEIGHT);

    /*
     *
     * Here the magic happens.
     *
     */

    engine.Run();
    return 0;
}

