#include <Entities/GameStaticObject.hpp>

namespace ink {

GameStaticObject::GameStaticObject(
    std::unique_ptr<component::GraphicsComponent> graphics,
    NodeCategory category)
    : SceneNode(category), graphics_impl_(std::move(graphics)) {}

sf::FloatRect GameStaticObject::getBoundingRect() const {
  assert(graphics_impl_);
  return getWorldTransform().transformRect(graphics_impl_->getGlobalBounds());
}

void GameStaticObject::drawCurrent(sf::RenderTarget& target,
                                   const sf::RenderStates states) const {
  assert(graphics_impl_);
  graphics_impl_->draw(target, states);
}

}  // namespace ink
