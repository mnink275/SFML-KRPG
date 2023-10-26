#pragma once

#include <Components/InputComponent.hpp>

namespace ink::component {

class MouseKeyboardInput final : public InputComponent {
 public:
  ~MouseKeyboardInput() override = default;

  void handlePlayerInput(GameObject* object, const sf::Keyboard::Key key,
                         const bool is_pressed) override;
};

}  // namespace ink::component
