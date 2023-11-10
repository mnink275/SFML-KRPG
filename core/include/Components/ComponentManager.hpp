#pragma once

#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

#include <Commands/Category/ComponentCategory.hpp>
#include <Commands/CommandQueue.hpp>
#include <Components/Collision/CollisionComponent.hpp>
#include <Components/Combat/CombatComponent.hpp>
#include <Components/Component.hpp>
#include <Components/Graphics/GraphicsComponent.hpp>
#include <Components/Input/InputComponent.hpp>
#include <Components/Physics/PhysicsComponent.hpp>

namespace ink {

class ComponentManager final {
 private:
  using SharedPtr = std::shared_ptr<component::Component>;

 public:
  template <class... Args>
  ComponentManager(Args&&... args) {
    (addComponent(std::forward<Args&&>(args)), ...);
  }

  template <class ComponentType, typename = std::enable_if_t<std::is_base_of_v<
                                     component::Component, ComponentType>>>
  std::shared_ptr<ComponentType> findComponent() const {
    auto category = ComponentType::kCategory;
    auto it = std::find_if(components_.begin(), components_.end(),
                           [category](SharedPtr component) {
                             return component->getCategory() == category;
                           });
    // TODO: return "empty" component to do nothing outside
    if (it == components_.end()) {
      std::cout << "Calling for a missing " << ComponentType::kName
                << " component\n";
      assert(false);
    }

    return std::dynamic_pointer_cast<ComponentType>(*it);
  }

  void setCommandQueue(CommandQueue<ComponentCommand>* command_queue) noexcept {
    for (auto component : components_) {
      component->setCommandQueue(command_queue);
    }
  }

  void onCommand(const ComponentCommand& command, sf::Time dt) {
    for (auto component : components_) {
      component->onCommand(command, dt);
    }
  }

 private:
  void addComponent(std::unique_ptr<component::Component> component) {
    components_.push_back(std::move(component));
  }

 private:
  std::vector<SharedPtr> components_;
};

}  // namespace ink
