#pragma once

#include <cassert>
#include <functional>

#include <SFML/System/Time.hpp>

#include <Components/Category.hpp>

namespace ink::component {
class Component;
}  // namespace ink::component

namespace ink {

struct ComponentCommand {
  using Action = std::function<void(component::Component&, sf::Time)>;

  ComponentCommand()
      : action(),
        category(
            static_cast<component::CategoryType>(component::Category::None)) {}

  Action action;
  component::CategoryType category;
};

template <class ConcreteComponent, class Func>
ComponentCommand::Action SendAsComp(Func func) {
  return [func](component::Component& component, sf::Time dt) {
    assert(dynamic_cast<ConcreteComponent*>(&component) != nullptr);

    func(static_cast<ConcreteComponent&>(component), dt);
  };
}

}  // namespace ink
