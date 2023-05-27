#pragma once

#include <cmath>

#include "RoomConnectionTypes.hpp"
#include "RoomTypes.hpp"
#include "SpriteNode.hpp"

class Door final : public SpriteNode {
 public:
  Door(sf::Texture& texture, sf::IntRect texture_rect,
       RoomConnectionType door_type, sf::Vector2f coords,
       sf::Vector2f transition_coords);

  bool nearOf(sf::Vector2f player_position) const;
  sf::Vector2f getDoorOtherSidePosition() const;
  void activate();
  void deactivate();
  bool isActive() const;

 private:
  bool is_active_{false};
  Room next_room_type_;
  RoomConnectionType door_type_;
  sf::Vector2f other_size_position_;
};