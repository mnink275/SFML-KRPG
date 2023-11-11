#pragma once

#include <cstddef>

#include <Entities/GameObject.hpp>
#include <Entities/UnitContext.hpp>

namespace ink::combat {

class Projectile final : public GameObject {
 public:
  Projectile(ComponentManager manager, NodeCategory category, OwnerType owner);

  std::size_t getDamage() const noexcept;
  OwnerType getOwner() const noexcept;

 private:
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;

 private:
  OwnerType owner_;
};

}  // namespace ink::combat
