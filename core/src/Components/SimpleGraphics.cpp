#include <Components/SimpleGraphics.hpp>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace ink::component {

SimpleGraphics::SimpleGraphics(const sf::Texture& texture, bool is_centered)
    : SimpleGraphics(texture,
                     sf::IntRect{{0, 0}, sf::Vector2i{texture.getSize()}},
                     is_centered) {}

SimpleGraphics::SimpleGraphics(const sf::Texture& texture,
                               const sf::IntRect& rect, bool is_centered)
    : sprite_(texture, rect) {
  if (is_centered) doSpriteCentering(sprite_);
}

void SimpleGraphics::draw(sf::RenderTarget& target,
                          const sf::RenderStates states) const {
  target.draw(sprite_, states);
}

sf::FloatRect SimpleGraphics::getGlobalBounds() const {
  return sprite_.getGlobalBounds();
}

}  // namespace ink::component
