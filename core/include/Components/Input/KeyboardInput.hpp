#pragma once

#include <Commands/Command.hpp>
#include <Components/Input/InputComponent.hpp>

namespace ink::component {

class KeyboardInput : public InputComponent {
 public:
  KeyboardInput();

  void handleInput(CommandQueue<NodeCommand>& command_queue,
                   const sf::Keyboard::Key key, const bool is_pressed) override;

  void handleRealtimeInput(sf::Time dt,
                           CommandQueue<NodeCommand>& commands) override;

 private:
  static bool isRealtimeAction(sf::Keyboard::Key key) noexcept;

 private:
  ComponentCommand do_idle_;
};

}  // namespace ink::component
