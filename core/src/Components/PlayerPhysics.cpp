#include <Components/PlayerPhysics.hpp>

#include <cmath>

namespace ink::component {

void PlayerPhysics::update(sf::Time dt, sf::Vector2f& transform) {
  transform = velocity_ * dt.asSeconds();
}

sf::Vector2f PlayerPhysics::getVelocity() const noexcept { return velocity_; }

void PlayerPhysics::setVelocity(sf::Vector2f velocity) noexcept {
  velocity_ = velocity;
}

sf::Vector2f PlayerPhysics::updatedVelocity() const {
  if (velocity_.x != 0.f && velocity_.y != 0.f) {
    return velocity_ / std::sqrt(2.f);
  }
  return velocity_;
}

}  // namespace ink::component
