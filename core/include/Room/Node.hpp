#pragma once

#include <array>
#include <optional>

#include <Resource/ResourceHolder.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/ConnectionTypes.hpp>
#include <Room/Door.hpp>
#include <Room/Types.hpp>
#include <SceneNode.hpp>

namespace ink::room {

class RoomNode final : public SceneNode {
  using DoorPtr = std::unique_ptr<Door>;

 public:
  RoomNode(TextureHolder& texture_holder, sf::Texture& texture,
           sf::FloatRect bounds, Type room_type);

  void setPlayer(Ptr player);
  Ptr popPlayer();
  void createConnection(Type neighbor_room_type,
                        room::ConnectionType direction);
  std::optional<Type> isDoorInteraction();

 private:
  enum Layer { Background, Player, LayerCount };

  void doorsInitialize();

  Type room_type_;
  TextureHolder& texture_;
  sf::Vector2f room_bounds_;
  std::array<SceneNode*, LayerCount> room_layers_{nullptr};
  // order: top = 0, right = 1, bottom = 2, left = 3
  std::array<Door*, ConnectionsCount> doors_storage_;
  std::array<Type, ConnectionsCount> connected_rooms_;
};

}  // namespace ink::room
