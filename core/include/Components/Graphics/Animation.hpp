#pragma once

#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

#include <Entities/Types/EyesDirection.hpp>

namespace ink {

class Animation final {
 public:
  // TODO: change `scale` with something more meaningful for understanding
  Animation(const sf::Texture& texture, const sf::Vector2u sizes,
            bool is_centered, const sf::Time sprite_change_interval);
  Animation(const sf::Texture& texture, const sf::Vector2u sizes,
            bool is_centered, const sf::Time sprite_change_interval,
            const sf::Vector2f scale);

  const sf::Sprite& getCurrentSprite() const;
  sf::Time getAnimationDuration() const noexcept;
  std::size_t getCurrentSpriteIndex() const noexcept;

  void update(sf::Time dt);
  void start(sf::Time duration) noexcept;
  void flitTo(EyesDirection direction);

 private:
  void flipVertically();

 private:
  sf::Time timer_;
  sf::Time sprite_change_interval;
  std::vector<sf::Sprite> animation_;
  std::size_t curr_sprite_;
  sf::Vector2f scale_;
  EyesDirection eyes_direction_;
};

}  // namespace ink
