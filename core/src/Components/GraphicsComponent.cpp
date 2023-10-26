#include <Components/GraphicsComponent.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace ink::component {

void GraphicsComponent::doSpriteCentering(sf::Sprite& sprite) {
  const sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin({bounds.width / 2.f, bounds.height / 2.f});
}

}  // namespace ink::component
