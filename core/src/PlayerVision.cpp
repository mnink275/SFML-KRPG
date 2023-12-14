#include <PlayerVision.hpp>

#include <fmt/format.h>
#include <SFML/Graphics/CircleShape.hpp>

#include <array>

#include <Utils/Math.hpp>

namespace ink {

namespace {

using TraceType = PlayerVision::Trace::TraceType;
using Trace = PlayerVision::Trace;

constexpr auto trace_type_initer = [](const sf::VertexArray& line) {
  ASSERT(line.getVertexCount() == 2);
  auto [x1, y1] = line[0].position;
  auto [x2, y2] = line[1].position;
  bool is_vertical = std::abs(x2 - x1) < Trace::kEps;
  bool is_horizontal = std::abs(y2 - y1) < Trace::kEps;
  // fmt::println("Line: P1: ({}, {}), P2: ({}, {})", x1, y1, x2, y2);
  // fmt::println("Direction: vertical {}, horizontal {}", is_vertical,
  //              is_horizontal);
  if (is_vertical && is_horizontal)
    throw std::runtime_error("Too short Trace line");
  if (is_vertical) return TraceType::kVertical;
  if (is_horizontal) return TraceType::kHorizontal;
  return TraceType::kCommon;
};

constexpr auto slope_initer = [](const sf::VertexArray& line,
                                 const TraceType trace_type) {
  auto [x1, y1] = line[0].position;
  auto [x2, y2] = line[1].position;
  switch (trace_type) {
    case TraceType::kVertical:
      return std::numeric_limits<float>::max();
    case TraceType::kHorizontal:
      return 0.f;
    case TraceType::kCommon:
      ASSERT(std::abs(x2 - x1) > Trace::kEps);
      return (y2 - y1) / (x2 - x1);
  }
  ASSERT(false);
};

constexpr auto height_initer = [](const sf::VertexArray& line,
                                  const TraceType trace_type,
                                  const float slope) {
  auto [x1, y1] = line[0].position;
  switch (trace_type) {
    case TraceType::kVertical:
      return std::numeric_limits<float>::max();
    case TraceType::kHorizontal:
      return y1;  // or from line[1] because they are equal
    case TraceType::kCommon:
      return y1 - slope * x1;
  }
  ASSERT(false);
};

}  // namespace

PlayerVision::Trace::Trace(sf::VertexArray line)
    : trace_type(std::invoke(trace_type_initer, line)),
      slope(std::invoke(slope_initer, line, trace_type)),
      height(std::invoke(height_initer, line, trace_type, slope)),
      line(std::move(line)),
      intersection_point(std::nullopt),
      intersection_points() {
  ASSERT_MSG(this->line.getVertexCount() == 2,
             fmt::format("Lines count is: {}", this->line.getVertexCount()));
  intersection_points.reserve(20);
};

std::optional<sf::Vector2f> PlayerVision::Trace::findIntersection(
    const Trace& other_trace) const {
  auto point = findIntersectionImpl(*this, other_trace);
  if (!point.has_value()) return std::nullopt;

  if (!belongsToLine(*point, line) ||
      !belongsToLine(*point, other_trace.line)) {
    return std::nullopt;
  }

  return point;
}

bool PlayerVision::Trace::belongsToLine(
    sf::Vector2f point, const sf::VertexArray& line) const noexcept {
  ASSERT(line.getVertexCount() == 2);
  auto [x1, y1] = line[0].position;
  auto [x2, y2] = line[1].position;

  if (x1 > x2) std::swap(x1, x2);
  if (std::clamp(point.x, x1, x2) != point.x) return false;

  if (y1 > y2) std::swap(y1, y2);
  if (std::clamp(point.y, y1, y2) != point.y) return false;

  return true;
}

std::optional<sf::Vector2f> PlayerVision::Trace::findIntersectionImpl(
    const Trace& left, const Trace& right) {
  auto left_type = left.trace_type;
  auto right_type = right.trace_type;

  if (static_cast<int>(left_type) > static_cast<int>(right_type))
    return findIntersectionImpl(right, left);

  float x = 0.f;
  float y = 0.f;
  // equal pairs
  if ((left_type == TraceType::kVertical &&
       right_type == TraceType::kVertical) ||
      (left_type == TraceType::kHorizontal &&
       right_type == TraceType::kHorizontal)) {
    return std::nullopt;
  }
  if (left_type == TraceType::kCommon && right_type == TraceType::kCommon) {
    x = -1 * (right.height - left.height) / (right.slope - left.slope);
    y = left.slope * x + left.height;

    return sf::Vector2f{x, y};
  }

  // unique pairs in ascending order
  if (left_type == TraceType::kVertical &&
      right_type == TraceType::kHorizontal) {
    x = left.line[0].position.x;
    y = right.line[0].position.y;
  } else if (left_type == TraceType::kHorizontal &&
             right_type == TraceType::kCommon) {
    y = left.line[0].position.y;
    x = (y - right.height) / right.slope;
  } else if (left_type == TraceType::kVertical &&
             right_type == TraceType::kCommon) {
    x = left.line[0].position.x;
    y = right.slope * x + right.height;
  }

  return sf::Vector2f{x, y};
}

PlayerVision::PlayerVision(const float trace_len, sf::FloatRect bounds)
    : SceneNode(NodeCategory::kVision),
      trace_len_(trace_len),
      bounds_(bounds),
      traces_(),
      trace_count_(1024) {
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

      trace.intersection_points.push_back(*point);
    }
  }
  for (auto&& trace : traces_) {
    auto& inter_points = trace.intersection_points;
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
    trace.intersection_points.clear();

    auto old_pos = trace.line[0].position;
    trace.line[0].position -= old_pos;
    trace.line[1].position -= old_pos;

    trace.line[0].position += player_pos;
    trace.line[1].position += player_pos;

    trace.height =
        std::invoke(height_initer, trace.line, trace.trace_type, trace.slope);
  }
}

