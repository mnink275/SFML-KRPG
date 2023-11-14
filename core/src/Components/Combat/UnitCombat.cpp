#include <Components/Combat/UnitCombat.hpp>

#include <SFML/System/Vector2.hpp>

#include <Combat/Melee.hpp>
#include <Combat/Projectile.hpp>
#include <Components/Collision/MeleeCollision.hpp>
#include <Components/Collision/ProjectileCollision.hpp>
#include <Components/Graphics/SimpleGraphics.hpp>
#include <Components/Physics/BulletPhysics.hpp>
#include <Components/Physics/SimplePhysics.hpp>
#include <Entities/Unit.hpp>
#include <Utils/Assert.hpp>

namespace ink::component {

UnitCombat::UnitCombat(const TextureHolder& texture_holder, Owner owner,
                       int health, float attack_speed, Weapon weapon)
    : CombatComponent(health, sf::seconds(attack_speed)),
      texture_holder(texture_holder),
      owner(owner),
      weapon(weapon) {
  ASSERT(health > 0);
  ASSERT(attack_speed >= 0.0f);
}

void UnitCombat::onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                          EyesDirection eyes_direction) {
  switch (weapon) {
    case Weapon::kGun: {
      auto bullet = std::make_unique<combat::Projectile>(
          ComponentManager{
              std::make_unique<component::BulletPhysics>(eyes_direction),
              std::make_unique<component::SimpleGraphics>(
                  texture_holder.get(Textures::kBullet), true),
              std::make_unique<component::ProjectileCollision>()},
          NodeCategory::kBullet, owner);
      bullet->setPosition(owner_position);

      node.attachChild(std::move(bullet));
      break;
    }
    case Weapon::kSword: {
      // TODO: mapping sword animation to hit area sizes
      // (e.g. SwordSizes[Textures::CommonSword] -> sf::Vector2i{30, 70})
      auto sword = std::make_unique<combat::Melee>(
          ComponentManager{std::make_unique<component::SimplePhysics>(),
                           std::make_unique<component::SimpleGraphics>(
                               texture_holder.get(Textures::kDoor),
                               sf::Vector2i{30, 70}, true),
                           std::make_unique<component::MeleeCollision>()},
          NodeCategory::kMelee, owner);
      // TODO: need access to player sprite sizes
      if (eyes_direction == EyesDirection::kLeft) {
        sword->setPosition(owner_position + sf::Vector2f{-30.0f, 0.0f});
      } else {
        sword->setPosition(owner_position + sf::Vector2f{30.0f, 0.0f});
      }

      node.attachChild(std::move(sword));
      break;
    }
  }
}

}  // namespace ink::component
