#pragma once

#include <memory>

#include <Entities/Player.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/Node.hpp>
#include <Room/Types.hpp>
#include <SceneNode.hpp>

namespace ink::room {

class RoomManager final {
 private:
  using Ptr = SceneNode::Ptr;

 public:
  RoomManager(SceneNode& scene_graph, room::Type init_room,
              sf::FloatRect world_bounds, TextureHolder& textures)
      : scene_graph_(scene_graph),
        current_room_type_(init_room),
        world_bounds_(world_bounds),
        textures_(textures) {}

  void attachPlayer(std::unique_ptr<Player> player) {
    // connect entities to the Graph
    player->setParentRoom(room_nodes_[current_room_type_]);
    room_nodes_[current_room_type_]->setPlayer(std::move(player));
    scene_graph_.attachChild(std::move(room_storage_[current_room_type_]));
  }

  void createRooms() {
    // rooms factory
    for (int i = 0; i < room::RoomCount; ++i) {
      const auto texture_type = static_cast<Textures::ID>(i);
      const auto room_type = static_cast<room::Type>(i);

      auto room = std::make_unique<room::RoomNode>(
          textures_, textures_.get(texture_type), world_bounds_, room_type);
      room_nodes_[room_type] = room.get();
      room_storage_[room_type] = std::move(room);
    }
  }

  void changeRoom(room::Type prev_type, room::Type new_type) {
    // re-set the player
    auto player = room_nodes_[prev_type]->popPlayer();
    room_nodes_[new_type]->setPlayer(std::move(player));
    // detach a previous room
    auto prev_room = scene_graph_.detachChild(*room_nodes_[prev_type]);
    room_storage_[prev_type] = std::move(prev_room);
    // attach a new room
    auto new_room = std::move(room_storage_[new_type]);
    scene_graph_.attachChild(std::move(new_room));

    current_room_type_ = new_type;
  }
  void createRoomConnections() const {
    room_nodes_[room::DesertRoom]->createConnection(room::StoneRoom,
                                                    room::ConnectionType::Top);
    room_nodes_[room::StoneRoom]->createConnection(
        room::DesertRoom, room::ConnectionType::Bottom);

    room_nodes_[room::DesertRoom]->createConnection(
        room::LavaRoom, room::ConnectionType::Right);
    room_nodes_[room::LavaRoom]->createConnection(room::DesertRoom,
                                                  room::ConnectionType::Left);
  }

  void checkDoorInteraction() {
    room::RoomNode* curr_room = room_nodes_[current_room_type_];
    if (auto next_room_type = curr_room->isDoorInteraction()) {
      changeRoom(current_room_type_, next_room_type.value());
    }
  }

 private:
  SceneNode& scene_graph_;
  // it needs to detach SceneNode(rooms) by it's address
  // and work with concrete object.
  std::array<room::RoomNode*, room::RoomCount> room_nodes_{};
  std::array<Ptr, room::RoomCount> room_storage_{};
  room::Type current_room_type_;
  sf::FloatRect world_bounds_;
  TextureHolder& textures_;
};

}  // namespace ink::room
