#include <Entities/Player.hpp>

namespace ink {

Player::Player(std::unique_ptr<component::PhysicsComponent> physics,
               std::unique_ptr<component::GraphicsComponent> graphics,
               std::unique_ptr<component::InputComponent> inputs,
               std::unique_ptr<component::CombatComponent> combat,
               const TextureHolder& texture_holder, NodeCategory category)
    : GameObject(std::move(physics), std::move(graphics), std::move(inputs),
                 std::move(combat), category),
      texture_holder_(texture_holder) {
  physics_impl_->setCommandQueue(&command_queue_);
  graphics_impl_->setCommandQueue(&command_queue_);
  inputs_impl_->setCommandQueue(&command_queue_);
  combat_impl_->setCommandQueue(&command_queue_);

  fire_command_.category = NodeCategory::Room;
  fire_command_.action = [this](SceneNode& node, sf::Time) {
    combat_impl_->onAttack(node, getPosition(), graphics_impl_->eyes_direction);
  };
}

void Player::handlePlayerInput(CommandQueue<NodeCommand>& commands,
                               const sf::Keyboard::Key key,
                               const bool is_pressed) {
  inputs_impl_->handlePlayerInput(commands, key, is_pressed);
}

void Player::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) {
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

}  // namespace ink
