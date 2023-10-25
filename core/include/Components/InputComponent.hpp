#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <Components/PhysicsComponent.hpp>
#include <Entities/VelocityModule.hpp>

namespace ink::component {

class InputComponent {
 public:
  virtual ~InputComponent() = default;

  virtual void handlePlayerInput(const sf::Keyboard::Key key,
                                 const bool is_pressed,
                                 VelocityModule& velocity) = 0;
};

}  // namespace ink::component
