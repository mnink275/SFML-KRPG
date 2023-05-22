#pragma once

#include <array>
#include <iostream>

#include "Aircraft.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "RoomNode.hpp"

class World final : private sf::NonCopyable {
  using Ptr = SceneNode::Ptr;

 public:
  explicit World(sf::RenderWindow& window);
  void update(sf::Time dt);
  void draw() const;
  void handlePlayerInput(sf::Keyboard::Key key, bool is_pressed);

 private:
  enum Rooms { DesertRoom, LavaRoom, RoomCount };

  void loadTextures();
  void buildScene();
  void changeRoom(Rooms prev_type, Rooms new_type);

  sf::RenderWindow& window_;
  sf::View world_view_;
  TextureHolder textures_;
  SceneNode scene_graph_;
  std::array<RoomNode*, RoomCount> room_nodes_{nullptr};
  std::array<Ptr, RoomCount> room_storage_;
  sf::FloatRect world_bounds_;
  sf::Vector2f spawn_position_;
  bool interact_with_{false};

  Aircraft* player_aircraft_;
};