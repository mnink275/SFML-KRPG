#include <Components/Graphics/GraphicsComponent.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace ink::component {

GraphicsComponent::GraphicsComponent()
    : Component(kCategory),
      object_state(ObjectState::kIdle),
      eyes_direction(EyesDirection::kRight) {}

GraphicsComponent::GraphicsComponent(ObjectState object_state,
                                     EyesDirection eyes_direction)
    : Component(kCategory),
      object_state(object_state),
      eyes_direction(eyes_direction) {}

void GraphicsComponent::update(sf::Time /*dt*/) {}

}  // namespace ink::component
