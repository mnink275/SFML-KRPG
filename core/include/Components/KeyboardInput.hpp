#pragma once

#include <Commands/Command.hpp>
#include <Components/InputComponent.hpp>

namespace ink::component {

class KeyboardInput final : public InputComponent {
 public:
  KeyboardInput();
  ~KeyboardInput() override = default;

  void handlePlayerInput(CommandQueue<NodeCommand>& command_queue,
                         const sf::Keyboard::Key key,
                         const bool is_pressed) override;

 private:
  ComponentCommand player_move_;
  ComponentCommand player_fire_;
  ComponentCommand player_body_rotation_;
};

}  // namespace ink::component
