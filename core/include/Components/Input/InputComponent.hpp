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

 protected:
  void createCommand(sf::Keyboard::Key key,
                     ComponentCommand::Receiver receiver_category,
                     const ComponentCommand::Action& action);

  std::unordered_map<sf::Keyboard::Key, std::vector<ComponentCommand>>
      commands_;
};

}  // namespace ink::component
