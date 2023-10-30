#include <Components/BulletPhysics.hpp>

namespace ink::component {

BulletPhysics::BulletPhysics(bool is_turned_right)
    : is_turned_right(is_turned_right) {}

sf::Vector2f BulletPhysics::getTransform(sf::Time dt) {
  const static auto bullet_speed = 1000;
  if (is_turned_right) {
    velocity.to_left_ = 0;
    velocity.to_right_ = bullet_speed;
  } else {
    velocity.to_left_ = bullet_speed;
    velocity.to_right_ = 0;
  }
  velocity.to_down_ = 0;
  velocity.to_up_ = 0;
  return velocity.toVector() * dt.asSeconds();
}

}  // namespace ink::component
