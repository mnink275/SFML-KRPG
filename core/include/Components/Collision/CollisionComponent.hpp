#pragma once

#include <Components/Component.hpp>

namespace ink::component {

class CollisionComponent : public Component {
 public:
  static constexpr auto kCategory = ComponentCategory::kCollision;
  static constexpr auto kName = "Collision";

 public:
  CollisionComponent();

  virtual void handleCollisionWith(SceneNode* owner_node, NodeCategory category,
                                   const SceneNode* node) = 0;
};

}  // namespace ink::component
