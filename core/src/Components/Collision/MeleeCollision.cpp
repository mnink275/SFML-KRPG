#include <Components/Collision/MeleeCollision.hpp>

#include <Combat/Melee.hpp>
#include <Entities/Unit.hpp>
#include <Utils/Assert.hpp>

namespace ink::component {

void MeleeCollision::handleCollisionWith(SceneNode* owner_node,
                                         NodeCategory category,
                                         const SceneNode* node) {
  ASSERT(dynamic_cast<combat::Melee*>(owner_node));
  auto* melee = static_cast<combat::Melee*>(owner_node);
  switch (category) {
    case NodeCategory::kUnit: {
      const auto* unit = static_cast<const Unit*>(node);
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
