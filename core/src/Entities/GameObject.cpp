#include <Entities/GameObject.hpp>

namespace ink {

GameObject::GameObject(ComponentManager manager, NodeCategory category)
    : SceneNode(category), manager_(std::move(manager)) {}

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
