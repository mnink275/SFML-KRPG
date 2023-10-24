#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace ink::component {

class PhysicsComponent {
 public:
  virtual ~PhysicsComponent() = default;

  virtual void update(sf::Time dt, sf::Vector2f& transform) = 0;
  virtual sf::Vector2f getVelocity() const noexcept = 0;
  virtual void setVelocity(sf::Vector2f velocity) noexcept = 0;
};

}  // namespace ink::component
