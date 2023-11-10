#pragma once

#include <Components/Collision/CollisionComponent.hpp>

namespace ink::component {

class ProjectileCollision final : public CollisionComponent {
 public:
  void handleCollisionWith(SceneNode* owner_node, NodeCategory category,
                           const SceneNode* node) override;
};

}  // namespace ink::component
