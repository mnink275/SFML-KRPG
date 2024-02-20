#include <Components/Input/InputComponent.hpp>

namespace ink::component {

InputComponent::InputComponent() : Component(kCategory) {}

void InputComponent::createCommand(sf::Keyboard::Key key,
                                   ComponentCommand::Receiver receiver_category,
                                   const ComponentCommand::Action& action) {
  commands_[key].emplace_back(receiver_category, action);
}

}  // namespace ink::component
