#include <Components/Collision/MeleeCollision.hpp>

#include <Combat/Melee.hpp>
#include <Entities/Unit.hpp>
#include <Utils/Assert.hpp>

namespace ink::component {

void MeleeCollision::handleCollisionWith(SceneNode* owner_node,
                                         NodeCategory category,
                                         const SceneNode* node) {
  auto* melee = dynamic_cast<combat::Melee*>(owner_node);
  ASSERT(melee);
  switch (category) {
    case NodeCategory::kUnit: {
      const auto* unit = dynamic_cast<const Unit*>(node);
      ASSERT(unit);
      if (melee->getOwner() != unit->GetOwnerType()) {
        melee->addDamaged(node);
      }
      break;
    }
    default:
      break;
  }
}

}  // namespace ink::component
