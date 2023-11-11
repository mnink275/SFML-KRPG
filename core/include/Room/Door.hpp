#pragma once

#include <Components/ComponentManager.hpp>
#include <Entities/GameObject.hpp>
#include <Room/ConnectionTypes.hpp>

namespace ink {

class Door final : public GameObject {
 public:
  Door(ComponentManager manager, ConnectionType door_type, sf::Vector2f coords,
       sf::Vector2f transition_coords, NodeCategory category);

  bool nearOf(sf::Vector2f player_position) const;
  sf::Vector2f getDoorOtherSidePosition() const;
  void activate();
  void deactivate();
  bool isActive() const;

 private:
  bool is_active_{false};
  ConnectionType door_type_;
  sf::Vector2f other_side_position_;
};

}  // namespace ink
