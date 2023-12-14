#pragma once

#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

#include <Entities/Unit.hpp>
#include <SceneNode.hpp>

namespace ink {

class PlayerVision : public SceneNode {
 public:
  struct Trace {
    enum class TraceType {
      kVertical = 0,
      kHorizontal = 1,
      kCommon = 2,
    };

    explicit Trace(sf::VertexArray line);

    ~Trace() = default;

    Trace(const Trace&) = default;
    Trace& operator=(const Trace&) = delete;

    Trace(Trace&&) = default;
    Trace& operator=(Trace&&) = delete;

    std::optional<sf::Vector2f> findIntersection(
        const Trace& other_trace) const;

    static constexpr auto kEps = 1.f;

    const TraceType trace_type;
    const float slope;
    float height;
    sf::VertexArray line;
    std::optional<sf::Vector2f> intersection_point;
    std::vector<sf::Vector2f> intersection_points;

   private:
    bool belongsToLine(sf::Vector2f point,
                       const sf::VertexArray& line) const noexcept;

    static std::optional<sf::Vector2f> findIntersectionImpl(const Trace& left,
                                                            const Trace& right);
  };

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
  const float trace_len_;
  const sf::FloatRect bounds_;  // init it with world_bounds
  std::vector<Trace> traces_;
  const std::size_t trace_count_;
};

}  // namespace ink
