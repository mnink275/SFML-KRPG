#include <Components/PlayerPhysics.hpp>

#include <cmath>
#include "SFML/System/Vector2.hpp"

namespace ink::component {

sf::Vector2f PlayerPhysics::getTransform(sf::Time dt,
                                         VelocityModule& velocity) {
  return fixDiagonalVelocity(velocity.toVector()) * dt.asSeconds();
}

sf::Vector2f PlayerPhysics::fixDiagonalVelocity(sf::Vector2f velocity) const {
  if (velocity.x != 0.f && velocity.y != 0.f) {
    return velocity / std::sqrt(2.f);
  }
  return velocity;
}

}  // namespace ink::component
