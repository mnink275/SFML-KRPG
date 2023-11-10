#include <Components/Combat/UnitCombat.hpp>

#include <Combat/Projectile.hpp>
#include <Components/Collision/ProjectileCollision.hpp>
#include <Components/Graphics/SimpleGraphics.hpp>
#include <Components/Physics/BulletPhysics.hpp>
#include <Entities/Unit.hpp>

namespace ink::component {

UnitCombat::UnitCombat(const TextureHolder& texture_holder, OwnerType owner,
                       int health, float attack_speed)
    : CombatComponent(health),
      texture_holder(texture_holder),
      owner(owner),
      attack_speed(sf::seconds(attack_speed)) {
  assert(health > 0);
  assert(attack_speed >= 0.0f);
}

void UnitCombat::onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                          EyesDirection eyes_direction) {
  if (time_since_last_attack >= attack_speed) {
    time_since_last_attack -= attack_speed;
    auto bullet = std::make_unique<combat::Projectile>(
        ComponentManager{
            std::make_unique<component::BulletPhysics>(eyes_direction),
            std::make_unique<component::SimpleGraphics>(
                texture_holder.get(Textures::kBullet), true),
            std::make_unique<component::ProjectileCollision>()},
        NodeCategory::kBullet);
    bullet->setPosition(owner_position);
    bullet->owner = owner;

    node.attachChild(std::move(bullet));
  }
}

}  // namespace ink::component
