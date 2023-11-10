#include <Entities/GameObject.hpp>

#include <Components/Collision/CollisionComponent.hpp>
#include <Components/Graphics/GraphicsComponent.hpp>

namespace ink {

GameObject::GameObject(ComponentManager manager, NodeCategory category)
    : SceneNode(category), manager_(std::move(manager)) {}

void GameObject::handleCollisionWith(NodeCategory category,
                                     const SceneNode* node) {
  auto collision = manager_.findComponent<component::CollisionComponent>();
  collision->handleCollisionWith(this, category, node);
}

sf::FloatRect GameObject::getBoundingRect() const {
  auto graphics = manager_.findComponent<component::GraphicsComponent>();
  return getWorldTransform().transformRect(graphics->getGlobalBounds());
}

void GameObject::drawCurrent(sf::RenderTarget& target,
                             const sf::RenderStates states) const {
  auto graphics = manager_.findComponent<component::GraphicsComponent>();
  graphics->draw(target, states);
}

}  // namespace ink
