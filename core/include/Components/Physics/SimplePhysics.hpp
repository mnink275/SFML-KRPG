#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/Physics/PhysicsComponent.hpp>

namespace ink::component {

class SimplePhysics final : public PhysicsComponent {
 public:
  sf::Vector2f getTransform(sf::Time dt) override;
};

}  // namespace ink::component
