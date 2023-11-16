#include <Components/Graphics/GraphicsComponent.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace ink::component {

GraphicsComponent::GraphicsComponent()
    : GraphicsComponent(ObjectState::kIdle, EyesDirection::kRight) {}

GraphicsComponent::GraphicsComponent(ObjectState object_state,
                                     EyesDirection eyes_direction)
    : Component(kCategory),
      eyes_direction(eyes_direction),
      freezing_time_(sf::Time::Zero),
      state_changed_(false),
      object_state_(object_state) {}

void GraphicsComponent::update(sf::Time dt) {
  freezing_time_ -= dt;
  updateCurrent(dt);
}

void GraphicsComponent::updateCurrent(sf::Time /*dt*/) {}

void GraphicsComponent::setObjectState(ObjectState state,
                                       FreezeFor freeze_for) noexcept {
  if (freezing_time_ <= sf::Time::Zero) {
    state_changed_ = true;
    object_state_ = state;
    freezing_time_ = freeze_for.freezing_time;
  }
}

ObjectState GraphicsComponent::getObjectState() const noexcept {
  return object_state_;
}

}  // namespace ink::component
