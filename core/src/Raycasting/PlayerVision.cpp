#include <Raycasting/PlayerVision.hpp>

#include <array>

#include <fmt/format.h>
#include <SFML/Graphics/CircleShape.hpp>

namespace ink {

PlayerVision::PlayerVision(const float trace_len, sf::FloatRect bounds,
                           const sf::Vector2f& player_pos,
                           const std::vector<sf::FloatRect>& walls)
    : SceneNode(NodeCategory::kVision),
      player_pos_(player_pos),
      trace_len_(trace_len),
      next_trace_id_(0),
      bounds_(bounds),
      walls_(walls),
      traces_(),
      intersection_points_() {}

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

  // intersection with obstacles
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

  findNearestIntersectionPoints();
}

sf::FloatRect PlayerVision::getBoundingRect() const { return bounds_; }

void PlayerVision::drawCurrent(sf::RenderTarget& target,
                               sf::RenderStates /*states*/) const {
  // drawing the traces and intersection points
#if !NDEBUG
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
    convex.setFillColor(sf::Color{0, 0, 0, 230});

    target.draw(convex);
  }
}

void PlayerVision::updateCurrent(sf::Time /*dt*/,
                                 CommandQueue<NodeCommand>& /*commands*/) {
  next_trace_id_ = 0;
  for (auto&& trace : traces_) {
    trace.intersection_point.reset();
    intersection_points_[trace.getId()].clear();
  }
  traces_.clear();

  generateTraces();
}

void PlayerVision::generateTraces() {
  static constexpr auto kWallsVertexes = 4;
  static constexpr auto kAdditionalTraces = 2;
  traces_.reserve(walls_.size() * kWallsVertexes * (1 + kAdditionalTraces));
  for (auto&& rect : walls_) {
    auto rect_points = std::array<sf::Vector2f, 4>{
        sf::Vector2f{rect.left, rect.top},
        sf::Vector2f{rect.left + rect.width, rect.top},
        sf::Vector2f{rect.left + rect.width, rect.top + rect.height},
        sf::Vector2f{rect.left, rect.top + rect.height}};

    generateTracesToWall(std::move(rect_points));
  }

  static auto comp = [](const Trace& left_trace, const Trace& right_trace) {
    const auto left_line = left_trace.line;
    const auto right_line = right_trace.line;

    const auto left_direction =
        (left_line[1].position - left_line[0].position).normalized();
    const auto right_direction =
        (right_line[1].position - right_line[0].position).normalized();

    return left_direction.angleTo(right_direction) > sf::degrees(0.f);
  };
  std::sort(traces_.begin(), traces_.end(), comp);
}

void PlayerVision::findNearestIntersectionPoints() {
  for (auto&& trace : traces_) {
    const auto& inter_points = intersection_points_[trace.getId()];
    if (inter_points.empty()) continue;

    auto nearest_point = inter_points[0];
    for (auto&& point : inter_points) {
      static constexpr auto distance = [](sf::Vector2f p1, sf::Vector2f p2) {
        return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
      };
      if (distance(trace.line[0].position, point) <
          distance(trace.line[0].position, nearest_point)) {
        nearest_point = point;
      }
    }

    trace.intersection_point = nearest_point;
  }
}

void PlayerVision::generateTracesToWall(
    std::array<sf::Vector2f, 4> rect_points) {
  static sf::VertexArray line(sf::PrimitiveType::Lines, 2);
  const auto start_pos = player_pos_;
  line[0].position = start_pos;

  static constexpr auto kAngleEps = sf::degrees(0.5f);  // variation angle

  for (auto&& vertex_pos : rect_points) {
    auto direction = (vertex_pos - start_pos).normalized();

    // left
    line[1].position = direction.rotatedBy(-kAngleEps) * trace_len_ + start_pos;
    traces_.emplace_back(line, next_trace_id_++);

    // middle
    line[1].position = direction * trace_len_ + start_pos;
    traces_.emplace_back(line, next_trace_id_++);

    // right
    line[1].position = direction.rotatedBy(kAngleEps) * trace_len_ + start_pos;
    traces_.emplace_back(line, next_trace_id_++);
  }
  ASSERT(traces_.size() < kMaxTraceCount);
}

}  // namespace ink
