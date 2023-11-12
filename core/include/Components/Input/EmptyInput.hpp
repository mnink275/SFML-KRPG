#pragma once

#include <Components/Input/InputComponent.hpp>

namespace ink::component {

// TODO: do something with "dead" functions like `handleInput`
class EmptyInput : public InputComponent {
 public:
  EmptyInput() = default;

  void handleInput(CommandQueue<NodeCommand>& command_queue,
                   const sf::Keyboard::Key key, const bool is_pressed) override;

  void handleRealtimeInput(sf::Time dt,
                           CommandQueue<NodeCommand>& commands) override;
};

}  // namespace ink::component
