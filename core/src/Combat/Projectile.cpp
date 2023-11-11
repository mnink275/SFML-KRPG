#include <Combat/Projectile.hpp>

#include <Components/Physics/PhysicsComponent.hpp>
#include <Entities/Unit.hpp>

namespace ink::combat {

Projectile::Projectile(ComponentManager manager, NodeCategory category,
                       OwnerType owner)
    : GameObject(std::move(manager), category), owner_(owner) {}

std::size_t Projectile::getDamage() const noexcept {
  // TODO: redirect to CombatComponent???
  return 5;
}

OwnerType Projectile::getOwner() const noexcept { return owner_; }

void Projectile::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>&) {
  auto physics = manager_.findComponent<component::PhysicsComponent>();
  auto transforms = physics->getTransform(dt);
  Transformable::move(transforms);
};

}  // namespace ink::combat
