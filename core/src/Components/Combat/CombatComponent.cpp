#include <Components/Combat/CombatComponent.hpp>

namespace ink::component {

CombatComponent::CombatComponent(int health)
    : Component(kCategory), is_attacking(false), health(health) {}

}  // namespace ink::component
