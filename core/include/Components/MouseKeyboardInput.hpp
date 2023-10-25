#pragma once

#include <Components/InputComponent.hpp>

namespace ink::component {

class MouseKeyboardInput final : public InputComponent {
 public:
  // TODO: delete and make commands system
  MouseKeyboardInput(PhysicsComponent* physics) : physics_(physics) {}

  ~MouseKeyboardInput() override = default;

  void handlePlayerInput(const sf::Keyboard::Key key, const bool is_pressed,
                         VelocityModule& velocity) override;

 private:
  PhysicsComponent* physics_;
};

}  // namespace ink::component
