#pragma once

#include <cstddef>

#include <Entities/GameObject.hpp>
#include <Entities/UnitContext.hpp>

namespace ink::combat {

class Projectile final : public GameObject {
 public:
  using GameObject::GameObject;

  std::size_t getDamage() const noexcept;

 public:
  OwnerType owner;

 private:
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;
};

}  // namespace ink::combat
