#pragma once

#include "SceneNode.hpp"

class SpriteNode final : public SceneNode {
 public:
  explicit SpriteNode(const sf::Texture& texture);
  SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  sf::Sprite sprite_;
};