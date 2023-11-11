#include <Components/Collision/CollisionComponent.hpp>

#include <Commands/Category/ComponentCategory.hpp>

namespace ink::component {

CollisionComponent::CollisionComponent()
    : Component(kCategory), interact_with(false) {}

}  // namespace ink::component
