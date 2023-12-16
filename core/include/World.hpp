#pragma once

#include <array>

#include <Commands/CommandQueue.hpp>
#include <Entities/Unit.hpp>
#include <Raycasting/PlayerVision.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/RoomManager.hpp>

namespace ink {

class World final {
  using Ptr = SceneNode::Ptr;

 public:
  explicit World(sf::RenderWindow& window, TextureHolder& textures,
                 FontHolder& fonts);

  ~World() = default;

  World(const World&) = delete;
  World& operator=(const World&) = delete;

  World(World&&) = delete;
  World& operator=(World&&) = delete;

  void update(sf::Time dt);
  void draw() const;
  void handlePlayerInput(sf::Keyboard::Key key, bool is_pressed);
  void handleCollisions();

 private:
  void buildScene();
  // update
  void checkDoorInteraction();
  bool matchesCategories(SceneNode::NodePair& colliders,
                         NodeCategory requested1,
                         NodeCategory requested2) const noexcept;

  sf::RenderWindow& window_;
  sf::View world_view_;
  TextureHolder& textures_;
  FontHolder& fonts_;
  SceneNode scene_graph_;

  sf::FloatRect world_bounds_;
  sf::Vector2f spawn_position_;

  Unit* player_;
  PlayerVision* player_vision_;

  RoomManager* room_manager_;
  CommandQueue<NodeCommand> command_queue_;
};

}  // namespace ink
