#pragma once

#include <cassert>
#include <functional>

#include <SFML/System/Time.hpp>

#include <Category.hpp>
#include <Components/Category.hpp>

namespace ink::component {
class Component;
}  // namespace ink::component
namespace ink {
class SceneNode;
}  // namespace ink

namespace ink {

template <class Base, class Category>
struct Command {
  using Action = std::function<void(Base&, sf::Time)>;

  Command() : action(), category(0) {}

  Action action;
  unsigned int category;
};

using NodeCommand = Command<SceneNode, Category>;
using ComponentCommand = Command<component::Component, component::Category>;

template <class Derived>
using GetBase = std::conditional_t<std::is_base_of_v<SceneNode, Derived>,
                                   SceneNode, component::Component>;

template <class Derived, class Func>
typename std::conditional_t<std::is_same_v<SceneNode, GetBase<Derived>>,
                            NodeCommand, ComponentCommand>::Action
SendTo(Func func) {
  return [func](GetBase<Derived>& node, sf::Time dt) {
    assert(dynamic_cast<Derived*>(&node) != nullptr);

    func(static_cast<Derived&>(node), dt);
  };
}

}  // namespace ink
