#include <Combat/Projectile.hpp>

#include <Components/Physics/PhysicsComponent.hpp>
#include <Entities/Unit.hpp>

namespace ink::combat {

void Projectile::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>&) {
  auto physics = manager_.findComponent<component::PhysicsComponent>();
  auto transforms = physics->getTransform(dt);
  Transformable::move(transforms);
};

}  // namespace ink::combat
