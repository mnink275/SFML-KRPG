#include <Combat/Projectile.hpp>

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

}  // namespace ink::combat
