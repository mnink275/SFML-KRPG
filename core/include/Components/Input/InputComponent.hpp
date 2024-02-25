#pragma once

#include <unordered_map>
#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>
#include <Components/Component.hpp>

namespace ink::component {

class InputComponent : public Component {
 public:
  static constexpr auto kCategory = ComponentCategory::kInput;
  static constexpr auto kName = "Input";

 public:
  InputComponent();

  virtual void handleInput(CommandQueue<NodeCommand>& command_queue,
                           const sf::Keyboard::Key key,
                           const bool is_pressed) = 0;
  virtual void handleRealtimeInput(sf::Time dt,
                                   CommandQueue<NodeCommand>& commands) = 0;

 private:
  using KeyToCommandsMap = std::unordered_map<sf::Keyboard::Key, std::vector<ComponentCommand>>;
  class MonadicHelper final {
   public:
    MonadicHelper(sf::Keyboard::Key key, KeyToCommandsMap& key_commands) noexcept
        : key_(key), key_commands_(key_commands) {}

    template <CoreComponent TComponent, class Command>
    MonadicHelper BindCommandTo(Command&& command) const && {
      key_commands_[key_].emplace_back(
        TComponent::kCategory,
        SendTo<TComponent>(std::forward<Command>(command)));
      return *this;
    }

   private:
    sf::Keyboard::Key key_;
    KeyToCommandsMap& key_commands_;
  };

 protected:
  MonadicHelper ForKey(sf::Keyboard::Key key) noexcept {
    return MonadicHelper{key, commands_};
  }

  KeyToCommandsMap commands_;
};

}  // namespace ink::component
