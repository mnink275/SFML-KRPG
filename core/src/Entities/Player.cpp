#include <Entities/Player.hpp>

#include <cassert>
#include <iostream>
#include <memory>

#include <Combat/Projectile.hpp>
#include <Components/BulletPhysics.hpp>
#include <Components/MouseKeyboardInput.hpp>
#include <Components/SimpleGraphics.hpp>

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
      std::make_unique<component::BulletPhysics>(),
      std::make_unique<component::SimpleGraphics>(
          texture_holder_.get(Textures::Bullet), true),
      nullptr));
}

}  // namespace ink
