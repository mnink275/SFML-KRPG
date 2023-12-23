#include <Combat/Projectile.hpp>

#include <Components/Physics/PhysicsComponent.hpp>
#include <Entities/Unit.hpp>

namespace ink::combat {

Projectile::Projectile(ComponentManager manager, NodeCategory category,
                       Owner owner)
    : GameObject(std::move(manager), category), owner_(owner) {}

// TODO: make `getDamage()` virtulal
// NOLINTNEXTLINE (readability-convert-member-functions-to-static)
std::size_t Projectile::getDamage() const noexcept {
  // TODO: redirect to CombatComponent???

  static const std::size_t kDamage = 5;
  return kDamage;
}

Owner Projectile::getOwner() const noexcept { return owner_; }

void Projectile::updateCurrent(sf::Time dt,
                               CommandQueue<NodeCommand>& /*commands*/) {
  auto physics = manager_.findComponent<component::PhysicsComponent>();
  auto transforms = physics->getTransform(dt);
  Transformable::move(transforms);
};

}  // namespace ink::combat
