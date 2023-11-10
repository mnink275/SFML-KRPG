#include <Components/Collision/UnitCollision.hpp>

#include <cassert>

#include <Combat/Projectile.hpp>
#include <Entities/GameStaticObject.hpp>
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
      if (unit->GetOwnerType() != bullet->owner) unit->destroy();
      break;
    }
    case NodeCategory::kWall: {
      const auto* wall = static_cast<const GameStaticObject*>(node);
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
    default:
      break;
  }
}

}  // namespace ink::component
