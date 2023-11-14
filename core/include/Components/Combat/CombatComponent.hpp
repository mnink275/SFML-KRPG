#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <Components/Component.hpp>
#include <Entities/Types/EyesDirection.hpp>
#include <SceneNode.hpp>

namespace ink::component {

class CombatComponent : public Component {
 public:
  static constexpr auto kCategory = ComponentCategory::kCombat;
  static constexpr auto kName = "Combat";

 public:
  CombatComponent(int health, sf::Time attack_speed);

  void update(sf::Time dt) noexcept;
  virtual void onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                        EyesDirection eyes_direction) = 0;
  void onAttackUpdate();
  bool isReadyToAttack() const noexcept;

 public:
  enum class AttackState {
    kNone,
    kStarted,
    kInProcess,
    kFinished,
  };

  sf::Time time_since_last_attack;
  sf::Time full_attack_duration;
  int health;
  bool attack_requested;
  bool attack_started;
  ComponentCommand set_attacking_state;
};

}  // namespace ink::component
