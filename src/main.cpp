#include "raylib.h"
#include "world.hpp"

int main() {
    const int width = 1200;
    const int height = 800;
    auto w = MakeWorld();
    Camera2D camera = {
        .offset = {width/2, height/2},
        .target = w.getFocus(),
        .rotation = 0,
        .zoom = 1
    };
    InitWindow(width, height, "spaceship");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        camera.target = w.getFocus();
        w.HandleInput();
        w.Tick(GetFrameTime());
        BeginDrawing();
        BeginMode2D(camera);
        for (int i = -1000; i < 1000; i++) {
            DrawLine(i*100, 100000, i*100, -100000, BLACK);
        }
        for (int i = -1000; i < 1000; i++) {
            DrawLine(-100000, 100*i, 100000, 100*i, BLACK);
        }
        ClearBackground(WHITE);
        w.Draw();
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
