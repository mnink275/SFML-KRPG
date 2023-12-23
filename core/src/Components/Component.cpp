#include <Components/Component.hpp>

#include <fmt/format.h>

#include <Utils/Assert.hpp>

namespace ink::component {

Component::Component(ComponentCategory category)
    : category_(category), command_queue_(nullptr) {}

void Component::onCommand(const ComponentCommand& command, sf::Time dt) {
  if ((static_cast<CategoryUnderlying>(command.category) &
       static_cast<CategoryUnderlying>(category_)) != 0u) {
    command.action(*this, dt);
  }
}

void Component::setCommandQueue(
    CommandQueue<ComponentCommand>* command_queue) noexcept {
  command_queue_ = command_queue;
}

void Component::sendCommand(ComponentCommand& command) noexcept {
  ASSERT_MSG(command_queue_, "Need to set component command queue");
  command_queue_->push(command);
}

ComponentCategory Component::getCategory() const noexcept { return category_; }

}  // namespace ink::component
