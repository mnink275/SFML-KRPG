#include <Entities/GameObject.hpp>

namespace ink {

GameObject::GameObject(std::unique_ptr<component::PhysicsComponent> physics,
                       std::unique_ptr<component::GraphicsComponent> graphics,
                       std::unique_ptr<component::InputComponent> inputs)
    : physics_impl_(std::move(physics)),
      graphics_impl_(std::move(graphics)),
      inputs_impl_(std::move(inputs)) {}

void GameObject::drawCurrent(sf::RenderTarget& target,
                             const sf::RenderStates states) const {
  graphics_impl_->draw(target, states);
}

void GameObject::updateCurrent(sf::Time dt) {
  auto transforms = physics_impl_->getTransform(dt);
  Transformable::move(transforms);
};

}  // namespace ink
