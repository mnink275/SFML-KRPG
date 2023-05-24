#include "Entity.hpp"

#include <cmath>

void Entity::setVelocity(const sf::Vector2f velocity) { velocity_ = velocity; }

void Entity::setVelocityX(const float vx) {
  velocity_.x = vx != 0.f ? vx : 0.f;
}

void Entity::setVelocityY(const float vy) {
  velocity_.y = vy != 0.f ? vy : 0.f;
}

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