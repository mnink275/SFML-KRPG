#include <Components/BulletPhysics.hpp>

namespace ink::component {

sf::Vector2f BulletPhysics::getTransform(sf::Time dt,
                                         VelocityModule& velocity) {
  velocity.to_left_ = 0;
  velocity.to_right_ = 50;
  velocity.to_down_ = 50;
  velocity.to_up_ = 0;
  return velocity.toVector() * dt.asSeconds();
}

}  // namespace ink::component
