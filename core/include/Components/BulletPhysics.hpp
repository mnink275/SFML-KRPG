#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/PhysicsComponent.hpp>

namespace ink::component {

class BulletPhysics : public PhysicsComponent {
 public:
  BulletPhysics(bool is_turned_right);

  virtual ~BulletPhysics() = default;

  sf::Vector2f getTransform(sf::Time dt) override;

  bool is_turned_right;
};

}  // namespace ink::component
