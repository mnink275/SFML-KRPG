#pragma once

#include <Components/Collision/CollisionComponent.hpp>
#include <Entities/GameObject.hpp>
#include <Entities/Unit.hpp>

namespace ink::component {

class UnitCollision final : public CollisionComponent {
 public:
  void handleCollisionWith(SceneNode* owner_node, NodeCategory category,
                           const SceneNode* node) override;

 private:
  static void handleWallCollision(Unit* unit, const GameObject* wall);
};

}  // namespace ink::component
