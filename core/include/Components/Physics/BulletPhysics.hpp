#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/Physics/PhysicsComponent.hpp>
#include <Entities/EyesDirection.hpp>

namespace ink::component {

class BulletPhysics final : public PhysicsComponent {
 public:
  BulletPhysics(EyesDirection eyes_direction);

  sf::Vector2f getTransform(sf::Time dt) override;

  EyesDirection eyes_direction;
};

}  // namespace ink::component
