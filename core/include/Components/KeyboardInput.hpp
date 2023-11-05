#pragma once

#include <Commands/Command.hpp>
#include <Components/InputComponent.hpp>

namespace ink::component {

class KeyboardInput final : public InputComponent {
 public:
  KeyboardInput();
  ~KeyboardInput() override = default;

  void handleInput(CommandQueue<NodeCommand>& command_queue,
                   const sf::Keyboard::Key key, const bool is_pressed) override;

  void handleRealtimeInput(sf::Time dt,
                           CommandQueue<NodeCommand>& commands) override;

 private:
  bool isRealtimeAction(sf::Keyboard::Key key) const noexcept;
};

}  // namespace ink::component
