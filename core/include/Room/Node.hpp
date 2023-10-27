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
  // TODO: make TextureHolder& and Texture& const refs
  RoomNode(TextureHolder& texture_holder, sf::Texture& texture,
           sf::FloatRect bounds, Type room_type, std::size_t room_id);

  void setPlayer(Ptr player);
  Ptr popPlayer();
  void createConnection(const std::size_t room_id,
                        const room::ConnectionType direction);
  std::optional<std::size_t> isDoorInteraction();

 private:
  enum Layer { Background, Player, LayerCount };

  void doorsInitialize();

  Type room_type_;
  TextureHolder& texture_;
  sf::Vector2f room_bounds_;
  std::array<SceneNode*, LayerCount> room_layers_{nullptr};
  // order: top = 0, right = 1, bottom = 2, left = 3
  std::array<Door*, ConnectionsCount> doors_storage_;
  std::array<std::size_t, ConnectionsCount> connected_rooms_;
  std::size_t room_id_;
};

}  // namespace ink::room
