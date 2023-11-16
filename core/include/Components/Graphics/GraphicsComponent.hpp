#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Components/Component.hpp>
#include <Entities/Types/EyesDirection.hpp>
#include <Entities/Types/ObjectState.hpp>

namespace ink::component {

struct FreezeFor final {
  FreezeFor() : FreezeFor(sf::Time::Zero) {}
  FreezeFor(sf::Time freezing_time) : freezing_time(freezing_time) {}

  const sf::Time freezing_time;
};

class GraphicsComponent : public Component {
 public:
  static constexpr auto kCategory = ComponentCategory::kGraphics;
  static constexpr auto kName = "Graphics";

 public:
  GraphicsComponent();
  GraphicsComponent(ObjectState object_state, EyesDirection eyes_direction);

  virtual void draw(sf::RenderTarget& target,
                    const sf::RenderStates states) const = 0;
  void update(sf::Time dt);

  virtual sf::FloatRect getGlobalBounds() const = 0;
  void setObjectState(ObjectState state,
                      FreezeFor freeze_for = FreezeFor{}) noexcept;
  ObjectState getObjectState() const noexcept;

 private:
  virtual void updateCurrent(sf::Time dt);

 public:
  EyesDirection eyes_direction;

 protected:
  sf::Time freezing_time_;
  bool state_changed_;

 private:
  ObjectState object_state_;
};

}  // namespace ink::component
