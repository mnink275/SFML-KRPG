#include <Game.hpp>

#include <stdexcept>

namespace ink {

Game::Game()
    : window_(sf::VideoMode({1280, 720}), "KRPG", sf::Style::Close),
      world_(window_),
      font_(),
      statistics_text_(font_),
      statistics_update_time_(),
      statistics_num_frames_(0) {
  if (!font_.loadFromFile(std::string(RESOURCE_FOLDER) + "/font/arial.ttf")) {
    throw std::runtime_error("Font loading error");
  }
  statistics_text_.setFont(font_);
  statistics_text_.setPosition({5.f, 5.f});
  statistics_text_.setFillColor(sf::Color::Red);
  statistics_text_.setCharacterSize(15);
}

void Game::run() {
  sf::Clock clock;
  sf::Time time_since_last_update = sf::Time::Zero;
  while (window_.isOpen()) {
    processEvents();
    time_since_last_update += clock.restart();
    updateStatistics(time_since_last_update);
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
      case sf::Event::KeyPressed:
        handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        window_.close();
        break;
      // unused
      case sf::Event::Resized:
      case sf::Event::LostFocus:
      case sf::Event::GainedFocus:
      case sf::Event::TextEntered:
      case sf::Event::MouseWheelScrolled:
      case sf::Event::MouseButtonPressed:
      case sf::Event::MouseButtonReleased:
      case sf::Event::MouseMoved:
      case sf::Event::MouseEntered:
      case sf::Event::MouseLeft:
      case sf::Event::JoystickButtonPressed:
      case sf::Event::JoystickButtonReleased:
      case sf::Event::JoystickMoved:
      case sf::Event::JoystickConnected:
      case sf::Event::JoystickDisconnected:
      case sf::Event::TouchBegan:
      case sf::Event::TouchMoved:
      case sf::Event::TouchEnded:
      case sf::Event::SensorChanged:
      case sf::Event::Count:
        break;
    }
  }
}

void Game::update(const sf::Time elapsed_time) { world_.update(elapsed_time); }

void Game::render() {
  window_.clear();
  world_.draw();

  window_.setView(window_.getDefaultView());
  window_.draw(statistics_text_);
  window_.display();
}

void Game::updateStatistics(const sf::Time elapsed_time) {
  statistics_update_time_ += elapsed_time;
  statistics_num_frames_ += 1;

  if (statistics_update_time_ >= sf::seconds(1.0f)) {
    statistics_text_.setString(
        "Frames / Second = " + std::to_string(statistics_num_frames_) + "\n" +
        "Time / Update = " +
        std::to_string(statistics_update_time_.asMicroseconds() /
                       statistics_num_frames_) +
        "us");

    statistics_update_time_ -= sf::seconds(1.0f);
    statistics_num_frames_ = 0;
  }
}

void Game::handlePlayerInput(const sf::Keyboard::Key key,
                             const bool is_pressed) {
  world_.handlePlayerInput(key, is_pressed);
}

}  // namespace ink
