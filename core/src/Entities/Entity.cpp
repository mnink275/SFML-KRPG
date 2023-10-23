#include <Entities/Entity.hpp>

#include <cmath>

namespace ink {

void Entity::setVelocity(const sf::Vector2f velocity) noexcept {
  velocity_ = velocity;
}

void Entity::setVelocityX(const float vx) noexcept { velocity_.x = vx; }

void Entity::setVelocityY(const float vy) noexcept { velocity_.y = vy; }

sf::Vector2f Entity::getVelocity() const { return velocity_; }

void Entity::updateCurrent(const sf::Time dt) {
  // Transformable::move
  move(updatedVelocity() * dt.asSeconds());
}

sf::Vector2f Entity::updatedVelocity() const {
  if (velocity_.x != 0.f && velocity_.y != 0.f) {
    return velocity_ / std::sqrt(2.f);
  }
  return velocity_;
}

}  // namespace ink
