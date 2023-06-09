#pragma once

#include <array>
#include <optional>

#include "Door.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "RoomConnectionTypes.hpp"
#include "RoomTypes.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"

class RoomNode final : public SceneNode {
  using DoorPtr = std::unique_ptr<Door>;

 public:
  RoomNode(TextureHolder& texture_holder, sf::Texture& texture,
           sf::FloatRect bounds, Room room_type);

  void setPlayer(Ptr player);
  Ptr popPlayer() const;
  void createConnection(Room neighbor_room_type, RoomConnectionType direction);
  std::optional<Room> isDoorInteraction();

 private:
  enum Layer { Background, Player, LayerCount };

  void doorsInitialize();

  Room room_type_;
  TextureHolder& texture_;
  sf::Vector2f room_bounds_;
  std::array<SceneNode*, LayerCount> room_layers_{nullptr};
  // order: top = 0, right = 1, bottom = 2, left = 3
  std::array<Door*, RoomConnectionCount> doors_storage_;
  std::array<Room, RoomConnectionCount> connected_rooms_;
};