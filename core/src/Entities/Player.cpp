#include <Entities/Player.hpp>

namespace ink {

void Player::handlePlayerInput(const sf::Keyboard::Key key,
                               const bool is_pressed) {
  inputs_impl_->handlePlayerInput(this, key, is_pressed);
}

}  // namespace ink
