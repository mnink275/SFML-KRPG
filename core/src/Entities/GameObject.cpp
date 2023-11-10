#include <Entities/GameObject.hpp>

namespace ink {

GameObject::GameObject(std::unique_ptr<component::PhysicsComponent> physics,
                       std::unique_ptr<component::GraphicsComponent> graphics,
                       std::unique_ptr<component::InputComponent> inputs,
                       std::unique_ptr<component::CombatComponent> combat,
                       std::unique_ptr<component::CollisionComponent> collision,
                       NodeCategory category)
    : SceneNode(category),
      manager_(std::move(physics), std::move(graphics), std::move(inputs),
               std::move(combat), std::move(collision)) {}

sf::FloatRect GameObject::getBoundingRect() const {
  auto graphics = manager_.findComponent<component::GraphicsComponent>();
  return getWorldTransform().transformRect(graphics->getGlobalBounds());
}

void GameObject::drawCurrent(sf::RenderTarget& target,
                             const sf::RenderStates states) const {
  auto graphics = manager_.findComponent<component::GraphicsComponent>();
  graphics->draw(target, states);
}

void GameObject::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>&) {
  auto physics = manager_.findComponent<component::PhysicsComponent>();
  auto transforms = physics->getTransform(dt);
  Transformable::move(transforms);
};

}  // namespace ink
