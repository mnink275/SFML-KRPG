#include <Room/Node.hpp>

#include <iostream>
#include <limits>

#include <SFML/Graphics/Rect.hpp>

#include <Components/SimpleGraphics.hpp>
#include <Entities/GameStaticObject.hpp>

namespace ink::room {

RoomNode::RoomNode(NodeCategory category, TextureHolder& texture_holder,
                   sf::Texture& texture, sf::FloatRect bounds, Type room_type,
                   std::size_t room_id)
    : SceneNode(category),
      room_type_(room_type),
      texture_(texture_holder),
      room_bounds_(bounds.width, bounds.height),
      room_id_(room_id) {
  // prepare the tiled background
  sf::IntRect background_texture_rect(bounds);
  texture.setRepeated(true);

  // add the background sprite to the scene
  auto background_sprite = std::make_unique<GameStaticObject>(
      std::make_unique<component::SimpleGraphics>(
          texture, background_texture_rect, false));
  background_sprite->setPosition({bounds.left, bounds.top});
  room_layers_[Background] = background_sprite.get();
  attachChild(std::move(background_sprite));

  doorsInitialize();
  buildWalls();
}

void RoomNode::doorsInitialize() {
  // TODO: simplify
  // door position constants
  float width = room_bounds_.x;
  float height = room_bounds_.y;
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
        std::make_unique<component::SimpleGraphics>(
            texture_.get(Textures::kDoor), sf::IntRect{door_sizes[dir_id]},
            false),
        direction_type, door_positions[dir_id],
        door_positions[static_cast<std::size_t>(transition_type)]);
    doors_storage_[dir_id] = door.get();
    doors_storage_[dir_id]->setPosition(door_positions[dir_id] +
                                        texture_shift[dir_id]);
    attachChild(std::move(door));
  }
}

void RoomNode::buildWalls() {
  texture_.get(Textures::kWall).setRepeated(true);
  static constexpr std::size_t kWallsCount = 4;

  auto walls_holder = std::make_unique<SceneNode>();
  float width = room_bounds_.x;
  float height = room_bounds_.y;
  float thickness = 10.0f;

  // `positions` contains left-top corner of the walls
  // walls "grow" from the left-top corner to the bottom-right
  const std::vector<sf::Vector2f> positions = {
      {0.0f, 0.0f},                                              // left
      {0.0f, 0.0f},                                              // top
      {width - thickness, 0.0f},                                 // right
      {0.0f, height - thickness}};                               // bottomt
  const std::vector<sf::Vector2f> sizes = {{thickness, height},  // left
                                           {width, thickness},   // top
                                           {thickness, height},  // right
                                           {width, thickness}};  // bottom

  for (std::size_t i = 0; i < kWallsCount; ++i) {
    auto wall = std::make_unique<GameStaticObject>(
        std::make_unique<component::SimpleGraphics>(
            texture_.get(Textures::kWall), sf::Vector2i{sizes[i]}, false),
        NodeCategory::kWall);
    wall->setPosition(positions[i]);
    walls_holder->attachChild(std::move(wall));
  }

  attachChild(std::move(walls_holder));
}

void RoomNode::createConnection(const std::size_t room_id,
                                const ConnectionType direction) {
  auto dir_id = static_cast<std::size_t>(direction);
  connected_rooms_[dir_id] = room_id;
  doors_storage_[dir_id]->activate();
}

std::optional<std::size_t> RoomNode::isDoorInteraction() {
  const sf::Vector2f& player_coords = room_layers_[Player]->getPosition();
  for (std::size_t i = 0; i < ConnectionsCount; ++i) {
    const auto& door = doors_storage_[i];
    if (door->isActive() && door->nearOf(player_coords)) {
      room_layers_[Player]->setPosition(door->getDoorOtherSidePosition());
      return std::optional{connected_rooms_[i]};
    }
  }

  return std::nullopt;
}

RoomNode::InteractionResult RoomNode::CheckDoorInteraction() {
  const sf::Vector2f& player_coords = room_layers_[Player]->getPosition();
  for (std::size_t i = 0; i < ConnectionsCount; ++i) {
    const auto& door = doors_storage_[i];
    if (door->nearOf(player_coords)) {
      if (door->isActive()) {
        std::cout << "Interactions with active door\n";
        room_layers_[Player]->setPosition(door->getDoorOtherSidePosition());
        return connected_rooms_[i];
      }
      std::cout << "Interactions with inactive door\n";
      return static_cast<ConnectionType>(i);
    }
  }
  std::cout << "No interactions with doors\n";
  return std::monostate{};
}

void RoomNode::setPlayer(Ptr player) {
  room_layers_[Player] = player.get();
  attachChild(std::move(player));
}

SceneNode::Ptr RoomNode::popPlayer() {
  return detachChild(*room_layers_[Player]);
}

}  // namespace ink::room
