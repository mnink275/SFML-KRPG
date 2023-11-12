#include <Components/Graphics/GraphicsComponent.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace ink::component {

GraphicsComponent::GraphicsComponent(EyesDirection eyes_direction)
    : Component(kCategory), eyes_direction(eyes_direction) {}

void GraphicsComponent::update(sf::Time /*dt*/) {}

}  // namespace ink::component
