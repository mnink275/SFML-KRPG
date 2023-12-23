#pragma once

#include <SFML/Graphics/Sprite.hpp>

namespace ink::utils {

inline static void doSpriteCentering(sf::Sprite& sprite) {
  const sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin({bounds.width / 2, bounds.height / 2});
}

}  // namespace ink::utils
