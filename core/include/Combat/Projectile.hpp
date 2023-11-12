#pragma once

#include <cstddef>

#include <Entities/GameObject.hpp>
#include <Entities/Types/UnitContext.hpp>

namespace ink::combat {

class Projectile final : public GameObject {
 public:
  Projectile(ComponentManager manager, NodeCategory category, Owner owner);

  std::size_t getDamage() const noexcept;
  Owner getOwner() const noexcept;

 private:
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;

 private:
  Owner owner_;
};

}  // namespace ink::combat
