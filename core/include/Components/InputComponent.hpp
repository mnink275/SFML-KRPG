#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>
#include <Components/Component.hpp>

namespace ink::component {

class InputComponent : public Component {
 public:
  InputComponent();
  virtual ~InputComponent() = default;

  virtual void handlePlayerInput(CommandQueue<NodeCommand>& command_queue,
                                 const sf::Keyboard::Key key,
                                 const bool is_pressed) = 0;
};

}  // namespace ink::component
