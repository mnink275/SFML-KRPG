#include <Combat/Projectile.hpp>

#include <Components/Physics/PhysicsComponent.hpp>
#include <Entities/Unit.hpp>

namespace ink::combat {

void Projectile::handleCollisionWith(NodeCategory category,
                                     const SceneNode* node) {
  switch (category) {
    case NodeCategory::kUnit: {
      const auto* unit = static_cast<const Unit*>(node);
      if (owner != unit->GetOwnerType()) destroy();
      break;
    }
    case NodeCategory::kWall: {
      destroy();
      break;
    }
    default:
      break;
  }
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>&) {
  auto physics = manager_.findComponent<component::PhysicsComponent>();
  auto transforms = physics->getTransform(dt);
  Transformable::move(transforms);
};

}  // namespace ink::combat
