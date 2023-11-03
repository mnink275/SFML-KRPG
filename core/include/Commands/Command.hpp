#pragma once

#include <cassert>
#include <functional>

#include <SFML/System/Time.hpp>

#include <Category.hpp>

namespace ink {

class SceneNode;

struct Command {
  using Action = std::function<void(SceneNode&, sf::Time)>;

  Command() : action(), category(static_cast<CategoryType>(Category::None)) {}

  Action action;
  CategoryType category;
};

template <class GameObject, class Func>
Command::Action SendAs(Func func) {
  return [func](SceneNode& node, sf::Time dt) {
    assert(dynamic_cast<GameObject*>(&node) != nullptr);

    func(static_cast<GameObject&>(node), dt);
  };
}

}  // namespace ink
