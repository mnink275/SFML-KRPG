#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/PhysicsComponent.hpp>

namespace ink::component {

class BulletPhysics : public PhysicsComponent {
 public:
  virtual ~BulletPhysics() = default;

  sf::Vector2f getTransform(GameObject* object, sf::Time dt) override;
};

}  // namespace ink::component
