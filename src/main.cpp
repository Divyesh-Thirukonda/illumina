#include "Engine.h"

int main() {
    Engine engine;
    if (!engine.OpenProject(".")) return -1;
    if (!engine.Init()) return -1;
    engine.Run();
    return 0;
}
