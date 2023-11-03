#include <Components/CombatComponent.hpp>

namespace ink::component {

CombatComponent::CombatComponent()
    : Component(ComponentCategory::kCombat), is_attacking(false) {}

}  // namespace ink::component
