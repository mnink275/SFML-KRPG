#include <PlayerVision.hpp>

#include <fmt/format.h>
#include <SFML/Graphics/CircleShape.hpp>

#include <array>

namespace ink {

PlayerVision::PlayerVision(const float trace_len, sf::FloatRect bounds)
    : SceneNode(NodeCategory::kVision),
      trace_len_(trace_len),
      bounds_(bounds),
      traces_(),
      intersection_points_() {
  generateTraces();
}

void PlayerVision::handleCollisionWith(NodeCategory category,
                                       const SceneNode* node) {
  ASSERT(category == NodeCategory::kWall);
  const auto* wall = static_cast<const GameObject*>(node);
  auto rect = wall->getBoundingRect();

  const auto rect_points = std::array<sf::Vector2f, 4>{
      sf::Vector2f{rect.left, rect.top},
      sf::Vector2f{rect.left + rect.width, rect.top},
      sf::Vector2f{rect.left + rect.width, rect.top + rect.height},
      sf::Vector2f{rect.left, rect.top + rect.height}};
  const auto rect_points_size = rect_points.size();

  static constexpr auto distance = [](sf::Vector2f p1, sf::Vector2f p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
  };
  for (auto&& trace : traces_) {
    for (std::size_t i = 0; i < rect_points_size; ++i) {
      auto side = sf::VertexArray(sf::PrimitiveType::Lines, 2);
      side[0].position = rect_points[i];
      side[1].position = rect_points[(i + 1) % rect_points_size];

      const auto point = trace.findIntersection(Trace{side});
      if (!point.has_value()) continue;

      intersection_points_[trace.getId()].push_back(*point);
    }
  }
  for (auto&& trace : traces_) {
    auto& inter_points = intersection_points_[trace.getId()];
    if (inter_points.empty()) continue;

    auto nearest_point = inter_points[0];
    for (auto&& point : inter_points) {
      if (distance(trace.line[0].position, point) <
          distance(trace.line[0].position, nearest_point)) {
        nearest_point = point;
      }
    }

    trace.intersection_point = nearest_point;
  }
}

void PlayerVision::updateTraces(sf::Vector2f player_pos) {
  for (auto&& trace : traces_) {
    trace.intersection_point.reset();
    intersection_points_[trace.getId()].clear();

    trace.shiftTo(player_pos);
  }
}

sf::FloatRect PlayerVision::getBoundingRect() const { return bounds_; }

void PlayerVision::drawCurrent(sf::RenderTarget& target,
                               sf::RenderStates /*states*/) const {
  // drawing the traces and intersection points
  #if 0
  for (auto&& trace : traces_) {
    target.draw(trace.line);
  }
  for (auto&& trace : traces_) {
    sf::CircleShape circle{2.0f};
    circle.setFillColor(sf::Color::Red);
    ASSERT(trace.intersection_point.has_value());
    circle.setPosition(*trace.intersection_point);
    target.draw(circle);
  }
  #endif

  // drawing the unseen zone
  sf::ConvexShape convex;
  convex.setPointCount(4);
  for (std::size_t i = 0; i < traces_.size(); ++i) {
    const auto& left_trace = traces_[i];
    const auto& right_trace = traces_[(i + 1) % traces_.size()];
    
    convex.setPoint(0, *right_trace.intersection_point);
    convex.setPoint(1, *left_trace.intersection_point);
    convex.setPoint(2, left_trace.line[1].position);
    convex.setPoint(3, right_trace.line[1].position);
    convex.setFillColor(sf::Color::Black);

    target.draw(convex);
  }
}

void PlayerVision::updateCurrent(sf::Time /*dt*/,
                                 CommandQueue<NodeCommand>& /*commands*/) {}

void PlayerVision::generateTraces() {
  sf::VertexArray line(sf::PrimitiveType::Lines, 2);
  const auto init_pos = sf::Vector2f{0.f, 0.f};
  line[0].position = init_pos;
  line[1].position = init_pos + sf::Vector2f{0.0f, trace_len_};

  const auto angle_step = sf::degrees(360.0f / kTraceCount);

  std::vector<Trace> traces;
  traces.reserve(kTraceCount);
  for (std::size_t i = 0; i < kTraceCount; ++i) {
    traces.emplace_back(line, i);

    // turn the `line` clockwise
    line[1].position -= line[0].position;
    line[1].position = line[1].position.rotatedBy(angle_step);
    line[1].position += line[0].position;
  }

  traces_ = std::move(traces);
}

}  // namespace ink
