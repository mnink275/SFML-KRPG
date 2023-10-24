#pragma once

#include <Components/GraphicsComponent.hpp>

#include "SFML/Graphics/Sprite.hpp"

namespace ink::component {

class PlayerGraphics final : public GraphicsComponent {
 public:
  PlayerGraphics(const sf::Texture& texture);

  ~PlayerGraphics() override = default;

  void draw(sf::RenderTarget& target,
            const sf::RenderStates states) const override;

 private:
  sf::Sprite sprite_;
};

}  // namespace ink::component
