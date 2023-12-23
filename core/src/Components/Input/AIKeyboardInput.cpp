#include <Components/Input/AIKeyboardInput.hpp>

#include <Components/Combat/CombatComponent.hpp>
#include <Components/Graphics/GraphicsComponent.hpp>
#include <Components/Physics/PhysicsComponent.hpp>

namespace ink::component {

void AIKeyboardInput::handleInput(CommandQueue<NodeCommand>& /*command_queue*/,
                                  const sf::Keyboard::Key /*key*/,
                                  const bool /*is_pressed*/) {}

void AIKeyboardInput::handleRealtimeInput(
    sf::Time dt, CommandQueue<NodeCommand>& /*commands*/) {
  static constexpr auto kIdleInterval = sf::seconds(2.f);
  static constexpr auto kMoveInterval = sf::seconds(1.f);
  static auto timer = sf::Time::Zero;
  timer += dt;
  bool is_state_changed = false;
  switch (state) {
    case State::kIdle:
      if (timer > kIdleInterval) {
        timer -= kIdleInterval;
        state = State::kMoveDown;
        is_state_changed = true;
      }
      break;
    case State::kMoveDown:
      if (timer > kMoveInterval) {
        timer -= kMoveInterval;
        state = State::kMoveRight;
        is_state_changed = true;
      }
      for (auto&& command : commands_[sf::Keyboard::S]) sendCommand(command);
      break;
    case State::kMoveRight:
      if (timer > kMoveInterval) {
        timer -= kMoveInterval;
        state = State::kMoveUp;
        is_state_changed = true;
      }
      for (auto&& command : commands_[sf::Keyboard::D]) sendCommand(command);
      break;
    case State::kMoveUp:
      if (timer > kMoveInterval) {
        timer -= kMoveInterval;
        state = State::kMoveLeft;
        is_state_changed = true;
      }
      for (auto&& command : commands_[sf::Keyboard::W]) sendCommand(command);
      break;
    case State::kMoveLeft:
      if (timer > kMoveInterval) {
        timer -= kMoveInterval;
        state = State::kIdle;
        is_state_changed = true;
      }
      for (auto&& command : commands_[sf::Keyboard::A]) sendCommand(command);
      break;
  }

  if (is_state_changed)
    for (auto&& command : commands_[sf::Keyboard::Space]) sendCommand(command);
}

}  // namespace ink::component
