#include <Components/Graphics/AssetGraphics.hpp>

namespace ink::component {

AssetGraphics::AssetGraphics(const sf::Texture& texture,
                             const sf::Vector2u& sizes, bool is_centered)
    : GraphicsComponent(EyesDirection::kLeft),
      is_idle(true),
      idle_animation_(texture, sizes, is_centered, sf::seconds(0.1f)) {}

void AssetGraphics::draw(sf::RenderTarget& target,
                         const sf::RenderStates states) const {
  if (is_idle) {
    target.draw(idle_animation_.getCurrentSprite(), states);
  }
#if 0
    switch (eyes_direction) {
      case EyesDirection::kLeft:
        target.draw(animation_[curr_sprite_], states);
        break;
      case EyesDirection::kRight:
        target.draw(animation_[curr_sprite_], states);
        break;
      default:
        std::cout << "Warning in PlayerGraphics: eye direction is kNone\n";
        break;
    }
#endif
}

void AssetGraphics::update(sf::Time dt) { idle_animation_.update(dt); }

sf::FloatRect AssetGraphics::getGlobalBounds() const {
  return idle_animation_.getCurrentSprite().getGlobalBounds();
}

}  // namespace ink::component
