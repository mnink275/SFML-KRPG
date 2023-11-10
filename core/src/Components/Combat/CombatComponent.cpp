#include <Components/Combat/CombatComponent.hpp>

namespace ink::component {

CombatComponent::CombatComponent(int health)
    : Component(kCategory),
      time_since_last_attack(sf::Time::Zero),
      health(health),
      is_attacking(false) {}

void CombatComponent::updateTimeSineLastAttack(sf::Time dt) noexcept {
  time_since_last_attack += dt;
}

}  // namespace ink::component
