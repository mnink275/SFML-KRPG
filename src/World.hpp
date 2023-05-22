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
  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

 private:
  enum Rooms { DesertRoom, LavaRoom, RoomCount };

  void loadTextures();
  void buildScene();
  void changeRoom(Rooms prev_type, Rooms new_type);

  sf::RenderWindow& mWindow;
  sf::View mWorldView;
  TextureHolder mTextures;
  SceneNode mSceneGraph;
  std::array<RoomNode*, RoomCount> mRoomNodes;
  std::array<Ptr, RoomCount> room_storage;
  sf::FloatRect mWorldBounds;
  sf::Vector2f mSpawnPosition;
  bool interact_with{false};

  Aircraft* mPlayerAircraft;
};