#include <Wall.hpp>

#include <fmt/format.h>

namespace ink {

Wall::Wall(const sf::Vector2f position, const sf::Vector2f size)
    : shape_(size), shift_() {
  shape_.setPosition(position);
  shape_.setFillColor(sf::Color::Green);
}

void Wall::handleInput(const sf::Event::MouseMoveEvent event) {
  fmt::println("Mouse moved: ({}, {})", event.x, event.y);
  const auto x = event.x - shift_.x;
  const auto y = event.y - shift_.y;
  shape_.setPosition({x, y});
}

sf::FloatRect Wall::getBoundingRect() const noexcept {
  return shape_.getGlobalBounds();
}

void Wall::draw(sf::RenderTarget& target) const { target.draw(shape_); }

void Wall::setShift(sf::Vector2f mouse_position) {
  shift_ = mouse_position - shape_.getPosition();
}

}  // namespace ink
