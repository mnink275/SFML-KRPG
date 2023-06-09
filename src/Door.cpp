#include "Door.hpp"

Door::Door(sf::Texture& texture, sf::IntRect texture_rect,
           RoomConnectionType door_type, sf::Vector2f coords,
           sf::Vector2f transition_coords)
    : SpriteNode(texture, texture_rect),
      door_type_(door_type),
      other_size_position_(transition_coords) {
  setPosition(coords);
}

bool Door::nearOf(sf::Vector2f player_position) const {
  const auto& coords = getPosition();
  const float shift_x = std::abs(player_position.x - coords.x);
  const float shift_y = std::abs(player_position.y - coords.y);
  const float radius = std::sqrt(shift_x * shift_x + shift_y * shift_y);

  return radius < 100.0f;
}

sf::Vector2f Door::getDoorOtherSidePosition() const {
  return other_size_position_;
};

void Door::activate() { is_active_ = true; }

void Door::deactivate() { is_active_ = false; }

bool Door::isActive() const { return is_active_; }