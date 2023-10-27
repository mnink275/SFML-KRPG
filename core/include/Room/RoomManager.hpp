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
  RoomManager(SceneNode& scene_graph, sf::FloatRect world_bounds,
              TextureHolder& textures)
      : scene_graph_(scene_graph),
        curr_room_id_(0),
        rooms_count_(0),
        world_bounds_(world_bounds),
        textures_(textures) {}

  void attachPlayer(std::unique_ptr<Player> player) {
    // connect entities to the Graph
    player->setParentRoom(room_nodes_[curr_room_id_]);
    room_nodes_[curr_room_id_]->setPlayer(std::move(player));
    scene_graph_.attachChild(std::move(room_storage_[curr_room_id_]));
  }

  void createRooms() {
    // rooms factory
    for (int i = 0; i < room::RoomCount; ++i) {
      const auto texture_type = static_cast<Textures>(i);
      const auto room_type = static_cast<room::Type>(i);

      auto room_id = rooms_count_++;
      auto room = std::make_unique<room::RoomNode>(
          textures_, textures_.get(texture_type), world_bounds_, room_type,
          room_id);
      room_nodes_.push_back(room.get());
      room_storage_.push_back(std::move(room));
    }
  }

  void changeRoomTo(std::size_t next_room_id) {
    // re-set the player
    auto player = room_nodes_[curr_room_id_]->popPlayer();
    room_nodes_[next_room_id]->setPlayer(std::move(player));
    // detach a previous room
    auto prev_room = scene_graph_.detachChild(*room_nodes_[curr_room_id_]);
    room_storage_[curr_room_id_] = std::move(prev_room);
    // attach a new room
    auto new_room = std::move(room_storage_[next_room_id]);
    scene_graph_.attachChild(std::move(new_room));

    curr_room_id_ = next_room_id;
  }
  void createRoomConnections() const {
    room_nodes_[0]->createConnection(1, room::ConnectionType::Top);
    room_nodes_[1]->createConnection(0, room::ConnectionType::Bottom);

    room_nodes_[0]->createConnection(2, room::ConnectionType::Right);
    room_nodes_[2]->createConnection(0, room::ConnectionType::Left);
  }

  void checkDoorInteraction() {
    room::RoomNode* curr_room = room_nodes_[curr_room_id_];
    if (auto next_room_type = curr_room->isDoorInteraction()) {
      changeRoomTo(next_room_type.value());
    }
  }

 private:
  SceneNode& scene_graph_;
  // it needs to detach SceneNode(rooms) by it's address
  // and work with concrete object.
  std::vector<room::RoomNode*> room_nodes_;
  std::vector<Ptr> room_storage_;
  std::size_t curr_room_id_;
  std::size_t rooms_count_;
  sf::FloatRect world_bounds_;
  TextureHolder& textures_;
};

}  // namespace ink::room
