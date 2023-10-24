#include <Entities/Player.hpp>

#include <cassert>
#include <iostream>
#include <memory>

#include <Combat/Projectile.hpp>

namespace ink {

Textures::ID Player::toTextureID(const Player::Type type) const {
  switch (type) {
    case Player::Peepo:
      return Textures::Peepo;
  }
  return Textures::Peepo;
}

Player::Player(const Type type, const TextureHolder& textures)
    : Entity(textures.get(toTextureID(type)), true),
      Killable(20, getSpriteGlobalBounds()),
      type_(type), texture_holder_(textures) {}

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

void Player::setParentRoom(room::RoomNode* parent) noexcept {
  parent_ = parent;
}

void Player::OnAttack() {
  parent_->attachChild(std::make_unique<combat::Projectile>(texture_holder_.get(toTextureID(type_))));
}

void Player::updatePlayerVelocity() noexcept {
  setVelocityX(to_left_vel_ + to_right_vel_);
  setVelocityY(to_down_vel_ + to_up_vel_);
}

}  // namespace ink
