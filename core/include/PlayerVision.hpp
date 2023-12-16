#pragma once

#include <functional>
#include <set>
#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

#include <Entities/Unit.hpp>
#include <SceneNode.hpp>
#include <Trace.hpp>

namespace ink {

class PlayerVision : public SceneNode {
 public:
  // TODO: use `const sf::Vector2f& player_pos` instead of `const Unit& player`
  // TODO: the `walls` variable always contains walls of the same room
  PlayerVision(const float trace_len, sf::FloatRect bounds, const Unit& player,
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

 private:
  inline static constexpr std::size_t kMaxTraceCount = 500;

  const Unit& player_;
  const float trace_len_;
  std::size_t next_trace_id_;
  const sf::FloatRect bounds_;  // the area covering all the obstacles
  // TODO: optimize all the below std::vector allocations
  // maybe using a kMaxTraceCount?
  const std::vector<sf::FloatRect>& walls_;

  std::vector<Trace> traces_;
  std::array<std::vector<sf::Vector2f>, kMaxTraceCount> intersection_points_;
};

}  // namespace ink
