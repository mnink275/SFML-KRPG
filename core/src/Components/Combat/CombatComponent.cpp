#include <Components/Combat/CombatComponent.hpp>

namespace ink::component {

CombatComponent::CombatComponent()
    : Component(kCategory), is_attacking(false) {}

}  // namespace ink::component
