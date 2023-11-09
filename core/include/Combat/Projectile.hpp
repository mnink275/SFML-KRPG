#pragma once

#include <Entities/GameObject.hpp>
#include <Entities/UnitContext.hpp>

namespace ink::combat {

class Projectile : public GameObject {
 public:
  using GameObject::GameObject;

  void handleCollisionWith(NodeCategory category,
                           const SceneNode* node) override;

  OwnerType owner;
};

}  // namespace ink::combat
