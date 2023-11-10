#include <Entities/Unit.hpp>

#include <Combat/Projectile.hpp>
#include <Entities/GameStaticObject.hpp>

namespace ink {

Unit::Unit(std::unique_ptr<component::PhysicsComponent> physics,
           std::unique_ptr<component::GraphicsComponent> graphics,
           std::unique_ptr<component::InputComponent> inputs,
           std::unique_ptr<component::CombatComponent> combat,
           const TextureHolder& texture_holder, NodeCategory category,
           OwnerType owner)
    : GameObject(std::move(physics), std::move(graphics), std::move(inputs),
                 std::move(combat), category),
      texture_holder_(texture_holder),
      owner_(owner) {
  // TODO: move components logic to GameObject class
  physics_impl_->setCommandQueue(&command_queue_);
  graphics_impl_->setCommandQueue(&command_queue_);
  inputs_impl_->setCommandQueue(&command_queue_);
  combat_impl_->setCommandQueue(&command_queue_);

  fire_command_.category = NodeCategory::kRoom;
  fire_command_.action = [this](SceneNode& node, sf::Time) {
    combat_impl_->onAttack(node, getPosition(), graphics_impl_->eyes_direction);
  };
}

void Unit::handleInput(CommandQueue<NodeCommand>& commands,
                       const sf::Keyboard::Key key, const bool is_pressed) {
  inputs_impl_->handleInput(commands, key, is_pressed);
}

void Unit::handleCollisionWith(NodeCategory category, const SceneNode* node) {
  switch (category) {
    case NodeCategory::kBullet: {
      const auto* bullet = static_cast<const combat::Projectile*>(node);
      if (GetOwnerType() != bullet->owner) destroy();
      break;
    }
    case NodeCategory::kWall: {
      const auto* wall = static_cast<const GameStaticObject*>(node);
      auto intersection_opt =
          getBoundingRect().findIntersection(wall->getBoundingRect());
      assert(intersection_opt.has_value());
      auto intersection = intersection_opt.value();

      auto is_vertical_collision = intersection.width < intersection.height;
      auto shift = std::min(intersection.width, intersection.height);
      auto player_pos = getPosition();
      auto obstacle_pos = wall->getPosition();
      if (is_vertical_collision) {
        auto sign = (player_pos.x < obstacle_pos.x) ? -1 : +1;
        player_pos.x += shift * sign;
      } else {
        auto sign = (player_pos.y < obstacle_pos.y) ? -1 : +1;
        player_pos.y += shift * sign;
      }
      setPosition(player_pos);
      break;
    }
    default:
      break;
  }
}

void Unit::handleRealtimeInput(sf::Time dt,
                               CommandQueue<NodeCommand>& commands) {
  inputs_impl_->handleRealtimeInput(dt, commands);
}

void Unit::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) {
  handleRealtimeInput(dt, commands);

  while (!command_queue_.isEmpty()) {
    auto command = command_queue_.pop();
    physics_impl_->onCommand(command, dt);
    graphics_impl_->onCommand(command, dt);
    inputs_impl_->onCommand(command, dt);
    combat_impl_->onCommand(command, dt);
  }

  auto transforms = physics_impl_->getTransform(dt);
  Transformable::move(transforms);

  if (combat_impl_->is_attacking) {
    combat_impl_->is_attacking = false;
    commands.push(fire_command_);
  }
};

OwnerType Unit::GetOwnerType() const noexcept { return owner_; }

}  // namespace ink
