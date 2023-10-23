#pragma once

#include <SceneNode.hpp>

namespace ink {

class SpriteNode : public SceneNode {
 public:
  explicit SpriteNode(const sf::Texture& texture);
  SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
  virtual ~SpriteNode() = default;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  sf::Sprite sprite_;
};

}  // namespace ink
