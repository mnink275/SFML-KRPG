#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

// #include <Components/Component.hpp>

namespace ink::component {

class PhysicsComponent {
 public:
  virtual ~PhysicsComponent() = default;

  virtual void update(sf::Time dt, sf::Vector2f& transform) = 0;
};

}  // namespace ink::component