#pragma once

#include <SFML/Window/Keyboard.hpp>

namespace ink {
class GameObject;
}

namespace ink::component {

class InputComponent {
 public:
  virtual ~InputComponent() = default;

  virtual void handlePlayerInput(GameObject* object,
                                 const sf::Keyboard::Key key,
                                 const bool is_pressed) = 0;
};

}  // namespace ink::component
