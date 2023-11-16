#pragma once

#include <functional>

#include <fmt/format.h>
#include <SFML/System/Time.hpp>

#include <Commands/Category/ComponentCategory.hpp>
#include <Commands/Category/NodeCategory.hpp>
#include <Utils/Assert.hpp>

namespace ink::component {
class Component;
}  // namespace ink::component
namespace ink {
class SceneNode;
}  // namespace ink

namespace ink {

template <class Base, class CategoryType>
struct Command final {
  using Action = std::function<void(Base&, sf::Time)>;
  using Receiver = CategoryType;

  Command() = default;
  Command(CategoryType category, Action action)
      : action(action), category(category), delay(sf::Time::Zero) {}
  Command(CategoryType category, Action action, sf::Time delay)
      : action(action), category(category), delay(delay) {}

  Action action;
  CategoryType category;
  sf::Time delay;
};

using NodeCommand = Command<SceneNode, NodeCategory>;
using ComponentCommand = Command<component::Component, ComponentCategory>;

template <class Derived>
using GetBase = std::conditional_t<std::is_base_of_v<SceneNode, Derived>,
                                   SceneNode, component::Component>;

template <class Derived, class Func>
typename std::conditional_t<std::is_same_v<SceneNode, GetBase<Derived>>,
                            NodeCommand, ComponentCommand>::Action
SendTo(Func func) {
  return [func](GetBase<Derived>& node, sf::Time dt) {
    ASSERT(dynamic_cast<Derived*>(&node) != nullptr);

    func(static_cast<Derived&>(node), dt);
  };
}

}  // namespace ink
