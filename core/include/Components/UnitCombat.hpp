#pragma once

#include <Components/CombatComponent.hpp>
#include <Entities/UnitContext.hpp>
#include <Resource/ResourceHolder.hpp>
#include <Resource/ResourceIdentifiers.hpp>

namespace ink::component {

class UnitCombat final : public CombatComponent {
 public:
  explicit UnitCombat(const TextureHolder& texture_holder, OwnerType owner);

  void onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                EyesDirection eyes_direction) override;

  ~UnitCombat() override = default;

  const TextureHolder& texture_holder;
  const OwnerType owner;
};

}  // namespace ink::component
