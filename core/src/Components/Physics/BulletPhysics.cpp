#include <Components/Physics/BulletPhysics.hpp>

#include <fmt/format.h>

#include <Utils/Assert.hpp>

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
      ASSERT_MSG(false, "Bullet must have a direction");
  }

  return velocity * dt.asSeconds();
}

}  // namespace ink::component
