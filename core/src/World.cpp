#include <World.hpp>

#include <memory>
#include <set>

#include <fmt/format.h>
#include <SFML/Graphics/Texture.hpp>

#include <Combat/Melee.hpp>
#include <Combat/Projectile.hpp>
#include <Commands/Category/Category.hpp>
#include <Components/Collision/UnitCollision.hpp>
#include <Components/Combat/UnitCombat.hpp>
#include <Components/ComponentManager.hpp>
#include <Components/Graphics/AssetGraphics.hpp>
#include <Components/Graphics/TwoSpriteGraphics.hpp>
#include <Components/Input/AIKeyboardInput.hpp>
#include <Components/Input/EmptyInput.hpp>
#include <Components/Input/KeyboardInput.hpp>
#include <Components/Physics/SimplePhysics.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Utils/Assert.hpp>

namespace ink {

World::World(sf::RenderWindow& window, TextureHolder& textures,
             FontHolder& fonts)
    : window_(window),
      world_view_(window.getDefaultView()),
      textures_(textures),
      fonts_(fonts),
      world_bounds_({0.f, 0.f},
                    {world_view_.getSize().x, world_view_.getSize().y}),
      spawn_position_(world_view_.getSize().x / 2,
                      world_bounds_.height - world_view_.getSize().y / 2),
      player_(nullptr),
      player_vision_(nullptr),
      room_manager_(nullptr) {
  // TODO: make something better
  auto room_manager = std::make_unique<RoomManager>(
      scene_graph_, world_bounds_, textures_, NodeCategory::kRoomManager);
  room_manager_ = room_manager.get();
  scene_graph_.attachChild(std::move(room_manager));

  buildScene();
  world_view_.setCenter(spawn_position_);
}

void World::update(const sf::Time dt) {
  using namespace std::placeholders;
  command_queue_.handle(
      [this](const auto& command, sf::Time time) {
        scene_graph_.onCommand(command, time);
      },
      dt);

  scene_graph_.update(dt, command_queue_);
  handleCollisions();
  scene_graph_.cleanGarbage();
}

bool World::matchesCategories(SceneNode::NodePair& colliders,
                              NodeCategory requested1,
                              NodeCategory requested2) noexcept {
  auto requested1_id = static_cast<CategoryUnderlying>(requested1);
  auto requested2_id = static_cast<CategoryUnderlying>(requested2);
  auto collider1_id =
      static_cast<CategoryUnderlying>(colliders.first->getCategory());
  auto collider2_id =
      static_cast<CategoryUnderlying>(colliders.second->getCategory());
  if (((requested1_id & collider1_id) != 0u) &&
      ((requested2_id & collider2_id) != 0u)) {
    return true;
  }
  if (((requested1_id & collider2_id) != 0u) &&
      ((requested2_id & collider1_id) != 0u)) {
    std::swap(colliders.first, colliders.second);
    return true;
  }

  return false;
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
    case sf::Keyboard::Key::E:
    case sf::Keyboard::Key::Space:
      player_->handleInput(command_queue_, key, is_pressed);
      break;
    default:
      fmt::println("The key wasn't implemented");
  }
}

