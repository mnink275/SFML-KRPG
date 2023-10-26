#include <Components/PlayerGraphics.hpp>

namespace ink::component {

PlayerGraphics::PlayerGraphics(const sf::Texture& left_movement,
                               const sf::Texture& right_movement,
                               bool is_centered)
    : PlayerGraphics(left_movement, right_movement,
                     sf::IntRect{{0, 0}, sf::Vector2i{left_movement.getSize()}},
                     is_centered) {}

PlayerGraphics::PlayerGraphics(const sf::Texture& left_movement,
                               const sf::Texture& right_movement,
                               const sf::IntRect& rect, bool is_centered)
    : left_movement_sprite_(left_movement, rect),
      right_movement_sprite_(right_movement, rect) {
  if (is_centered) {
    doSpriteCentering(left_movement_sprite_);
    doSpriteCentering(right_movement_sprite_);
  }
  assert(left_movement.getSize() == right_movement.getSize());
}

void PlayerGraphics::draw(sf::RenderTarget& target,
                          const sf::RenderStates states) const {
  if (is_turned_right) {
    target.draw(right_movement_sprite_, states);
  } else {
    target.draw(left_movement_sprite_, states);
  }
}

}  // namespace ink::component
