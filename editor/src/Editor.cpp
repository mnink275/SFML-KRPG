#include <Editor.hpp>

#include <algorithm>
#include <fstream>

#include <fmt/format.h>

namespace ink {

namespace {

void writeFileContent(const std::string& path, const std::string& content) {
  std::ofstream of_stream(path, std::ios::trunc);
  if (!of_stream.is_open()) {
    throw std::runtime_error(
        fmt::format("Error opening the file for writing: '{}'", path));
  }
  of_stream << content;
}

constexpr auto kFramePerSecond = 60.f;

constexpr auto kWidth = 1280u;
constexpr auto kHeight = 720u;

}  // namespace

Editor::Editor()
    : kTimePerFrame(sf::seconds(1.f / kFramePerSecond)),
      window_(sf::VideoMode({kWidth, kHeight}), "KRPG-Editor",
              sf::Style::Close),
      active_wall_it_(walls_.end()) {
  window_.setPosition({0, 0});
}

void Editor::run() {
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

void Editor::processEvents() {
  sf::Event event{};
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::MouseMoved:
        last_mouse_pos_ =
            sf::Vector2f{sf::Vector2i{event.mouseMove.x, event.mouseMove.y}};
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

void Editor::update(const sf::Time /*dt*/) {}

void Editor::render() {
  static constexpr auto kBackgroundColor = sf::Color{169, 169, 169};
  window_.clear(kBackgroundColor);

  for (auto&& wall : walls_) {
    wall.draw(window_);
  }

  window_.setView(window_.getDefaultView());
  window_.display();
}

void Editor::handleMouseInput(const sf::Event::MouseButtonEvent event,
                              bool is_pressed) {
  if (!is_pressed) {
    fmt::println("Wall deactivated");
    active_wall_it_ = walls_.end();
    return;
  }

  const auto mouse_pos = sf::Vector2f{sf::Vector2i{event.x, event.y}};
  active_wall_it_ = tryFindActiveWall(mouse_pos);
  if (active_wall_it_ == walls_.end()) return;
  fmt::println("Wall activated");

  switch (event.button) {
    case sf::Mouse::Left:
      active_wall_it_->setShift(mouse_pos);
      break;
    case sf::Mouse::Right:
      // NOLINTNEXTLINE (readability-magic-numbers)
      active_wall_it_->rotate(sf::degrees(90.f));
      break;
    default:
      break;
  }
}

void Editor::handleKeyPressed(const sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::C:
      createNewWall();
      break;
    case sf::Keyboard::S:
      serialize();
      break;
    default:
      break;
  }
}

void Editor::createNewWall() {
  const auto position = last_mouse_pos_;
  const auto size = sf::Vector2f{10.f, 200.f};
  walls_.emplace_back(position, size);

  fmt::println("Wall created");
  fmt::println("Position: ({}, {}), Size: ({}, {})", position.x, position.y,
               size.x, size.y);
}

Editor::WallIter Editor::tryFindActiveWall(const sf::Vector2f mouse_pos) {
  return std::find_if(walls_.begin(), walls_.end(),
                      [&mouse_pos](const Wall& wall) {
                        auto rect = wall.getBoundingRect();
                        return rect.contains(mouse_pos);
                      });
}

void Editor::serialize() const {
  std::string data;
  for (auto&& wall : walls_) {
    // template:
    // {left} {top} {width} {height}\n
    const auto rect = wall.getBoundingRect();
    auto row = fmt::format("{} {} {} {}\n", rect.left, rect.top, rect.width,
                           rect.height);
    data.append(row);
  }

  static constexpr std::string_view kPath = "./data/editor_walls.txt";
  writeFileContent(std::string{kPath}, data);

  fmt::println("Editor state has been saved");
}

}  // namespace ink
