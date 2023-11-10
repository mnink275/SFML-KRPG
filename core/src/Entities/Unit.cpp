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
  manager_.setCommandQueue(&command_queue_);
  fire_command_.category = NodeCategory::kRoom;
  fire_command_.action = [this](SceneNode& node, sf::Time) {
    auto combat = manager_.findComponent<component::CombatComponent>();
    auto graphics = manager_.findComponent<component::GraphicsComponent>();
    combat->onAttack(node, getPosition(), graphics->eyes_direction);
  };
}

void Unit::handleInput(CommandQueue<NodeCommand>& commands,
                       const sf::Keyboard::Key key, const bool is_pressed) {
  auto input = manager_.findComponent<component::InputComponent>();
  input->handleInput(commands, key, is_pressed);
}

void Unit::handleCollisionWith(NodeCategory category, const SceneNode* node) {
  auto collision = manager_.findComponent<component::CollisionComponent>();
  collision->handleCollisionWith(this, category, node);
}

void Unit::handleRealtimeInput(sf::Time dt,
                               CommandQueue<NodeCommand>& commands) {
  auto input = manager_.findComponent<component::InputComponent>();
  input->handleRealtimeInput(dt, commands);
}

void Unit::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) {
  handleRealtimeInput(dt, commands);

  while (!command_queue_.isEmpty()) {
    auto command = command_queue_.pop();
    manager_.onCommand(command, dt);
  }

  auto physics = manager_.findComponent<component::PhysicsComponent>();
  auto transforms = physics->getTransform(dt);
  Transformable::move(transforms);

  auto combat = manager_.findComponent<component::CombatComponent>();
  if (combat->is_attacking) {
    combat->is_attacking = false;
    commands.push(fire_command_);
  }
};

OwnerType Unit::GetOwnerType() const noexcept { return owner_; }

}  // namespace ink
