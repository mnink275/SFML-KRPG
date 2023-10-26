#pragma once

#include <cassert>

#include <SFML/Window/Event.hpp>

#include <Components/PlayerPhysics.hpp>
#include <Commands/PhysicsCommand.hpp>

namespace ink {

class VelocityDiffCommand final : public PhysicsCommand {
 public:
  VelocityDiffCommand(float velocity_diff, sf::Keyboard::Key key)
      : velocity_diff(velocity_diff), key(key) {}

  void execute(component::PhysicsComponent* physics_base) override {
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

 public:
  float velocity_diff;
  sf::Keyboard::Key key;
};

}  // namespace ink
