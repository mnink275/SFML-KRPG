#pragma once

#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

namespace ink {

class Animation final {
 public:
  Animation(const sf::Texture& texture, const sf::Vector2u& sizes,
            bool is_centered, const sf::Time sprite_change_interval);

  const sf::Sprite& getCurrentSprite() const;
  void update(sf::Time dt);

 private:
  sf::Time timer_;
  const sf::Time kSpriteChangeInterval;
  std::vector<sf::Sprite> animation_;
  std::size_t curr_sprite_;
};

}  // namespace ink
