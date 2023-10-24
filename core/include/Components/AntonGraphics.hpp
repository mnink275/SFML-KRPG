#pragma once

#include <Components/GraphicsComponent.hpp>
#include "SFML/Graphics/Sprite.hpp"

namespace ink::component {

class AntonGraphics final : public GraphicsComponent {
 public:
  AntonGraphics(const sf::Texture& texture) : sprite_(texture) {}

  ~AntonGraphics() override = default;

  void draw(sf::RenderTarget& target, 
            const sf::RenderStates states) const override {
    target.draw(sprite_, states);
  }

 private:
  sf::Sprite sprite_;
};

}  // namespace ink::component