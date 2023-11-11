#pragma once

#include <SFML/System/Time.hpp>

#include <Commands/Category/ComponentCategory.hpp>
#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>

namespace ink::component {

class Component {
 public:
  explicit Component(ComponentCategory category);
  virtual ~Component() = default;

  Component(const Component&) = delete;
  Component& operator=(const Component&) = delete;

  Component(Component&&) = delete;
  Component& operator=(Component&&) = delete;

  virtual void onCommand(const ComponentCommand& command, sf::Time dt);
  virtual void setCommandQueue(
      CommandQueue<ComponentCommand>* command_queue) noexcept;
  virtual void sendCommand(ComponentCommand& command) noexcept;

  ComponentCategory getCategory() const noexcept;

 private:
  ComponentCategory category_;
  CommandQueue<ComponentCommand>* command_queue_;
};

}  // namespace ink::component
