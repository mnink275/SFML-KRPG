#pragma once

#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

#include <Entities/Unit.hpp>
#include <SceneNode.hpp>
#include <Trace.hpp>

namespace ink {

class PlayerVision : public SceneNode {
 public:
  PlayerVision(const float trace_len, sf::FloatRect bounds);

  ~PlayerVision() = default;

  PlayerVision(const PlayerVision&) = delete;
  PlayerVision& operator=(const PlayerVision&) = delete;

  PlayerVision(PlayerVision&&) = delete;
  PlayerVision& operator=(PlayerVision&&) = delete;

  void handleCollisionWith(NodeCategory category,
                           const SceneNode* node) override;

  void updateTraces(sf::Vector2f player_pos);

  sf::FloatRect getBoundingRect() const override;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;
  void generateTraces();

 private:
  inline static constexpr std::size_t kTraceCount = 512;

  const float trace_len_;
  const sf::FloatRect bounds_;  // init it with world_bounds
  std::vector<Trace> traces_;
  std::array<std::vector<sf::Vector2f>, kTraceCount> intersection_points_;
};

}  // namespace ink
