#pragma once

#include <memory>

#include <Entities/Unit.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/ConnectionTypes.hpp>
#include <Room/RoomNode.hpp>
#include <SceneNode.hpp>

namespace ink {

class RoomManager : public SceneNode {
 private:
  using Ptr = SceneNode::Ptr;

 public:
  RoomManager(SceneNode& scene_graph, sf::FloatRect world_bounds,
              TextureHolder& textures, NodeCategory category);

  ~RoomManager() = default;

  RoomManager(const RoomManager&) = delete;
  RoomManager& operator=(const RoomManager&) = delete;

  RoomManager(RoomManager&&) = delete;
  RoomManager& operator=(RoomManager&&) = delete;

  void attachUnit(std::unique_ptr<Unit> player);
  void createInitialRoom();
  void changeRoomTo(std::size_t next_room_id);
  void checkDoorInteraction();

 private:
  std::size_t createRandomRoom();
  std::size_t createRoom(std::size_t room_type_id);
  void createConnectionTo(ConnectionType connection);

 private:
  SceneNode& scene_graph_;
  // it needs to detach SceneNode(rooms) by it's address
  // and work with concrete object.
  std::vector<RoomNode*> room_nodes_;
  std::vector<Ptr> room_storage_;
  std::size_t curr_room_id_;
  std::size_t rooms_count_;
  sf::FloatRect world_bounds_;
  TextureHolder& textures_;
};

}  // namespace ink
