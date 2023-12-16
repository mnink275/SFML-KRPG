#pragma once

#include <functional>
#include <set>
#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

#include <Entities/Unit.hpp>
#include <Raycasting/Trace.hpp>
#include <SceneNode.hpp>

namespace ink {

class PlayerVision : public SceneNode {
 public:
  // TODO: the `walls` variable always contains walls of the same room
  PlayerVision(const float trace_len, sf::FloatRect bounds,
               const sf::Vector2f& player_pos,
               const std::vector<sf::FloatRect>& walls);

  ~PlayerVision() = default;

  PlayerVision(const PlayerVision&) = delete;
  PlayerVision& operator=(const PlayerVision&) = delete;

  PlayerVision(PlayerVision&&) = delete;
  PlayerVision& operator=(PlayerVision&&) = delete;

  void handleCollisionWith(NodeCategory category,
                           const SceneNode* node) override;

  sf::FloatRect getBoundingRect() const override;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;
  void generateTracesToWall(std::array<sf::Vector2f, 4> rect_points);
  void generateTraces();
  void findNearestIntersectionPoints();

 private:
  inline static constexpr std::size_t kMaxTraceCount = 500;

  const sf::Vector2f& player_pos_;
  const float trace_len_;
  std::size_t next_trace_id_;
  const sf::FloatRect bounds_;  // the area covering all the obstacles
  const std::vector<sf::FloatRect>& walls_;

  std::vector<Trace> traces_;
  // TODO: the cache-friendly optimizaiton possible if necessary
  std::array<std::vector<sf::Vector2f>, kMaxTraceCount> intersection_points_;
};

}  // namespace ink
