#include "Core.hpp"

Game::Game()
    : window_(sf::VideoMode(1280, 720), "KRPG", sf::Style::Close),
      world_(window_),
      font_(),
      statistics_text_(),
      statistics_update_time_(),
      statistics_num_frames_(0) {
  font_.loadFromFile(std::string(RESOURCE_FOLDER) + "/font/arial.ttf");
  statistics_text_.setFont(font_);
  statistics_text_.setPosition(5.f, 5.f);
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