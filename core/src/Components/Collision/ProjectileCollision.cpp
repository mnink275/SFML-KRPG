#include <Components/Collision/ProjectileCollision.hpp>

#include <Combat/Projectile.hpp>
#include <Entities/Unit.hpp>
#include <Utils/Assert.hpp>

namespace ink::component {

void ProjectileCollision::handleCollisionWith(SceneNode* owner_node,
                                              NodeCategory category,
                                              const SceneNode* node) {
  auto* bullet = dynamic_cast<combat::Projectile*>(owner_node);
  ASSERT(bullet);
  switch (category) {
    case NodeCategory::kUnit: {
      const auto* unit = dynamic_cast<const Unit*>(node);
      ASSERT(unit);
      if (bullet->getOwner() != unit->getOwnerType()) bullet->destroy();
      break;
    }
    case NodeCategory::kWall: {
      bullet->destroy();
      break;
    }
    default:
      break;
  }
}

}  // namespace ink::component
