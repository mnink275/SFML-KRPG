#pragma once

#include <Components/Combat/CombatComponent.hpp>
#include <Entities/UnitContext.hpp>
#include <Resource/ResourceHolder.hpp>
#include <Resource/ResourceIdentifiers.hpp>

namespace ink::component {

class UnitCombat final : public CombatComponent {
 public:
  UnitCombat(const TextureHolder& texture_holder, OwnerType owner, int health,
             float attack_speed_by_second);

  void onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                EyesDirection eyes_direction) override;

  const TextureHolder& texture_holder;
  const OwnerType owner;
  const sf::Time attack_speed;
};

}  // namespace ink::component
