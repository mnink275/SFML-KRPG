#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Components/GraphicsComponent.hpp>

namespace ink::component {

class SimpleGraphics final : public GraphicsComponent {
 public:
  explicit SimpleGraphics(const sf::Texture& texture, bool is_centered);
  SimpleGraphics(const sf::Texture& texture, const sf::IntRect& rect,
                 bool is_centered);

  ~SimpleGraphics() override = default;

  void draw(sf::RenderTarget& target,
            const sf::RenderStates states) const override;

 private:
  sf::Sprite sprite_;
};

}  // namespace ink::component
