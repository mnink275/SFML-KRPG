#include <Components/BulletPhysics.hpp>

#include <iostream>

namespace ink::component {

BulletPhysics::BulletPhysics(EyesDirection eyes_direction)
    : eyes_direction(eyes_direction) {}

sf::Vector2f BulletPhysics::getTransform(sf::Time dt) {
  const static auto bullet_speed = 1000;
  switch (eyes_direction) {
    case EyesDirection::kLeft:
      velocity.to_left_ = bullet_speed;
      velocity.to_right_ = 0;
      break;
    case EyesDirection::kRight:
      velocity.to_left_ = 0;
      velocity.to_right_ = bullet_speed;
      break;
    default:
      std::cout << "Error in BulletPhysics: bullet must have a direction\n";
      assert(false);
  }

  return velocity.toVector() * dt.asSeconds();
}

}  // namespace ink::component