sf::FloatRect PlayerVision::getBoundingRect() const { return bounds_; }

void PlayerVision::drawCurrent(sf::RenderTarget& target,
                               sf::RenderStates /*states*/) const {
  for (auto&& trace : traces_) {
    target.draw(trace.line);
  }
  for (auto&& trace : traces_) {
    sf::CircleShape circle{2.0f};
    circle.setFillColor(sf::Color::Red);
    // ASSERT(trace.intersection_point.has_value());
    circle.setPosition(*trace.intersection_point);
    target.draw(circle);
  }
  for (std::size_t i = 0; i < traces_.size(); ++i) {
    const auto& left_trace = traces_[i];
    const auto& right_trace = traces_[(i + 1) % traces_.size()];
    sf::ConvexShape convex;
    convex.setPointCount(4);
    if (!right_trace.intersection_point.has_value()) {
      // print_trace(right_trace);
      auto wrong = right_trace;
      wrong.line[0].color = sf::Color::Red;
      wrong.line[1].color = sf::Color::Red;
      target.draw(wrong.line);
    }
    if (!left_trace.intersection_point.has_value()) {
      // print_trace(left_trace);
      auto wrong = left_trace;
      wrong.line[0].color = sf::Color::Red;
      wrong.line[1].color = sf::Color::Red;
      target.draw(wrong.line);
    }
    convex.setPoint(0, *right_trace.intersection_point);
    convex.setPoint(1, *left_trace.intersection_point);
    convex.setPoint(2, left_trace.line[1].position);
    convex.setPoint(3, right_trace.line[1].position);
    convex.setFillColor(sf::Color::Blue);

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

  const auto angle_step = sf::degrees(360.0f / trace_count_);

  std::vector<Trace> traces;
  traces.reserve(trace_count_);
  for (std::size_t i = 0; i < trace_count_; ++i) {
    traces.emplace_back(line);

    // turn the `line` clockwise
    line[1].position -= line[0].position;
    line[1].position = line[1].position.rotatedBy(angle_step);
    line[1].position += line[0].position;
  }

  traces_ = std::move(traces);
}

}  // namespace ink
