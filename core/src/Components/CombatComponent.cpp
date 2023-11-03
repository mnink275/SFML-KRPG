#include <Components/CombatComponent.hpp>

namespace ink::component {

CombatComponent::CombatComponent()
    : Component(Category::kCombat), is_attacking(false) {}

}  // namespace ink::component
