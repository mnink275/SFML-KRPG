#include <Components/Graphics/TwoSpriteGraphics.hpp>

#include <fmt/format.h>

#include <Components/Graphics/Utils.hpp>
#include <Utils/Assert.hpp>

namespace ink::component {

TwoSpriteGraphics::TwoSpriteGraphics(const sf::Texture& left_movement,
                                     const sf::Texture& right_movement,
                                     bool is_centered)
    : TwoSpriteGraphics(
          left_movement, right_movement,
          sf::IntRect{{0, 0}, sf::Vector2i{left_movement.getSize()}},
          is_centered) {}

TwoSpriteGraphics::TwoSpriteGraphics(const sf::Texture& left_movement,
                                     const sf::Texture& right_movement,
                                     const sf::IntRect& rect, bool is_centered)
    : GraphicsComponent(),
      left_movement_sprite_(left_movement, rect),
      right_movement_sprite_(right_movement, rect) {
  if (is_centered) {
    utils::doSpriteCentering(left_movement_sprite_);
    utils::doSpriteCentering(right_movement_sprite_);
  }
  ASSERT(left_movement.getSize() == right_movement.getSize());
}

void TwoSpriteGraphics::draw(sf::RenderTarget& target,
                             const sf::RenderStates states) const {
  switch (eyes_direction) {
    case EyesDirection::kLeft:
      target.draw(left_movement_sprite_, states);
      break;
    case EyesDirection::kRight:
      target.draw(right_movement_sprite_, states);
      break;
    default:
      ASSERT_MSG(false, "Unhandled `eyes_direction`");
  }
}

sf::FloatRect TwoSpriteGraphics::getGlobalBounds() const {
  return left_movement_sprite_.getGlobalBounds();
}

}  // namespace ink::component
