#include <Components/PlayerCombat.hpp>

#include <Combat/Projectile.hpp>
#include <Components/BulletPhysics.hpp>
#include <Components/SimpleGraphics.hpp>

namespace ink::component {

PlayerCombat::PlayerCombat(const TextureHolder& texture_holder)
    : texture_holder(texture_holder) {}

void PlayerCombat::onAttack(SceneNode& node, const sf::Vector2f& owner_position,
                            EyesDirection eyes_direction) {
  auto bullet = std::make_unique<combat::Projectile>(
      std::make_unique<component::BulletPhysics>(eyes_direction),
      std::make_unique<component::SimpleGraphics>(
          texture_holder.get(Textures::kBullet), true),
      nullptr, nullptr);
  bullet->setPosition(owner_position);
  node.attachChild(std::move(bullet));
}

}  // namespace ink::component
