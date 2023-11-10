#pragma once

#include <Entities/GameObject.hpp>
#include <Entities/UnitContext.hpp>

namespace ink::combat {

class Projectile : public GameObject {
 public:
  using GameObject::GameObject;

  OwnerType owner;

 private:
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;
};

}  // namespace ink::combat
