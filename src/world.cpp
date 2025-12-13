#include "world.hpp"
#include "ship.hpp"

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

void World::addTicker(std::shared_ptr<Ticker> ticker) {
  tickers.push_back(std::move(ticker));
}
void World::addDrawable(std::shared_ptr<Drawable> drawable) {
  drawables.push_back(std::move(drawable));
}
void World::addInputSubscriber(std::shared_ptr<InputSubscriber> inputSub) {
  inputSubs.push_back(std::move(inputSub));
}
void World::Tick(float time) {
  for (auto& ticker : tickers) {
    ticker->Tick(time);
  }
}
void World::Draw() {
  for (auto& drawable : drawables) {
    drawable->Draw();
  }
}
void World::setFocusCallable(std::function<Vector2(void)> callable) {
  focusCallable = callable;
}
Vector2 World::getFocus() {
  return focusCallable();
}
void World::HandleInput() {
  for (auto& key : inputs) {
    if (!IsKeyPressed(key)) continue;
    for (auto& inputSub : inputSubs) {
      if (inputSub->HandleInput(key)) break;
    }
  }
}
