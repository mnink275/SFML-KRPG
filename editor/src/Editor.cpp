#include <Editor.hpp>

#include <algorithm>

#include <fmt/format.h>

namespace ink {

Game::Game()
    : kTimePerFrame(sf::seconds(1.f / 60.f)),
      window_(sf::VideoMode({1280, 720}), "KRPG-Editor", sf::Style::Close),
      walls_(),
      active_wall_it_(walls_.end()) {
  window_.setPosition({0, 0});
}

void Game::run() {
  sf::Clock clock;
  sf::Time time_since_last_update = sf::Time::Zero;
  while (window_.isOpen()) {
    processEvents();
    time_since_last_update += clock.restart();
    while (time_since_last_update > kTimePerFrame) {
      time_since_last_update -= kTimePerFrame;
      processEvents();
      update(kTimePerFrame);
      render();
    }
  }
}

void Game::processEvents() {
  sf::Event event{};
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::MouseMoved:
        if (active_wall_it_ == walls_.end()) break;
        active_wall_it_->handleInput(event.mouseMove);
        break;
      case sf::Event::MouseButtonPressed:
        handleMouseInput(event.mouseButton, true);
        break;
      case sf::Event::MouseButtonReleased:
        handleMouseInput(event.mouseButton, false);
        break;
      case sf::Event::KeyPressed:
        handleKeyPressed(event.key.code);
        break;
      case sf::Event::Closed:
        window_.close();
        break;
      default:
        break;
    }
  }
}

void Game::update(const sf::Time /*dt*/) {}

void Game::render() {
  window_.clear(sf::Color{169, 169, 169});

  for (auto&& wall : walls_) {
    wall.draw(window_);
  }

  window_.setView(window_.getDefaultView());
  window_.display();
}

void Game::handleMouseInput(const sf::Event::MouseButtonEvent event,
                              bool is_pressed) {
  if (!is_pressed) {
    fmt::println("Wall deactivated");
    active_wall_it_ = walls_.end();
    return;
  }

  const auto mouse_pos = sf::Vector2f{sf::Vector2i{event.x, event.y}};
  active_wall_it_ = std::find_if(walls_.begin(), walls_.end(),
                                 [&mouse_pos](const Wall& wall) {
                                   auto rect = wall.getBoundingRect();
                                   return rect.contains(mouse_pos);
                                 });
  if (active_wall_it_ != walls_.end()) {
    fmt::println("Wall activated");
    active_wall_it_->setShift(mouse_pos);
  }
}

void Game::handleKeyPressed(const sf::Keyboard::Key key) {
  if (key != sf::Keyboard::C) return;
  auto position = sf::Vector2f{window_.getSize() / 2u};
  auto size = sf::Vector2f{10.f, 200.f};
  walls_.emplace_back(position, size);

  fmt::println("Wall created");
  fmt::println("Position: ({}, {}), Size: ({}, {})", position.x, position.y,
               size.x, size.y);
}

}  // namespace ink
