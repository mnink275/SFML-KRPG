#include <World.hpp>

#include <memory>

#include <SFML/Graphics/Texture.hpp>

#include <Commands/Category/Category.hpp>
#include <Components/KeyboardInput.hpp>
#include <Components/PlayerCombat.hpp>
#include <Components/PlayerGraphics.hpp>
#include <Components/PlayerPhysics.hpp>
#include <Resource/ResourceIdentifiers.hpp>

namespace ink {

World::World(sf::RenderWindow& window)
    : window_(window),
      world_view_(window.getDefaultView()),
      world_bounds_({0.f, 0.f},
                    {world_view_.getSize().x, world_view_.getSize().y}),
      spawn_position_(world_view_.getSize().x / 2.f,
                      world_bounds_.height - world_view_.getSize().y / 2.f),
      player_(nullptr),
      room_manager_(scene_graph_, world_bounds_, textures_) {
  loadTextures();
  buildScene();
  world_view_.setCenter(spawn_position_);
}

void World::update(const sf::Time dt) {
  boundChecking();
  checkDoorInteraction();

  while (!command_queue_.isEmpty()) {
    scene_graph_.onCommand(command_queue_.pop(), dt);
  }

  player_->handleRealtimeInput(command_queue_);
  scene_graph_.update(dt, command_queue_);
}

void World::checkDoorInteraction() {
  if (interact_with_) {
    interact_with_ = false;
    room_manager_.checkDoorInteraction();
  }
}

void World::draw() const {
  window_.setView(world_view_);
  window_.draw(scene_graph_);
}

void World::handlePlayerInput(const sf::Keyboard::Key key,
                              const bool is_pressed) {
  switch (key) {
    case sf::Keyboard::Key::A:
    case sf::Keyboard::Key::D:
    case sf::Keyboard::Key::W:
    case sf::Keyboard::Key::S:
    case sf::Keyboard::Key::Space:
      player_->handlePlayerInput(command_queue_, key, is_pressed);
      break;
    case sf::Keyboard::Key::E:
      interact_with_ = is_pressed;
      break;
    default:
      std::cout << "The key isn't implemented!\n";
  }
}

void World::loadTextures() {
  const auto kTexturePath = std::string(RESOURCE_FOLDER);
  textures_.load(Textures::kDesert, kTexturePath + "/texture/DesertFloor.jpg");
  textures_.load(Textures::kStone, kTexturePath + "/texture/StoneFloor.jpg");
  textures_.load(Textures::kLava, kTexturePath + "/texture/LavaFloor.png");
  textures_.load(Textures::kPeepoLeft,
                 kTexturePath + "/texture/StaregeGun64x64Left.png");
  textures_.load(Textures::kPeepoRight,
                 kTexturePath + "/texture/StaregeGun64x64Right.png");
  textures_.load(Textures::kDoor, kTexturePath + "/texture/Door.png");
  textures_.load(Textures::kBullet, kTexturePath + "/texture/Bullet16x16T.png");
}

void World::buildScene() {
  // create and connect the rooms
  room_manager_.createInitialRoom();

  // add the player
  auto player = std::make_unique<Player>(
      std::make_unique<component::PlayerPhysics>(),
      std::make_unique<component::PlayerGraphics>(
          textures_.get(Textures::kPeepoLeft),
          textures_.get(Textures::kPeepoRight), true),
      std::make_unique<component::KeyboardInput>(),
      std::make_unique<component::PlayerCombat>(textures_), textures_,
      NodeCategory::Player);
  player_ = player.get();
  player_->setPosition(spawn_position_);

  room_manager_.attachPlayer(std::move(player));
}

void World::boundChecking() const {
  const auto& position = player_->getPosition();
  if (position.x < 0)
    player_->setPosition({0, position.y});
  else if (position.x > world_bounds_.width)
    player_->setPosition({world_bounds_.width, position.y});
  if (position.y < 0)
    player_->setPosition({position.x, 0});
  else if (position.y > world_bounds_.height)
    player_->setPosition({position.x, world_bounds_.height});
}

}  // namespace ink
