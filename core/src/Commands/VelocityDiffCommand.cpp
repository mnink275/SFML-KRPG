#include <Commands/VelocityDiffCommand.hpp>

#include <cassert>

namespace ink {

VelocityDiffCommand::VelocityDiffCommand(float velocity_diff,
                                         sf::Keyboard::Key key)
    : velocity_diff(velocity_diff), key(key) {}

void VelocityDiffCommand::execute(
    component::PhysicsComponent* physics_base) const noexcept {
  auto* physics = static_cast<component::PlayerPhysics*>(physics_base);
  switch (key) {
    case sf::Keyboard::Key::A:
      physics->velocity.to_left_ = velocity_diff;
      break;
    case sf::Keyboard::Key::D:
      physics->velocity.to_right_ = velocity_diff;
      break;
    case sf::Keyboard::Key::W:
      physics->velocity.to_up_ = velocity_diff;
      break;
    case sf::Keyboard::Key::S:
      physics->velocity.to_down_ = velocity_diff;
      break;
    default:
      assert(false);
  }
}

}  // namespace ink
