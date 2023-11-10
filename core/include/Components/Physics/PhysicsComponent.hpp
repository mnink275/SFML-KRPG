#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <Components/Component.hpp>

namespace ink::component {

class PhysicsComponent : public Component {
 public:
  PhysicsComponent();
  virtual ~PhysicsComponent() = default;

  virtual sf::Vector2f getTransform(sf::Time dt) = 0;

  sf::Vector2f velocity{};
};

}  // namespace ink::component
