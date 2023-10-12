#include "Player.hpp"

#include <iostream>
#include <cassert>

namespace ink {

Textures::ID toTextureID(const Player::Type type) {
  switch (type) {
    case Player::Peepo:
      return Textures::Peepo;
  }
  return Textures::Peepo;
}

Player::Player(const Type type, const TextureHolder& textures)
    : type_(type), sprite_(textures.get(toTextureID(type))) {
  const sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin({bounds.width / 2.f, bounds.height / 2.f});
}

void Player::drawCurrent(sf::RenderTarget& target,
                         const sf::RenderStates states) const {
  target.draw(sprite_, states);
}

void Player::setPlayerVelocity(float velocity, Direction direction) noexcept {
  switch (direction) {
    case Direction::kToLeft:
      to_left_vel_ = velocity;
      break;
    case Direction::kToRight:
      to_right_vel_ = velocity;
      break;
    case Direction::kToUp:
      to_up_vel_ = velocity;
      break;
    case Direction::kToDown:
      to_down_vel_ = velocity;
      break;
    default:
      std::cout << "Error: Wrong direction in Direction enum\n";
      assert(false);
  }
  updatePlayerVelocity();
}

void Player::updatePlayerVelocity() noexcept {
  setVelocityX(to_left_vel_ + to_right_vel_);
  setVelocityY(to_down_vel_ + to_up_vel_);
}

}  // namespace ink
