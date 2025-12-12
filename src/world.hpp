#ifndef _WORLD_H_
#define _WORLD_H_

#include <memory>
#include <vector>
#include <functional>
#include <array>
#include "raylib.h"
#include "entity.hpp"
#include "ship.hpp"

class World {
private:
  std::vector<std::shared_ptr<Ticker>> tickers;
  std::vector<std::shared_ptr<Drawable>> drawables;
  std::vector<std::shared_ptr<InputSubscriber>> inputSubs;
  static constexpr std::array inputs{
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D
  };
  std::function<Vector2(void)> focusCallable;

public:
  World() {}; // Make a singleton?
  void addTicker(std::shared_ptr<Ticker> ticker) {
    tickers.push_back(std::move(ticker));
  }
  void addDrawable(std::shared_ptr<Drawable> drawable) {
    drawables.push_back(std::move(drawable));
  }
  void addInputSubscriber(std::shared_ptr<InputSubscriber> inputSub) {
    inputSubs.push_back(std::move(inputSub));
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
  void setFocusCallable(std::function<Vector2(void)> callable) {
    focusCallable = callable;
  }
  Vector2 getFocus() {
    return focusCallable();
  }
  void HandleInput() {
    for (auto& key : inputs) {
      if (!IsKeyPressed(key)) continue;
      for (auto& inputSub : inputSubs) {
        if (inputSub->HandleInput(key)) break;
      }
    }
  }
};

World MakeWorld() {
  auto world = World();
  auto ship = std::make_shared<Ship>();
  ship->applyThrust(2);
  world.addTicker(ship);
  world.addDrawable(ship);
  world.addInputSubscriber(ship);
  world.setFocusCallable([ship] {return ship->getPos();});
  return world;
}

#endif
