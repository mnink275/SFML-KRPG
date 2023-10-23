#pragma once

#include <cmath>

#include <Resource/SpriteNode.hpp>
#include <Room/ConnectionTypes.hpp>
#include <Room/Types.hpp>

namespace ink::room {

class Door final : public SpriteNode {
 public:
  Door(sf::Texture& texture, sf::IntRect texture_rect, ConnectionType door_type,
       sf::Vector2f coords, sf::Vector2f transition_coords);

  bool nearOf(sf::Vector2f player_position) const;
  sf::Vector2f getDoorOtherSidePosition() const;
  void activate();
  void deactivate();
  bool isActive() const;

 private:
  bool is_active_{false};
  Type next_room_type_;
  ConnectionType door_type_;
  sf::Vector2f other_size_position_;
};

}  // namespace ink::room