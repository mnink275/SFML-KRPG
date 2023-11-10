#include <Components/Graphics/GraphicsComponent.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace ink::component {

GraphicsComponent::GraphicsComponent(EyesDirection eyes_direction)
    : Component(kCategory), eyes_direction(eyes_direction) {}

void GraphicsComponent::doSpriteCentering(sf::Sprite& sprite) {
  const sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin({bounds.width / 2.f, bounds.height / 2.f});
}

}  // namespace ink::component
