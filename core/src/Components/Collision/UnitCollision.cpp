#include <Components/Collision/UnitCollision.hpp>

#include <Combat/Melee.hpp>
#include <Combat/Projectile.hpp>
#include <Entities/GameObject.hpp>
#include <Entities/Unit.hpp>
#include <Utils/Assert.hpp>

namespace ink::component {

void UnitCollision::handleCollisionWith(SceneNode* owner_node,
                                        NodeCategory category,
                                        const SceneNode* node) {
  auto* unit = dynamic_cast<Unit*>(owner_node);
  ASSERT(unit);
  switch (category) {
    case NodeCategory::kBullet: {
      const auto* bullet = dynamic_cast<const combat::Projectile*>(node);
      ASSERT(bullet);
      if (unit->GetOwnerType() != bullet->getOwner()) {
        unit->selfDamage(bullet->getDamage());
      }
      break;
    }
    case NodeCategory::kMelee: {
      const auto* melee = dynamic_cast<const combat::Melee*>(node);
      ASSERT(melee);
      if (unit->GetOwnerType() != melee->getOwner()) {
        unit->selfDamage(melee->getDamage(unit));
      }
      break;
    }
    case NodeCategory::kWall: {
      const auto* wall = dynamic_cast<const GameObject*>(node);
      ASSERT(wall);
      handleWallCollision(unit, wall);
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

void UnitCollision::handleWallCollision(Unit* unit, const GameObject* wall) {
  auto intersection_opt =
      unit->getBoundingRect().findIntersection(wall->getBoundingRect());
  if (!intersection_opt.has_value()) return;
  const auto intersection = intersection_opt.value();

  const auto is_vertical_collision = intersection.width < intersection.height;
  const auto shift = std::min(intersection.width, intersection.height);
  auto player_pos = unit->getPosition();
  const auto obstacle_pos = wall->getPosition();
  if (is_vertical_collision) {
    const auto sign = (player_pos.x < obstacle_pos.x) ? -1.f : +1.f;
    player_pos.x += shift * sign;
  } else {
    const auto sign = (player_pos.y < obstacle_pos.y) ? -1.f : +1.f;
    player_pos.y += shift * sign;
  }
  unit->setPosition(player_pos);
}

}  // namespace ink::component
