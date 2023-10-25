#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <Entities/VelocityModule.hpp>

namespace ink::component {

class PhysicsComponent {
 public:
  virtual ~PhysicsComponent() = default;

  virtual sf::Vector2f getTransform(sf::Time dt, VelocityModule& velocity) = 0;
};

}  // namespace ink::component
