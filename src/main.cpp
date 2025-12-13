#include "raylib.h"
#include "world.hpp"

int main() {
  const int width = 1200;
  const int height = 800;
  auto w = MakeWorld();
  Camera2D camera = {
      .offset = {(float)width/2, (float)height/2},
      .target = w.getFocus(),
      .rotation = 0,
      .zoom = 1
  };
  InitWindow(width, height, "spaceship");
  SetTargetFPS(144);
  while (!WindowShouldClose()) {
    camera.target = w.getFocus();
    int gridOriginX = (((int)camera.target.x - width/2)/100)*100;
    int gridOriginY = (((int)camera.target.y - height/2)/100)*100;
    w.HandleInput();
    w.Tick(GetFrameTime());
    BeginDrawing(); {
    BeginMode2D(camera); {

      ClearBackground(WHITE);

      for (int x = gridOriginX - 100; x <= gridOriginX + width; x+=100)
          DrawLine(x, gridOriginY - 100, x, gridOriginY + height ,BLACK);
      for (int y = gridOriginY - 100; y <= gridOriginY + height; y+=100)
          DrawLine(gridOriginX - 100, y, gridOriginX + width, y, BLACK);

      w.Draw();

    }
    EndMode2D();
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
