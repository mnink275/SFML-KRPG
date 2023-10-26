#pragma once

#include <SFML/Window/Event.hpp>

#include <Commands/PhysicsCommand.hpp>
#include <Components/PlayerPhysics.hpp>

namespace ink {

class VelocityDiffCommand final : public PhysicsCommand {
 public:
  VelocityDiffCommand(float velocity_diff, sf::Keyboard::Key key);

  void execute(
      component::PhysicsComponent* physics_base) const noexcept override;

 public:
  float velocity_diff;
  sf::Keyboard::Key key;
};

}  // namespace ink
