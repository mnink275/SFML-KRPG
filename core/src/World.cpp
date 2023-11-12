#include <World.hpp>

#include <memory>
#include <set>

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

namespace ink {

World::World(sf::RenderWindow& window, TextureHolder& textures,
             FontHolder& fonts)
    : window_(window),
      world_view_(window.getDefaultView()),
      textures_(textures),
      fonts_(fonts),
      world_bounds_({0.f, 0.f},
                    {world_view_.getSize().x, world_view_.getSize().y}),
      spawn_position_(world_view_.getSize().x / 2.f,
                      world_bounds_.height - world_view_.getSize().y / 2.f),
      player_(nullptr),
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
  while (!command_queue_.isEmpty()) {
    scene_graph_.onCommand(command_queue_.pop(), dt);
  }

  scene_graph_.update(dt, command_queue_);
  handleCollisions();
  scene_graph_.cleanGarbage();
}

bool World::matchesCategories(SceneNode::NodePair& colliders,
                              NodeCategory requested1,
                              NodeCategory requested2) const noexcept {
  auto requested1_id = static_cast<CategoryUnderlying>(requested1);
  auto requested2_id = static_cast<CategoryUnderlying>(requested2);
  auto collider1_id =
      static_cast<CategoryUnderlying>(colliders.first->getCategory());
  auto collider2_id =
      static_cast<CategoryUnderlying>(colliders.second->getCategory());
  if (requested1_id & collider1_id && requested2_id & collider2_id) {
    return true;
  } else if (requested1_id & collider2_id && requested2_id & collider1_id) {
    std::swap(colliders.first, colliders.second);
    return true;
  } else {
    return false;
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
    case sf::Keyboard::Key::E:
    case sf::Keyboard::Key::Space:
      player_->handleInput(command_queue_, key, is_pressed);
      break;
    default:
      std::cout << "The key isn't implemented!\n";
  }
}

void World::handleCollisions() {
  std::set<SceneNode::NodePair> collisions;
  scene_graph_.checkSceneCollision(scene_graph_, collisions);
  for (auto pair : collisions) {
    if (matchesCategories(pair, NodeCategory::kUnit, NodeCategory::kBullet)) {
      assert(dynamic_cast<Unit*>(pair.first));
      assert(dynamic_cast<combat::Projectile*>(pair.second));
      pair.first->handleCollisionWith(NodeCategory::kBullet, pair.second);
      pair.second->handleCollisionWith(NodeCategory::kUnit, pair.first);
    } else if (matchesCategories(pair, NodeCategory::kUnit,
                                 NodeCategory::kMelee)) {
      assert(dynamic_cast<Unit*>(pair.first));
      assert(dynamic_cast<combat::Melee*>(pair.second));
      // strict order
      pair.first->handleCollisionWith(NodeCategory::kMelee, pair.second);
      pair.second->handleCollisionWith(NodeCategory::kUnit, pair.first);
    } else if (matchesCategories(pair, NodeCategory::kBullet,
                                 NodeCategory::kWall)) {
      assert(dynamic_cast<combat::Projectile*>(pair.first));
      assert(dynamic_cast<GameObject*>(pair.second));
      pair.first->handleCollisionWith(NodeCategory::kWall, pair.second);
    } else if (matchesCategories(pair, NodeCategory::kUnit,
                                 NodeCategory::kWall)) {
      assert(dynamic_cast<Unit*>(pair.first));
      assert(dynamic_cast<GameObject*>(pair.second));
      pair.first->handleCollisionWith(NodeCategory::kWall, pair.second);
    } else if (matchesCategories(pair, NodeCategory::kUnit,
                                 NodeCategory::kDoor)) {
      assert(dynamic_cast<Unit*>(pair.first));
      assert(dynamic_cast<GameObject*>(pair.second));
      pair.first->handleCollisionWith(NodeCategory::kDoor, pair.second);
    }
  }
}

void World::buildScene() {
  // create and connect the rooms
  room_manager_->createInitialRoom();

  // add a player
  auto player = std::make_unique<Unit>(
      ComponentManager{std::make_unique<component::SimplePhysics>(),
                       std::make_unique<component::AssetGraphics>(
                           textures_, sf::Vector2u{96, 96}, true),
                       std::make_unique<component::KeyboardInput>(),
                       std::make_unique<component::UnitCombat>(
                           textures_, OwnerType::kPlayer, 20, 1.0f),
                       std::make_unique<component::UnitCollision>()},
      fonts_, NodeCategory::kUnit, OwnerType::kPlayer);
  player_ = player.get();
  player_->setPosition(spawn_position_);
  room_manager_->attachUnit(std::move(player));

  // add an enemy
  auto enemy = std::make_unique<Unit>(
      ComponentManager{std::make_unique<component::SimplePhysics>(),
                       std::make_unique<component::TwoSpriteGraphics>(
                           textures_.get(Textures::kPeepoLeft),
                           textures_.get(Textures::kPeepoRight), true),
                       std::make_unique<component::AIKeyboardInput>(),
                       std::make_unique<component::UnitCombat>(
                           textures_, OwnerType::kEnemy, 20, 1.0f),
                       std::make_unique<component::UnitCollision>()},
      fonts_, NodeCategory::kUnit, OwnerType::kEnemy);
  enemy->setPosition(spawn_position_ * 0.5f);
  room_manager_->attachUnit(std::move(enemy));

  // add a character
  auto character = std::make_unique<Unit>(
      ComponentManager{std::make_unique<component::SimplePhysics>(),
                       std::make_unique<component::AssetGraphics>(
                           textures_, sf::Vector2u{96, 96}, true),
                       std::make_unique<component::EmptyInput>(),
                       std::make_unique<component::UnitCombat>(
                           textures_, OwnerType::kEnemy, 20, 1.0f),
                       std::make_unique<component::UnitCollision>()},
      fonts_, NodeCategory::kUnit, OwnerType::kEnemy);
  character->setPosition(spawn_position_ * 0.7f);
  room_manager_->attachUnit(std::move(character));
}

}  // namespace ink
