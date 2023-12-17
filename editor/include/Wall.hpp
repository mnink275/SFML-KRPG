#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace ink {

class Wall final {
 public:
  Wall(const sf::Vector2f position, const sf::Vector2f size);

  Wall(const Wall&) = delete;
  Wall& operator=(const Wall&) = delete;

  Wall(Wall&&) = default;
  Wall& operator=(Wall&&) = default;

  ~Wall() = default;

  void handleInput(const sf::Event::MouseMoveEvent event);
  sf::FloatRect getBoundingRect() const noexcept;
  void draw(sf::RenderTarget& target) const;
  void setShift(sf::Vector2f mouse_position);

 private:
  sf::RectangleShape shape_;
  sf::Vector2f shift_;
};

}  // namespace ink
