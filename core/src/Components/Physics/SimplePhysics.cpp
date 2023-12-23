#include <Components/Physics/SimplePhysics.hpp>

#include <cmath>

namespace ink::component {

namespace {

const auto fixDiagonalVelocity = [](sf::Vector2f velocity) {
  if (velocity.x != 0.f && velocity.y != 0.f) {
    return velocity / std::sqrt(2.f);
  }
  return velocity;
};

}  // namespace

sf::Vector2f SimplePhysics::getTransform(sf::Time dt) {
  auto transform = fixDiagonalVelocity(velocity) * dt.asSeconds();
  velocity = {0.f, 0.f};  // assign to zero for next frame
  return transform;
}

}  // namespace ink::component
