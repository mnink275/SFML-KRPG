#include <Entities/Player.hpp>

#include <cassert>
#include <iostream>
#include <memory>

#include <Combat/Projectile.hpp>

namespace ink {

void Player::handlePlayerInput(const sf::Keyboard::Key key,
                               const bool is_pressed) {
  inputs_impl_->handlePlayerInput(key, is_pressed, velocity_);
}

void Player::setParentRoom(room::RoomNode* parent) noexcept {
  parent_ = parent;
}

void Player::OnAttack() {
  parent_->attachChild(std::make_unique<combat::Projectile>(
      texture_holder_.get(Textures::Peepo)));
}

}  // namespace ink
