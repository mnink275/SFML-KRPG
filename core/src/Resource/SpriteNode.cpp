#include <Resource/SpriteNode.hpp>

namespace ink {

SpriteNode::SpriteNode(const sf::Texture& texture) : sprite_(texture) {}

SpriteNode::SpriteNode(const sf::Texture& texture,
                       const sf::IntRect& texture_rect)
    : sprite_(texture, texture_rect) {}

void SpriteNode::drawCurrent(sf::RenderTarget& target,
                             const sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace ink
