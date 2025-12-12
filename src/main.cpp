#include "raylib.h"
#include "world.hpp"

int main() {
    const int width = 1200;
    const int height = 800;
    auto w = MakeWorld();
    InitWindow(width, height, "spaceship");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        w.Tick(GetFrameTime());
        w.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
