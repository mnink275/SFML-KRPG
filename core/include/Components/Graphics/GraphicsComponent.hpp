#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Components/Component.hpp>
#include <Entities/EyesDirection.hpp>

namespace ink::component {

class GraphicsComponent : public Component {
 public:
  static constexpr auto kCategory = ComponentCategory::kGraphics;
  static constexpr auto kName = "Graphics";

 public:
  GraphicsComponent(EyesDirection eyes_direction = EyesDirection::kNone);

  virtual void draw(sf::RenderTarget& target,
                    const sf::RenderStates states) const = 0;
  virtual void update(sf::Time dt);

  virtual sf::FloatRect getGlobalBounds() const = 0;

 public:
  EyesDirection eyes_direction;

 protected:
  void doSpriteCentering(sf::Sprite& sprite);
};

}  // namespace ink::component
