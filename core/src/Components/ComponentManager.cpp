#include <Components/ComponentManager.hpp>

#include <memory>

#include <Commands/CommandQueue.hpp>
#include <Components/Component.hpp>

namespace ink {

void ComponentManager::setCommandQueue(
    CommandQueue<ComponentCommand>* command_queue) noexcept {
  for (const auto& component : components_) {
    component->setCommandQueue(command_queue);
  }
}

void ComponentManager::onCommand(const ComponentCommand& command, sf::Time dt) {
  for (const auto& component : components_) {
    component->onCommand(command, dt);
  }
}

void ComponentManager::addComponent(
    std::unique_ptr<component::Component> component) {
  components_.push_back(std::move(component));
}

}  // namespace ink
