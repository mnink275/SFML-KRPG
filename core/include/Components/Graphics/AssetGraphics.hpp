#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Components/Graphics/GraphicsComponent.hpp>

namespace ink::component {

class AssetGraphics final : public GraphicsComponent {
 public:
  AssetGraphics(const sf::Texture& texture, const sf::Vector2u& sizes,
                bool is_centered);

  void draw(sf::RenderTarget& target,
            const sf::RenderStates states) const override;
  void update(sf::Time dt) override;

  sf::FloatRect getGlobalBounds() const override;

 public:
  bool is_idle;

 private:
  // TODO: move logic to Animation class
  sf::Time timer_;
  const sf::Time kSpriteChangeInterval;
  std::vector<sf::Sprite> animation_;
  std::size_t curr_sprite_;
};

}  // namespace ink::component
