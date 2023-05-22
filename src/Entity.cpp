#include "Entity.hpp"

void Entity::setVelocity(const sf::Vector2f velocity) { velocity_ = velocity; }

void Entity::setVelocity(const float vx, const float vy) {
  velocity_.x = vx;
  velocity_.y = vy;
}

sf::Vector2f Entity::getVelocity() const { return velocity_; }

void Entity::updateCurrent(const sf::Time dt) {
  move(velocity_ * dt.asSeconds());
}