#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/Physics/PhysicsComponent.hpp>

namespace ink::component {

class SimplePhysics : public PhysicsComponent {
 public:
  using PhysicsComponent::PhysicsComponent;

  virtual ~SimplePhysics() = default;

  sf::Vector2f getTransform(sf::Time dt) override;

 private:
  sf::Vector2f fixDiagonalVelocity(sf::Vector2f velocity) const;
};

}  // namespace ink::component
