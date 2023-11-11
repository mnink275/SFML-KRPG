#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <Components/Component.hpp>

namespace ink::component {

class PhysicsComponent : public Component {
 public:
  static constexpr auto kCategory = ComponentCategory::kPhysics;
  static constexpr auto kName = "Physics";

 public:
  PhysicsComponent();

  virtual sf::Vector2f getTransform(sf::Time dt) = 0;

  sf::Vector2f velocity{};
};

}  // namespace ink::component
