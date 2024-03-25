#pragma once

#include <Components/Graphics/GraphicsComponent.hpp>

namespace ink::component {

class EmptyGraphics final : public GraphicsComponent {
 public:
  void draw(sf::RenderTarget& /*target*/,
            const sf::RenderStates /*states*/) const override {};

  [[nodiscard]] sf::FloatRect getGlobalBounds() const override { return {}; };
};

}  // namespace ink::component
