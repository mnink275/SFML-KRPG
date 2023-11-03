#include <Components/Component.hpp>

#include <iostream>

namespace ink::component {

Component::Component(component::Category category)
    : category_(category), command_queue_(nullptr) {}

void Component::onCommand(const ComponentCommand& command, sf::Time dt) {
  if (command.category & static_cast<component::CategoryType>(category_))
    command.action(*this, dt);
}

void Component::setCommandQueue(
    CommandQueue<ComponentCommand>* command_queue) noexcept {
  command_queue_ = command_queue;
}

void Component::sendCommand(ComponentCommand& command) noexcept {
  if (command_queue_) {
    command_queue_->push(command);
  } else {
    std::cout << "Warnings: need to set component command queue\n";
  }
}

}  // namespace ink::component
