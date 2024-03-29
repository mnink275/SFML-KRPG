#include <Room/Door.hpp>

#include <cmath>
#include <memory>

namespace ink {

Door::Door(ComponentManager manager, sf::Vector2f coords,
           sf::Vector2f transition_coords, NodeCategory category)
    : GameObject(std::move(manager), category),
      other_side_position_(transition_coords) {
  setPosition(coords);
}

bool Door::nearOf(sf::Vector2f player_position) const {
  const auto& coords = getPosition();
  const float shift_x = std::abs(player_position.x - coords.x);
  const float shift_y = std::abs(player_position.y - coords.y);
  const float radius = std::sqrt(shift_x * shift_x + shift_y * shift_y);

  static constexpr auto kInteractionDistance = 100.0f;
  return radius < kInteractionDistance;
}

sf::Vector2f Door::getDoorOtherSidePosition() const {
  return other_side_position_;
};

void Door::activate() { is_active_ = true; }

void Door::deactivate() { is_active_ = false; }

bool Door::isActive() const { return is_active_; }

}  // namespace ink
