#include <Components/Collision/UnitCollision.hpp>

#include <cassert>

#include <Combat/Melee.hpp>
#include <Combat/Projectile.hpp>
#include <Entities/GameObject.hpp>
#include <Entities/Unit.hpp>

namespace ink::component {

void UnitCollision::handleCollisionWith(SceneNode* owner_node,
                                        NodeCategory category,
                                        const SceneNode* node) {
  assert(dynamic_cast<Unit*>(owner_node));
  auto* unit = static_cast<Unit*>(owner_node);
  switch (category) {
    case NodeCategory::kBullet: {
      const auto* bullet = static_cast<const combat::Projectile*>(node);
      if (unit->GetOwnerType() != bullet->getOwner()) {
        unit->selfDamage(bullet->getDamage());
      }
      break;
    }
    case NodeCategory::kMelee: {
      const auto* melee = static_cast<const combat::Melee*>(node);
      if (unit->GetOwnerType() != melee->getOwner()) {
        unit->selfDamage(melee->getDamage(unit));
      }
      break;
    }
    case NodeCategory::kWall: {
      const auto* wall = static_cast<const GameObject*>(node);
      auto intersection_opt =
          unit->getBoundingRect().findIntersection(wall->getBoundingRect());
      assert(intersection_opt.has_value());
      auto intersection = intersection_opt.value();

      auto is_vertical_collision = intersection.width < intersection.height;
      auto shift = std::min(intersection.width, intersection.height);
      auto player_pos = unit->getPosition();
      auto obstacle_pos = wall->getPosition();
      if (is_vertical_collision) {
        auto sign = (player_pos.x < obstacle_pos.x) ? -1 : +1;
        player_pos.x += shift * sign;
      } else {
        auto sign = (player_pos.y < obstacle_pos.y) ? -1 : +1;
        player_pos.y += shift * sign;
      }
      unit->setPosition(player_pos);
      break;
    }
    case NodeCategory::kDoor: {
      unit->enableDoorInteraction(interact_with);
      interact_with = false;
      break;
    }
    default:
      break;
  }
}

}  // namespace ink::component
