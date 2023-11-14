#include <Components/Combat/CombatComponent.hpp>

#include <Components/Graphics/GraphicsComponent.hpp>
#include <Entities/Types/ObjectState.hpp>

namespace ink::component {

namespace {

struct SetAttackStateCommand final {
  SetAttackStateCommand(sf::Time freezing_time)
      : freezing_time(freezing_time) {}

  void operator()(component::GraphicsComponent& graphics, sf::Time) const {
    graphics.setObjectState(ObjectState::kAttacking, FreezeFor{freezing_time});
  }

  sf::Time freezing_time;
};

}  // namespace

CombatComponent::CombatComponent(int health, sf::Time attack_speed)
    : Component(kCategory),
      time_since_last_attack(sf::Time::Zero),
      // duration is a attack_speed, no delay between attack animation
      full_attack_duration(attack_speed),
      health(health),
      attack_requested(false),
      attack_started(false) {
  set_attacking_state.category = ComponentCategory::kGraphics;
  set_attacking_state.action =
      SendTo<GraphicsComponent>(SetAttackStateCommand{full_attack_duration});
}

void CombatComponent::update(sf::Time dt) noexcept {
  time_since_last_attack += dt;
  if (attack_requested) {
    attack_requested = false;
    sendCommand(set_attacking_state);
  }
}

void CombatComponent::onAttackUpdate() {
  time_since_last_attack %= full_attack_duration;
  attack_started = false;
}

bool CombatComponent::isReadyToAttack() const noexcept {
  return attack_started;
}

}  // namespace ink::component
