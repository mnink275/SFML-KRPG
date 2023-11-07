#include <Entities/GameStaticObject.hpp>

namespace ink {

GameStaticObject::GameStaticObject(
    std::unique_ptr<component::GraphicsComponent> graphics)
    : graphics_impl_(std::move(graphics)) {}

sf::FloatRect GameStaticObject::getBoundingRect() const {
  return getWorldTransform().transformRect(graphics_impl_->getGlobalBounds());
}

void GameStaticObject::drawCurrent(sf::RenderTarget& target,
                                   const sf::RenderStates states) const {
  graphics_impl_->draw(target, states);
}

}  // namespace ink
