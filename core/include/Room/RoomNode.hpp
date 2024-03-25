#pragma once

#include <array>
#include <variant>

#include <Commands/Category/NodeCategory.hpp>
#include <Resource/ResourceHolder.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/ConnectionTypes.hpp>
#include <Room/Door.hpp>
#include <SceneNode.hpp>

namespace ink {

class RoomNode final : public SceneNode {
 public:
  using InteractionResult =
      std::variant<std::monostate, std::size_t, ConnectionType>;

 public:
  // TODO: make TextureHolder& and Texture& const refs
  RoomNode(NodeCategory category, TextureHolder& texture_holder,
           sf::Texture& texture, sf::FloatRect bounds,
           std::vector<sf::FloatRect> walls, const float wall_thickness);

  void setPlayer(Ptr player);
  Ptr popPlayer();
  void createConnection(const std::size_t room_id,
                        const ConnectionType direction);
  InteractionResult CheckDoorInteraction();

 private:
  enum Layer { Background, Player, LayerCount };

  void doorsInit();
  void buildWalls(std::vector<sf::FloatRect>&& walls);

  TextureHolder& texture_;
  sf::Vector2f room_bounds_;
  std::array<SceneNode*, LayerCount> room_layers_{nullptr};
  // order: top = 0, right = 1, bottom = 2, left = 3
  std::array<Door*, ConnectionsCount> doors_storage_;
  std::array<std::size_t, ConnectionsCount> connected_rooms_;
  const float wall_thickness_;
};

}  // namespace ink
