#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <Entities/VelocityModule.hpp>

namespace ink {
class GameObject;
}

namespace ink::component {

class PhysicsComponent {
 public:
  virtual ~PhysicsComponent() = default;

  virtual sf::Vector2f getTransform(GameObject* object, sf::Time dt) = 0;

  VelocityModule velocity{};
};

}  // namespace ink::component
