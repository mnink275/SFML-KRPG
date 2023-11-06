#include <Entities/GameObject.hpp>

namespace ink {

GameObject::GameObject(std::unique_ptr<component::PhysicsComponent> physics,
                       std::unique_ptr<component::GraphicsComponent> graphics,
                       std::unique_ptr<component::InputComponent> inputs,
                       std::unique_ptr<component::CombatComponent> combat,
                       NodeCategory category)
    : SceneNode(category),
      physics_impl_(std::move(physics)),
      graphics_impl_(std::move(graphics)),
      inputs_impl_(std::move(inputs)),
      combat_impl_(std::move(combat)) {}

sf::FloatRect GameObject::getBoundingRect() const {
  return getWorldTransform().transformRect(graphics_impl_->getGlobalBounds());
}

void GameObject::drawCurrent(sf::RenderTarget& target,
                             const sf::RenderStates states) const {
  graphics_impl_->draw(target, states);
}

void GameObject::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>&) {
  auto transforms = physics_impl_->getTransform(dt);
  Transformable::move(transforms);
};

}  // namespace ink
