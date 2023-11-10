#include <Components/Collision/CollisionComponent.hpp>

#include <Commands/Category/ComponentCategory.hpp>

namespace ink::component {

CollisionComponent::CollisionComponent()
    : Component(ComponentCategory::kCollision) {}

}  // namespace ink::component
