#ifndef _WORLD_H_
#define _WORLD_H_

#include <memory>
#include "entity.hpp"
#include "ship.hpp"
#include <vector>

class World {
private:
  std::vector<std::shared_ptr<Ticker>> tickers;
  std::vector<std::shared_ptr<Drawable>> drawables;

public:
  World() {}; // Make a singleton?
  void addTicker(std::shared_ptr<Ticker> ticker) {
    tickers.push_back(std::move(ticker));
  }
  void addDrawable(std::shared_ptr<Drawable> drawable) {
    drawables.push_back(std::move(drawable));
  }
  void Tick(float time) {
    for (auto& ticker : tickers) {
      ticker->Tick(time);
    }
  }
  void Draw() {
    for (auto& drawable : drawables) {
      drawable->Draw();
    }
  }
};

World MakeWorld() {
  auto world = World();
  auto ship = std::make_shared<Ship>();
  ship->applyThrust(2);
  world.addTicker(ship);
  world.addDrawable(ship);
  return world;
}

#endif
