#include <Combat/Melee.hpp>

namespace ink::combat {

Melee::Melee(ComponentManager manager, NodeCategory category, Owner owner)
    : GameObject(std::move(manager), category),
      timer_(sf::Time::Zero),
      kLifeTime(sf::seconds(0.1f)),
      owner_(owner) {}

std::size_t Melee::getDamage(const SceneNode* node) const {
  // TODO: redirect to CombatComponent???

  if (already_damaged_.count(node)) return 0;

  static const std::size_t kDamage = 5;
  return kDamage;
}

Owner Melee::getOwner() const noexcept { return owner_; }

void Melee::addDamaged(const SceneNode* node) { already_damaged_.insert(node); }

void Melee::updateCurrent(sf::Time dt,
                          CommandQueue<NodeCommand>& /*commands*/) {
  timer_ += dt;
  if (timer_ >= kLifeTime) destroy();
}

}  // namespace ink::combat
