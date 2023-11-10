#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/Component.hpp>
#include <Entities/EyesDirection.hpp>
#include <SceneNode.hpp>

namespace ink::component {

class CombatComponent : public Component {
 public:
  CombatComponent();
  virtual ~CombatComponent() = default;

  virtual void onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                        EyesDirection eyes_direction) = 0;

  bool is_attacking;
};

}  // namespace ink::component
