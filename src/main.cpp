
#include "Engine.h"
#include <iostream>

int main() {
    Engine engine;
    if (!engine.Init()) {
        return -1;
    }
    engine.Run();
    engine.Shutdown();
    return 0;
}
