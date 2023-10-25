#include <Components/SimpleGraphics.hpp>

namespace ink::component {

SimpleGraphics::SimpleGraphics(const sf::Texture& texture, bool is_centered)
    : sprite_(texture) {
  if (is_centered) {
    const sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin({bounds.width / 2.f, bounds.height / 2.f});
  }
}

SimpleGraphics::SimpleGraphics(const sf::Texture& texture,
                               const sf::IntRect& rect, bool is_centered)
    : sprite_(texture, rect) {
  if (is_centered) {
    const sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin({bounds.width / 2.f, bounds.height / 2.f});
  }
}

void SimpleGraphics::draw(sf::RenderTarget& target,
                          const sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace ink::component
