#include <Game.hpp>

#include <stdexcept>

namespace ink {

namespace {

constexpr auto kFramePerSecond = 60.f;

constexpr auto kWindowSizes = sf::Vector2u{1280u, 720u};

}  // namespace

Game::Game()
    : kTimePerFrame(sf::seconds(1.f / kFramePerSecond)),
      kResourcePath(RESOURCE_FOLDER),
      textures_(loadTextures()),
      fonts_(loadFonts()),
      window_(sf::VideoMode(kWindowSizes), "KRPG", sf::Style::Close),
      world_(window_, textures_, fonts_),
      statistics_text_(fonts_.get(Fonts::kExpressway)),
      statistics_update_time_(),
      statistics_num_frames_(0) {
  statistics_text_.setPosition({5.0f, 5.0f});
  statistics_text_.setFillColor(sf::Color::Red);
  statistics_text_.setCharacterSize(15);

  window_.setPosition({0, 0});
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
        world_.handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        world_.handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        window_.close();
        break;
      default:
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

TextureHolder Game::loadTextures() {
  TextureHolder textures;
  textures.load(Textures::kDesert, kResourcePath + "/texture/DesertFloor.jpg");
  textures.load(Textures::kStone, kResourcePath + "/texture/StoneFloor.jpg");
  textures.load(Textures::kLava, kResourcePath + "/texture/LavaFloor.png");
  textures.load(Textures::kPeepoLeft,
                kResourcePath + "/texture/StaregeGun64x64Left.png");
  textures.load(Textures::kPeepoRight,
                kResourcePath + "/texture/StaregeGun64x64Right.png");
  textures.load(Textures::kDoor, kResourcePath + "/texture/Door.png");
  textures.load(Textures::kBullet, kResourcePath + "/texture/Bullet16x16T.png");
  textures.load(Textures::kWall,
                kResourcePath + "/texture/BlackSquare64x64.png");
  textures.load(Textures::kIce, kResourcePath + "/texture/Ice64x64.png");
  textures.load(Textures::kStoneOnGrass,
                kResourcePath + "/texture/StoneOnGrass256x256.png");
  textures.load(Textures::kPlayerIdle,
                kResourcePath + "/texture/PlayerIdle96x96.png");
  textures.load(Textures::kPlayerRun,
                kResourcePath + "/texture/PlayerRun96x96.png");
  textures.load(Textures::kPlayerSwordAttack,
                kResourcePath + "/texture/PlayerSwordAttack96x96.png");

  // debug
  textures.load(Textures::kSwordHitArea, kResourcePath + "/texture/Door.png");

  return textures;
}

FontHolder Game::loadFonts() {
  FontHolder fonts;
  fonts.load(Fonts::kArial, kResourcePath + "/font/Arial.ttf");
  fonts.load(Fonts::kExpressway, kResourcePath + "/font/Expressway.ttf");
  fonts.load(Fonts::kSansation, kResourcePath + "/font/Sansation.ttf");

  return fonts;
}

}  // namespace ink
