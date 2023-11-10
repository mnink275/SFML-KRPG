#include <Components/Physics/SimplePhysics.hpp>

#include <cmath>

namespace ink::component {

sf::Vector2f SimplePhysics::getTransform(sf::Time dt) {
  auto transform = fixDiagonalVelocity(velocity) * dt.asSeconds();
  velocity = {0.f, 0.f};  // assign to Zero for next frame
  return transform;
}

sf::Vector2f SimplePhysics::fixDiagonalVelocity(sf::Vector2f velo) const {
  if (velo.x != 0.f && velo.y != 0.f) {
    return velo / std::sqrt(2.f);
  }
  return velo;
}

}  // namespace ink::component
