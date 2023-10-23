#include <Room/Node.hpp>

#include "SFML/Graphics/Rect.hpp"

#include <Resource/SpriteNode.hpp>

namespace ink::room {

RoomNode::RoomNode(TextureHolder& texture_holder, sf::Texture& texture,
                   sf::FloatRect bounds, Type room_type)
    : room_type_(room_type),
      texture_(texture_holder),
      room_bounds_(bounds.height, bounds.width) {
  // prepare the tiled background
  sf::IntRect background_texture_rect(bounds);
  texture.setRepeated(true);

  // add the background sprite to the scene
  auto background_sprite =
      std::make_unique<SpriteNode>(texture, background_texture_rect, false);
  background_sprite->setPosition({bounds.left, bounds.top});
  room_layers_[Background] = background_sprite.get();
  attachChild(std::move(background_sprite));

  doorsInitialize();
}

void RoomNode::doorsInitialize() {
  // door position constants
  float height = room_bounds_.x;
  float width = room_bounds_.y;
  const float door_width = 100;
  const float door_height = 20;
  const sf::FloatRect horizontal_door({0, 0}, {door_width, door_height});
  const sf::FloatRect vertical_door({0, 0}, {door_height, door_width});
  const std::vector door_sizes = {horizontal_door,  // Top
                                  vertical_door,    // Right
                                  horizontal_door,  // Bottom
                                  vertical_door};   // Left
  const std::vector<sf::Vector2f> door_positions = {
      // left-top corner of the door position
      {width / 2, 0.0f},    // Top
      {width, height / 2},  // Right
      {width / 2, height},  // Bottom
      {0.0f, height / 2}};  // Left
  const std::vector<sf::Vector2f> texture_shift = {
      // shift the texture to the correct position
      {-door_width / 2, 0.0f},          // Top
      {-door_height, -door_width / 2},  // Right
      {-door_width / 2, -door_height},  // Bottom
      {0.0f, -door_width / 2}};         // Left
  static constexpr std::array transition = {
      ConnectionType::Bottom, ConnectionType::Left, ConnectionType::Top,
      ConnectionType::Right};
  // doors factory
  for (std::size_t dir_id = 0; dir_id < ConnectionsCount; ++dir_id) {
    const auto direction_type = static_cast<ConnectionType>(dir_id);
    const auto transition_type = transition[dir_id];

    auto door = std::make_unique<Door>(
        texture_.get(Textures::Door), sf::IntRect{door_sizes[dir_id]},
        direction_type, door_positions[dir_id],
        door_positions[static_cast<std::size_t>(transition_type)]);
    doors_storage_[dir_id] = door.get();
    doors_storage_[dir_id]->setPosition(door_positions[dir_id] +
                                        texture_shift[dir_id]);
    attachChild(std::move(door));
  }
}

void RoomNode::createConnection(const Type neighbor_room_type,
                                const ConnectionType direction) {
  auto dir_id = static_cast<std::size_t>(direction);
  connected_rooms_[dir_id] = neighbor_room_type;
  doors_storage_[dir_id]->activate();
}

std::optional<Type> RoomNode::isDoorInteraction() {
  const sf::Vector2f& player_coords = room_layers_[Player]->getPosition();
  for (int i = 0; i < ConnectionsCount; ++i) {
    const auto& door = doors_storage_[i];
    if (door->isActive() && door->nearOf(player_coords)) {
      room_layers_[Player]->setPosition(door->getDoorOtherSidePosition());
      return std::optional{connected_rooms_[i]};
    }
  }

  return std::nullopt;
}

void RoomNode::setPlayer(Ptr player) {
  room_layers_[Player] = player.get();
  room_layers_[Background]->attachChild(std::move(player));
}

SceneNode::Ptr RoomNode::popPlayer() const {
  return room_layers_[Background]->detachChild(*room_layers_[Player]);
}

}  // namespace ink::room
