#include <Entities/Player.hpp>

#include <cassert>
#include <iostream>
#include <memory>

#include <Combat/Projectile.hpp>

namespace ink {

void Player::setPlayerVelocity(float velocity, Direction direction) noexcept {
  switch (direction) {
    case Direction::kToLeft:
      velocity_.to_left_ = velocity;
      break;
    case Direction::kToRight:
      velocity_.to_right_ = velocity;
      break;
    case Direction::kToUp:
      velocity_.to_up_ = velocity;
      break;
    case Direction::kToDown:
      velocity_.to_down_ = velocity;
      break;
    default:
      std::cout << "Error: Wrong direction in Direction enum\n";
      assert(false);
  }
}

void Player::setParentRoom(room::RoomNode* parent) noexcept {
  parent_ = parent;
}

void Player::OnAttack() {
  parent_->attachChild(std::make_unique<combat::Projectile>(
      texture_holder_.get(Textures::Peepo)));
}

}  // namespace ink
