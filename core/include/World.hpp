#pragma once

#include <array>
#include <iostream>

#include <Room/RoomNode.hpp>
#include <Room/RoomTypes.hpp>
#include <Entities/Player.hpp>
#include <Resource/ResourceHolder.hpp>
#include <Resource/ResourceIdentifiers.hpp>

namespace ink {

class World final {
  using Ptr = SceneNode::Ptr;

 public:
  explicit World(sf::RenderWindow& window);

  World(const World&) = delete;
  World& operator=(const World&) = delete;

  World(World&&) = delete;
  World& operator=(World&&) = delete;

  void update(sf::Time dt);
  void draw() const;
  void handlePlayerInput(sf::Keyboard::Key key, bool is_pressed);

 private:
  // initial
  void loadTextures();
  void buildScene();
  // update
  void boundChecking() const;
  void checkDoorInteraction();
  // rooms
  void createRooms();
  void changeRoom(Room prev_type, Room new_type);
  void createRoomConnections() const;

  sf::RenderWindow& window_;
  sf::View world_view_;
  TextureHolder textures_;
  SceneNode scene_graph_;
  // it needs to detach SceneNode(rooms) by it's address
  // and work with concrete object.
  std::array<RoomNode*, RoomCount> room_nodes_{};
  std::array<Ptr, RoomCount> room_storage_{};
  sf::FloatRect world_bounds_;
  sf::Vector2f spawn_position_;
  bool interact_with_{false};

  Player* player_;
  Room current_room_type_;
};

}  // namespace ink
