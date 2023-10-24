#pragma once

#include <SFML/Graphics.hpp>

#include <Resource/ResourceIdentifiers.hpp>

namespace ink::component {

class GraphicsComponent {
 public:
  virtual ~GraphicsComponent() = default;

  virtual void draw(sf::RenderTarget& target,
                    const sf::RenderStates states) const = 0;
};

}  // namespace ink::component
