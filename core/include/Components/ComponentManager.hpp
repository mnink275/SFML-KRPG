#pragma once

#include <memory>
#include <type_traits>
#include <vector>

#include <fmt/format.h>

#include <Commands/Category/ComponentCategory.hpp>
#include <Commands/CommandQueue.hpp>
#include <Components/Component.hpp>
#include <Utils/Assert.hpp>

namespace ink {

class ComponentManager final {
 private:
  using SharedPtr = std::shared_ptr<component::Component>;

 public:
  template <class... Args>
  explicit ComponentManager(Args&&... args) {
    (addComponent(std::forward<Args&&>(args)), ...);
  }

  ~ComponentManager() = default;

  ComponentManager(const ComponentManager&) = delete;
  ComponentManager& operator=(const ComponentManager&) = delete;

  ComponentManager(ComponentManager&&) = default;
  ComponentManager& operator=(ComponentManager&&) = default;

  template <class ComponentType, typename = std::enable_if_t<std::is_base_of_v<
                                     component::Component, ComponentType>>>
  std::shared_ptr<ComponentType> findComponent() const {
    auto category = ComponentType::kCategory;
    auto it = std::find_if(components_.begin(), components_.end(),
                           [category](const SharedPtr& component) {
                             return component->getCategory() == category;
                           });
    // TODO: return "empty" component to do nothing outside
    ASSERT_MSG(it != components_.end(),
               fmt::format("Calling for a missing '{}' component",
                           ComponentType::kName));

    return std::dynamic_pointer_cast<ComponentType>(*it);
  }

  void setCommandQueue(CommandQueue<ComponentCommand>* command_queue) noexcept;

  void onCommand(const ComponentCommand& command, sf::Time dt);

 private:
  void addComponent(std::unique_ptr<component::Component> component);

 private:
  std::vector<SharedPtr> components_;
};

}  // namespace ink
