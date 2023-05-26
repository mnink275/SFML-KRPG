#pragma once

#include <array>
#include <optional>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Door.h"
#include "RoomTypes.hpp"
#include "RoomConnectionTypes.hpp"

class RoomNode final : public SceneNode {
  using DoorPtr = std::unique_ptr<Door>;
 public:
  RoomNode(TextureHolder& texture_holder, sf::Texture& texture, sf::FloatRect bounds,
           Room room_type);

  void setPlayer(Ptr player);
  Ptr popPlayer() const;
  void createConnection(Room neighbor_room_type, RoomConnectionType direction);
  std::optional<Room> isDoorInteraction();
 private:
  enum Layer { Background, Player, LayerCount };

  Room room_type_;
  TextureHolder& texture_;
  sf::Vector2f room_bounds_;
  std::array<SceneNode*, LayerCount> room_layers_{nullptr};
  std::array<Door*, RoomConnectionCount>
      doors_storage_;  // top, right, bottom, left
  std::array<Room, RoomConnectionCount> connected_rooms_;
};
