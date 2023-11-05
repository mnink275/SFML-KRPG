#include <Components/BulletPhysics.hpp>

#include <iostream>

namespace ink::component {

BulletPhysics::BulletPhysics(EyesDirection eyes_direction)
    : eyes_direction(eyes_direction) {}

sf::Vector2f BulletPhysics::getTransform(sf::Time dt) {
  const static auto bullet_speed = 1000;
  switch (eyes_direction) {
    case EyesDirection::kLeft:
      velocity = {-bullet_speed, 0.f};
      break;
    case EyesDirection::kRight:
      velocity = {bullet_speed, 0.f};
      break;
    default:
      std::cout << "Error in BulletPhysics: bullet must have a direction\n";
      assert(false);
  }

  return velocity * dt.asSeconds();
}

}  // namespace ink::component
