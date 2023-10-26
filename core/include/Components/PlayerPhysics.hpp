#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/PhysicsComponent.hpp>
#include <Entities/GameObject.hpp>

namespace ink::component {

class PlayerPhysics : public PhysicsComponent {
 public:
  using PhysicsComponent::PhysicsComponent;

  virtual ~PlayerPhysics() = default;

  sf::Vector2f getTransform(sf::Time dt) override;

 private:
  sf::Vector2f fixDiagonalVelocity(sf::Vector2f velocity) const;
};

}  // namespace ink::component
