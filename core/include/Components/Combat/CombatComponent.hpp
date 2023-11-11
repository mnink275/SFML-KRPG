#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <Components/Component.hpp>
#include <Entities/EyesDirection.hpp>
#include <SceneNode.hpp>

namespace ink::component {

class CombatComponent : public Component {
 public:
  static constexpr auto kCategory = ComponentCategory::kCombat;
  static constexpr auto kName = "Combat";

 public:
  CombatComponent(int health);

  void updateTimeSineLastAttack(sf::Time dt) noexcept;
  virtual void onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                        EyesDirection eyes_direction) = 0;

  sf::Time time_since_last_attack;
  int health;
  bool is_attacking;
};

}  // namespace ink::component
