#pragma once

#include "SFML/Graphics/Rect.hpp"

#include <SceneNode.hpp>

namespace ink {

class SpriteNode : public SceneNode {
 public:
  explicit SpriteNode(const sf::Texture& texture, bool is_centered);
  SpriteNode(const sf::Texture& texture, const sf::IntRect& rect,
             bool is_centered);

  SpriteNode(const SpriteNode&) = delete;
  SpriteNode& operator=(const SpriteNode&) = delete;

  SpriteNode(SpriteNode&&) noexcept = default;
  SpriteNode& operator=(SpriteNode&&) noexcept = default;

  virtual ~SpriteNode() = default;

  sf::FloatRect getSpriteGlobalBounds() const noexcept;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  sf::Sprite sprite_;
};

}  // namespace ink
