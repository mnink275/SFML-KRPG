#pragma once

#include <Combat/Projectile.hpp>
#include <Components/BulletPhysics.hpp>
#include <Components/CombatComponent.hpp>
#include <Components/SimpleGraphics.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/RoomManager.hpp>

namespace ink::component {

class PlayerCombat final : public CombatComponent {
 public:
  explicit PlayerCombat(room::RoomManager& room_manager,
                        const TextureHolder& texture_holder)
      : room_manager(room_manager), texture_holder(texture_holder) {}

  void onAttack(const sf::Vector2f& owner_position) override {
    auto bullet = std::make_unique<combat::Projectile>(
        std::make_unique<component::BulletPhysics>(is_turned_right),
        std::make_unique<component::SimpleGraphics>(
            texture_holder.get(Textures::kBullet), true),
        nullptr, nullptr);
    bullet->setPosition(owner_position);

    room_manager.onProjectileAttack(std::move(bullet));
  }

  ~PlayerCombat() override = default;

  bool is_turned_right{true};
  room::RoomManager& room_manager;
  const TextureHolder& texture_holder;
};

}  // namespace ink::component
