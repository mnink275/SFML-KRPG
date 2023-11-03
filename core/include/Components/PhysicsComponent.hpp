#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <Components/Component.hpp>
#include <Entities/VelocityModule.hpp>

namespace ink::component {

class PhysicsComponent : public Component {
 public:
  PhysicsComponent();
  virtual ~PhysicsComponent() = default;

  virtual sf::Vector2f getTransform(sf::Time dt) = 0;

  VelocityModule velocity{};
};

}  // namespace ink::component
