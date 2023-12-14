#include <Trace.hpp>

#include <cmath>
#include <functional>
#include <stdexcept>

#include <fmt/format.h>

#include <Utils/Assert.hpp>

namespace ink {

namespace {

using TraceType = Trace::TraceType;
using Trace = Trace;

constexpr auto trace_type_initer = [](const sf::VertexArray& line) {
  ASSERT(line.getVertexCount() == 2);
  auto [x1, y1] = line[0].position;
  auto [x2, y2] = line[1].position;
  bool is_vertical = std::abs(x2 - x1) < Trace::kEps;
  bool is_horizontal = std::abs(y2 - y1) < Trace::kEps;
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

Trace::Trace(sf::VertexArray trace_line) : Trace(std::move(trace_line), 0) {}

Trace::Trace(sf::VertexArray trace_line, std::size_t id)
    : line(std::move(trace_line)),
      intersection_point(std::nullopt),
      trace_type(std::invoke(trace_type_initer, line)),
      slope(std::invoke(slope_initer, line, trace_type)),
      height(std::invoke(height_initer, line, trace_type, slope)),
      id_(id) {
  ASSERT_MSG(line.getVertexCount() == 2,
             fmt::format("Lines count is: {}", line.getVertexCount()));
};

std::optional<sf::Vector2f> Trace::findIntersection(
    const Trace& other_trace) const {
  auto point = findIntersectionImpl(*this, other_trace);
  if (!point.has_value()) return std::nullopt;

  if (!belongsToLine(*point, line) ||
      !belongsToLine(*point, other_trace.line)) {
    return std::nullopt;
  }

  return point;
}

void Trace::shiftTo(const sf::Vector2f& new_pos) {
  auto curr_pos = line[0].position;
  line[0].position -= curr_pos;
  line[1].position -= curr_pos;

  line[0].position += new_pos;
  line[1].position += new_pos;

  height = std::invoke(height_initer, line, trace_type, slope);
}

std::size_t Trace::getId() const noexcept { return id_; }

bool Trace::belongsToLine(sf::Vector2f point,
                          const sf::VertexArray& line) const noexcept {
  ASSERT(line.getVertexCount() == 2);
  auto [x1, y1] = line[0].position;
  auto [x2, y2] = line[1].position;

  if (x1 > x2) std::swap(x1, x2);
  if (std::clamp(point.x, x1, x2) != point.x) return false;

  if (y1 > y2) std::swap(y1, y2);
  if (std::clamp(point.y, y1, y2) != point.y) return false;

  return true;
}

std::optional<sf::Vector2f> Trace::findIntersectionImpl(const Trace& left,
                                                        const Trace& right) {
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

}  // namespace ink
