#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Components/Component.hpp>
#include <Entities/Types/EyesDirection.hpp>
#include <Entities/Types/ObjectState.hpp>

namespace ink::component {

class GraphicsComponent : public Component {
 public:
  static constexpr auto kCategory = ComponentCategory::kGraphics;
  static constexpr auto kName = "Graphics";

 public:
  GraphicsComponent();
  GraphicsComponent(ObjectState object_state, EyesDirection eyes_direction);

  virtual void draw(sf::RenderTarget& target,
                    const sf::RenderStates states) const = 0;
  virtual void update(sf::Time dt);

  virtual sf::FloatRect getGlobalBounds() const = 0;

 public:
  ObjectState object_state;
  EyesDirection eyes_direction;
};

}  // namespace ink::component
