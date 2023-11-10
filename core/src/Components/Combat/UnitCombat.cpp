#include <Components/Combat/UnitCombat.hpp>

#include <Combat/Projectile.hpp>
#include <Components/Collision/ProjectileCollision.hpp>
#include <Components/Graphics/SimpleGraphics.hpp>
#include <Components/Physics/BulletPhysics.hpp>
#include <Entities/Unit.hpp>

namespace ink::component {

UnitCombat::UnitCombat(const TextureHolder& texture_holder, OwnerType owner)
    : texture_holder(texture_holder), owner(owner) {}

void UnitCombat::onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                          EyesDirection eyes_direction) {
  auto bullet = std::make_unique<combat::Projectile>(
      std::make_unique<component::BulletPhysics>(eyes_direction),
      std::make_unique<component::SimpleGraphics>(
          texture_holder.get(Textures::kBullet), true),
      nullptr, nullptr, std::make_unique<component::ProjectileCollision>(),
      NodeCategory::kBullet);
  bullet->setPosition(owner_position);
  bullet->owner = owner;

  node.attachChild(std::move(bullet));
}

}  // namespace ink::component
