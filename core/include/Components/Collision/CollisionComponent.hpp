#pragma once

#include <Components/Component.hpp>

namespace ink::component {

class CollisionComponent : public Component {
 public:
  CollisionComponent();
  virtual ~CollisionComponent() = default;

  virtual void handleCollisionWith(SceneNode* owner_node, NodeCategory category,
                                   const SceneNode* node) = 0;
};

}  // namespace ink::component
