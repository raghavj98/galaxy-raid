#ifndef _WORLD_H_
#define _WORLD_H_

#include <memory>
#include <vector>
#include <functional>
#include <array>
#include <map>
#include "raylib.h"
#include "entity.hpp"

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
  std::map<InputState, std::function<bool(int)>> getInputStateMap = {
    {InputState::DOWN, [](int key){return IsKeyDown(key);}},
    {InputState::PRSD, [](int key){return IsKeyPressed(key);}},
    {InputState::PRPT, [](int key){return IsKeyPressedRepeat(key);}},
  };
  std::map<int, int> customBinds = {};

public:
  World() {}; // Make a singleton?
  void addTicker(std::shared_ptr<Ticker> ticker);
  void addDrawable(std::shared_ptr<Drawable> drawable);
  void addInputSubscriber(std::shared_ptr<InputSubscriber> inputSub);
  void Tick(float time);
  void Draw();
  void setFocusCallable(std::function<Vector2(void)> callable);
  Vector2 getFocus();
  void HandleInput();

  void setCustomBind(int original, int rebind) {
    customBinds[original] =  rebind;
  }
};

World MakeWorld();


#endif
