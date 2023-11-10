#pragma once

#include <Entities/GameStaticObject.hpp>
#include <Room/ConnectionTypes.hpp>

namespace ink {

class Door final : public GameStaticObject {
 public:
  using GameStaticObject::GameStaticObject;
  Door(std::unique_ptr<component::GraphicsComponent> graphics,
       ConnectionType door_type, sf::Vector2f coords,
       sf::Vector2f transition_coords);

  bool nearOf(sf::Vector2f player_position) const;
  sf::Vector2f getDoorOtherSidePosition() const;
  void activate();
  void deactivate();
  bool isActive() const;

 private:
  bool is_active_{false};
  ConnectionType door_type_;
  sf::Vector2f other_size_position_;
};

}  // namespace ink