// TODO: make function more readable
// NOLINTNEXTLINE (readability-function-cognitive-complexity)
void World::handleCollisions() {
  std::set<SceneNode::NodePair> collisions;
  scene_graph_.checkSceneCollision(scene_graph_, collisions);
  for (auto pair : collisions) {
    if (matchesCategories(pair, NodeCategory::kUnit, NodeCategory::kBullet)) {
      ASSERT(dynamic_cast<Unit*>(pair.first));
      ASSERT(dynamic_cast<combat::Projectile*>(pair.second));
      pair.first->handleCollisionWith(NodeCategory::kBullet, pair.second);
      pair.second->handleCollisionWith(NodeCategory::kUnit, pair.first);
    } else if (matchesCategories(pair, NodeCategory::kUnit,
                                 NodeCategory::kMelee)) {
      ASSERT(dynamic_cast<Unit*>(pair.first));
      ASSERT(dynamic_cast<combat::Melee*>(pair.second));
      // Attention: strict order
      pair.first->handleCollisionWith(NodeCategory::kMelee, pair.second);
      pair.second->handleCollisionWith(NodeCategory::kUnit, pair.first);
    } else if (matchesCategories(pair, NodeCategory::kBullet,
                                 NodeCategory::kWall)) {
      ASSERT(dynamic_cast<combat::Projectile*>(pair.first));
      ASSERT(dynamic_cast<GameObject*>(pair.second));
      pair.first->handleCollisionWith(NodeCategory::kWall, pair.second);
    } else if (matchesCategories(pair, NodeCategory::kUnit,
                                 NodeCategory::kWall)) {
      ASSERT(dynamic_cast<Unit*>(pair.first));
      ASSERT(dynamic_cast<GameObject*>(pair.second));
      pair.first->handleCollisionWith(NodeCategory::kWall, pair.second);
    } else if (matchesCategories(pair, NodeCategory::kUnit,
                                 NodeCategory::kDoor)) {
      ASSERT(dynamic_cast<Unit*>(pair.first));
      ASSERT(dynamic_cast<GameObject*>(pair.second));
      pair.first->handleCollisionWith(NodeCategory::kDoor, pair.second);
    }
    if (matchesCategories(pair, NodeCategory::kWall, NodeCategory::kVision)) {
      ASSERT(dynamic_cast<GameObject*>(pair.first));
      ASSERT(dynamic_cast<PlayerVision*>(pair.second));
      pair.second->handleCollisionWith(NodeCategory::kWall, pair.first);
    }
  }
}

void World::buildScene() {
  // create and connect the rooms
  room_manager_->createInitialRoom();

  using Weapon = component::UnitCombat::Weapon;
  const std::size_t health = 20;
  const auto attack_speed = 1.0f;
  const bool centred = true;

  // add an enemy
  auto enemy = std::make_unique<Unit>(
      ComponentManager{
          std::make_unique<component::SimplePhysics>(),
          std::make_unique<component::TwoSpriteGraphics>(
              textures_.get(Textures::kPeepoLeft),
              textures_.get(Textures::kPeepoRight), centred),
          std::make_unique<component::AIKeyboardInput>(),
          std::make_unique<component::UnitCombat>(
              textures_, Owner::kEnemy, health, attack_speed, Weapon::kGun),
          std::make_unique<component::UnitCollision>()},
      fonts_, NodeCategory::kUnit, Owner::kEnemy);
  enemy->setPosition(spawn_position_ * 0.5f);
  room_manager_->attachUnit(std::move(enemy));

  const auto asset_size = sf::Vector2u{96, 96};
  // add a character
  auto character = std::make_unique<Unit>(
      ComponentManager{
          std::make_unique<component::SimplePhysics>(),
          std::make_unique<component::AssetGraphics>(textures_, asset_size,
                                                     centred),
          std::make_unique<component::EmptyInput>(),
          std::make_unique<component::UnitCombat>(
              textures_, Owner::kEnemy, health, attack_speed, Weapon::kSword),
          std::make_unique<component::UnitCollision>()},
      fonts_, NodeCategory::kUnit, Owner::kEnemy);
  character->setPosition(spawn_position_ * 0.7f);
  room_manager_->attachUnit(std::move(character));

  // add a player
  auto player = std::make_unique<Unit>(
      ComponentManager{std::make_unique<component::SimplePhysics>(),
                       std::make_unique<component::AssetGraphics>(
                           textures_, asset_size, centred),
                       std::make_unique<component::KeyboardInput>(),
                       std::make_unique<component::UnitCombat>(
                           textures_, Owner::kPlayer, health,
                           attack_speed - 0.2f, Weapon::kSword),
                       std::make_unique<component::UnitCollision>()},
      fonts_, NodeCategory::kUnit, Owner::kPlayer);
  player_ = player.get();
  player_->setPosition(spawn_position_);
  room_manager_->attachUnit(std::move(player));

  ASSERT(player_);
  const auto traces_len =
      2 * std::max(world_bounds_.height, world_bounds_.width);
  auto player_vision = std::make_unique<PlayerVision>(
      traces_len, world_bounds_, player_->getPosition(),
      room_manager_->getCurrentRoomWalls());
  player_vision_ = player_vision.get();
  player_->attachChild(std::move(player_vision));
}

}  // namespace ink
