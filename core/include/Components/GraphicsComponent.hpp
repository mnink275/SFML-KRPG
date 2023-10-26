#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace ink::component {

class GraphicsComponent {
 public:
  virtual ~GraphicsComponent() = default;

  virtual void draw(sf::RenderTarget& target,
                    const sf::RenderStates states) const = 0;

 protected:
  void doSpriteCentering(sf::Sprite& sprite);
};

}  // namespace ink::component
