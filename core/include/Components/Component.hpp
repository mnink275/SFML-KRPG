#pragma once

#include <SFML/System/Time.hpp>

#include <Commands/CommandQueue.hpp>
#include <Commands/ComponentCommand.hpp>
#include <Components/Category.hpp>

namespace ink::component {

class Component {
 public:
  explicit Component(component::Category category);
  virtual ~Component() = default;

  virtual void onCommand(const ComponentCommand& command, sf::Time dt);
  virtual void setCommandQueue(
      CommandQueue<ComponentCommand>* command_queue) noexcept;
  virtual void sendCommand(ComponentCommand& command) noexcept;

 private:
  component::Category category_;
  CommandQueue<ComponentCommand>* command_queue_;
};

}  // namespace ink::component
