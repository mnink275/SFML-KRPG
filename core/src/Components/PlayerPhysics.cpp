#include <Components/PlayerPhysics.hpp>

#include <cmath>

namespace ink::component {

sf::Vector2f PlayerPhysics::getTransform(sf::Time dt) {
  return fixDiagonalVelocity(velocity) * dt.asSeconds();
}

sf::Vector2f PlayerPhysics::fixDiagonalVelocity(sf::Vector2f velo) const {
  if (velo.x != 0.f && velo.y != 0.f) {
    return velo / std::sqrt(2.f);
  }
  return velo;
}

}  // namespace ink::component
