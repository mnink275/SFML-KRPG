#include <World.hpp>

#include <memory>
#include <set>

#include <SFML/Graphics/Texture.hpp>

#include <Combat/Projectile.hpp>
#include <Commands/Category/Category.hpp>
#include <Components/AIKeyboardInput.hpp>
#include <Components/KeyboardInput.hpp>
#include <Components/SimplePhysics.hpp>
#include <Components/TwoSpriteGraphics.hpp>
#include <Components/UnitCombat.hpp>
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
  // boundChecking();
  checkDoorInteraction();

  while (!command_queue_.isEmpty()) {
    scene_graph_.onCommand(command_queue_.pop(), dt);
  }

  scene_graph_.update(dt, command_queue_);
  handleCollisions();
  scene_graph_.cleanGarbage();
}

void World::checkDoorInteraction() {
  if (interact_with_) {
    interact_with_ = false;
    room_manager_.checkDoorInteraction();
  }
}

bool World::matchesCategories(SceneNode::NodePair& pair, NodeCategory first,
                              NodeCategory second) const noexcept {
  auto first_id = static_cast<CategoryUnderlying>(first);
  auto second_id = static_cast<CategoryUnderlying>(second);
  auto category_id1 =
      static_cast<CategoryUnderlying>(pair.first->getCategory());
  auto category_id2 =
      static_cast<CategoryUnderlying>(pair.second->getCategory());
  if (first_id & category_id1 && second_id & category_id2) {
    return true;
  } else if (first_id & category_id2 && second_id & category_id1) {
    std::swap(pair.first, pair.second);
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
    case sf::Keyboard::Key::Space:
      player_->handleInput(command_queue_, key, is_pressed);
      break;
    case sf::Keyboard::Key::E:
      interact_with_ = is_pressed;
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
      auto* unit = static_cast<Unit*>(pair.first);
      assert(dynamic_cast<combat::Projectile*>(pair.second));
      auto* bullet = static_cast<combat::Projectile*>(pair.second);
      if (unit->GetOwnerType() == Unit::OwnerType::kEnemy) {
        std::cout << "Unit and Bullet collision!\n";
        unit->destroy();
      }
    } else if (matchesCategories(pair, NodeCategory::kBullet,
                                 NodeCategory::kWall)) {
      std::cout << "Bullet and Wall collision!\n";
      assert(dynamic_cast<combat::Projectile*>(pair.first));
      auto* bullet = static_cast<combat::Projectile*>(pair.first);
      assert(dynamic_cast<GameStaticObject*>(pair.second));
      auto* wall = static_cast<GameStaticObject*>(pair.second);
      bullet->destroy();
    } else if (matchesCategories(pair, NodeCategory::kUnit,
                                 NodeCategory::kWall)) {
      std::cout << "Unit and Wall collision!\n";
      assert(dynamic_cast<Unit*>(pair.first));
      auto* unit = static_cast<Unit*>(pair.first);
      assert(dynamic_cast<GameStaticObject*>(pair.second));
      auto* wall = static_cast<GameStaticObject*>(pair.second);

      auto intersection_opt =
          unit->getBoundingRect().findIntersection(wall->getBoundingRect());
      assert(intersection_opt.has_value());
      auto intersection = intersection_opt.value();

      auto is_vertical_collision = intersection.width < intersection.height;
      auto shift = std::min(intersection.width, intersection.height);
      auto player_pos = unit->getPosition();
      auto obstacle_pos = wall->getPosition();
      if (is_vertical_collision) {
        auto sign = (player_pos.x < obstacle_pos.x) ? -1 : +1;
        player_pos.x += shift * sign;
      } else {
        auto sign = (player_pos.y < obstacle_pos.y) ? -1 : +1;
        player_pos.y += shift * sign;
      }
      unit->setPosition(player_pos);
    }
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
  textures_.load(Textures::kWall, kTexturePath + "/texture/Wall64x64.png");
  textures_.load(Textures::kIce, kTexturePath + "/texture/Ice64x64.png");
  textures_.load(Textures::kStoneOnGrass,
                 kTexturePath + "/texture/StoneOnGrass256x256.png");
}

void World::buildScene() {
  // create and connect the rooms
  room_manager_.createInitialRoom();

  // add a player
  auto player = std::make_unique<Unit>(
      std::make_unique<component::SimplePhysics>(),
      std::make_unique<component::TwoSpriteGraphics>(
          textures_.get(Textures::kPeepoLeft),
          textures_.get(Textures::kPeepoRight), true),
      std::make_unique<component::KeyboardInput>(),
      std::make_unique<component::UnitCombat>(textures_), textures_,
      NodeCategory::kUnit, Unit::OwnerType::kPlayer);
  player_ = player.get();
  player_->setPosition(spawn_position_);
  room_manager_.attachUnit(std::move(player));

  // add an enemy
  auto enemy = std::make_unique<Unit>(
      std::make_unique<component::SimplePhysics>(),
      std::make_unique<component::TwoSpriteGraphics>(
          textures_.get(Textures::kPeepoLeft),
          textures_.get(Textures::kPeepoRight), true),
      std::make_unique<component::AIKeyboardInput>(),
      std::make_unique<component::UnitCombat>(textures_), textures_,
      NodeCategory::kUnit, Unit::OwnerType::kEnemy);
  enemy->setPosition(spawn_position_ * 0.5f);
  room_manager_.attachUnit(std::move(enemy));
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
