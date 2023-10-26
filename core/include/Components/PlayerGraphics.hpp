#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Components/GraphicsComponent.hpp>

namespace ink::component {

class PlayerGraphics final : public GraphicsComponent {
 public:
  explicit PlayerGraphics(const sf::Texture& left_movement,
                          const sf::Texture& right_movement, bool is_centered);
  PlayerGraphics(const sf::Texture& left_movement,
                 const sf::Texture& right_movement, const sf::IntRect& rect,
                 bool is_centered);

  ~PlayerGraphics() override = default;

  void draw(sf::RenderTarget& target,
            const sf::RenderStates states) const override;

 public:
  bool is_turned_right{true};

 private:
  sf::Sprite left_movement_sprite_;
  sf::Sprite right_movement_sprite_;
};

}  // namespace ink::component
