#include <Resource/SpriteNode.hpp>

namespace ink {

SpriteNode::SpriteNode(const sf::Texture& texture, bool is_centered)
    : sprite_(texture) {
  if (is_centered) {
    const sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin({bounds.width / 2.f, bounds.height / 2.f});
  }
}

SpriteNode::SpriteNode(const sf::Texture& texture,
                       const sf::IntRect& texture_rect, bool is_centered)
    : sprite_(texture, texture_rect) {
  if (is_centered) {
    const sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin({bounds.width / 2.f, bounds.height / 2.f});
  }
}

sf::FloatRect SpriteNode::getSpriteGlobalBounds() const noexcept {
  return sprite_.getGlobalBounds();
}

void SpriteNode::drawCurrent(sf::RenderTarget& target,
                             const sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace ink
