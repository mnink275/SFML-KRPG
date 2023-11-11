#pragma once

#include <cstddef>
#include <set>

#include <SFML/System/Time.hpp>

#include <Entities/GameObject.hpp>
#include <Entities/UnitContext.hpp>

namespace ink::combat {

class Melee final : public GameObject {
 public:
  Melee(ComponentManager manager, NodeCategory category, OwnerType owner);

  std::size_t getDamage(const SceneNode* node) const;
  OwnerType getOwner() const noexcept;

  void addDamaged(const SceneNode* node);

 private:
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;

 private:
  sf::Time timer_;
  const sf::Time kLifeTime;
  std::set<const SceneNode*> already_damaged_;
  OwnerType owner_;
};

}  // namespace ink::combat
