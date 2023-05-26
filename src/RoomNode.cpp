#include "RoomNode.hpp"

RoomNode::RoomNode(TextureHolder& texture_holder, sf::Texture& texture,
                   sf::FloatRect bounds, Room room_type)
    : room_type_(room_type),
      texture_(texture_holder),
      room_bounds_(bounds.height, bounds.width) {
  // prepare the tiled background
  sf::IntRect background_texture_rect(bounds);
  texture.setRepeated(true);

  // add the background sprite to the scene
  auto background_sprite =
      std::make_unique<SpriteNode>(texture, background_texture_rect);
  background_sprite->setPosition(bounds.left, bounds.top);
  room_layers_[Background] = background_sprite.get();
  attachChild(std::move(background_sprite));

  // door initialize
  float height = room_bounds_.x;
  float width = room_bounds_.y;
  sf::IntRect door_texture_rect(0, 0, 50, 20);
  // TODO: create a for-loop
  auto door1 =
      std::make_unique<Door>(texture_.get(Textures::Door), door_texture_rect,
                             Top, width / 2, 0, width / 2, height);
  doors_storage_[0] = door1.get();
  doors_storage_[0]->setPosition(width / 2, 0);
  attachChild(std::move(door1));

  auto door2 =
      std::make_unique<Door>(texture_.get(Textures::Door), door_texture_rect,
                             Right, 0, height / 2, width, height / 2);
  doors_storage_[1] = door2.get();
  doors_storage_[1]->setPosition(0, height / 2);
  attachChild(std::move(door2));

  auto door3 =
      std::make_unique<Door>(texture_.get(Textures::Door), door_texture_rect,
                             Bottom, width / 2, height, width / 2, 0);
  doors_storage_[2] = door3.get();
  doors_storage_[2]->setPosition(width / 2, height);
  attachChild(std::move(door3));

  auto door4 =
      std::make_unique<Door>(texture_.get(Textures::Door), door_texture_rect,
                             Left, width, height / 2, 0, height / 2);
  doors_storage_[3] = door4.get();
  doors_storage_[3]->setPosition(width, height / 2);
  attachChild(std::move(door4));
}

void RoomNode::createConnection(Room neighbor_room_type,
                                RoomConnectionType direction) {
  connected_rooms_[direction] = neighbor_room_type;
  doors_storage_[direction]->activate();
}

std::optional<Room> RoomNode::isDoorInteraction() {
  const sf::Vector2f& player_coords = room_layers_[Player]->getPosition();

  for (int i = 0; i < RoomConnectionCount; ++i) {
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