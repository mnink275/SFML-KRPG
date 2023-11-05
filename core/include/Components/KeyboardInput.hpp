#pragma once

#include <unordered_map>
#include <vector>

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

  void handleRealtimeInput(CommandQueue<NodeCommand>& commands) override;

 private:
  bool isRealtimeAction(sf::Keyboard::Key key) const noexcept;

  void createCommand(sf::Keyboard::Key key,
                     ComponentCommand::Receiver receiver_category,
                     ComponentCommand::Action action);

 private:
  std::unordered_map<sf::Keyboard::Key, std::vector<ComponentCommand>>
      commands_;

  ComponentCommand stop_;
};

}  // namespace ink::component
