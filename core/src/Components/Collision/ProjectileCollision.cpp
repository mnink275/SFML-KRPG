#include <Components/Collision/ProjectileCollision.hpp>

#include <Combat/Projectile.hpp>
#include <Entities/Unit.hpp>
#include <Utils/Assert.hpp>

namespace ink::component {

void ProjectileCollision::handleCollisionWith(SceneNode* owner_node,
                                              NodeCategory category,
                                              const SceneNode* node) {
  ASSERT(dynamic_cast<combat::Projectile*>(owner_node));
  auto* bullet = static_cast<combat::Projectile*>(owner_node);
  switch (category) {
    case NodeCategory::kUnit: {
      const auto* unit = static_cast<const Unit*>(node);
      if (bullet->getOwner() != unit->GetOwnerType()) bullet->destroy();
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
