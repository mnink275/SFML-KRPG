#pragma once

#include <unordered_map>

#include <SFML/System/Time.hpp>

#include <Commands/Command.hpp>
#include <Components/Input/InputComponent.hpp>

namespace ink::component {

class AIKeyboardInput final : public InputComponent {
 public:
  AIKeyboardInput();
  ~AIKeyboardInput() override = default;

  void handleInput(CommandQueue<NodeCommand>& command_queue,
                   const sf::Keyboard::Key key, const bool is_pressed) override;

  void handleRealtimeInput(sf::Time dt,
                           CommandQueue<NodeCommand>& commands) override;

 private:
  enum class State {
    kIdle,
    kMoveDown,
    kMoveLeft,
    kMoveUp,
    kMoveRight,
  };

 private:
  std::unordered_map<sf::Keyboard::Key, bool> is_pressed_map_;
  State state{State::kIdle};
};

}  // namespace ink::component
