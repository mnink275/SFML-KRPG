#include <Entities/Unit.hpp>

#include <Combat/Projectile.hpp>
#include <Entities/GameStaticObject.hpp>

namespace ink {

Unit::Unit(std::unique_ptr<component::PhysicsComponent> physics,
           std::unique_ptr<component::GraphicsComponent> graphics,
           std::unique_ptr<component::InputComponent> inputs,
           std::unique_ptr<component::CombatComponent> combat,
           std::unique_ptr<component::CollisionComponent> collision,
           const TextureHolder& texture_holder, NodeCategory category,
           OwnerType owner)
    : GameObject(std::move(physics), std::move(graphics), std::move(inputs),
                 std::move(combat), std::move(collision), category),
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
  assert(collision_impl_);
  collision_impl_->handleCollisionWith(this, category, node);
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
