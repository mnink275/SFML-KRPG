#pragma once

#include <optional>
#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

namespace ink {

// TODO: rename `Trace` to `Line`
class Trace {
 public:
  explicit Trace(sf::VertexArray trace_line);
  Trace(sf::VertexArray trace_line, std::size_t id);

  ~Trace() = default;

  Trace(const Trace&) = delete;
  Trace& operator=(const Trace&) = delete;

  Trace(Trace&&) = default;
  Trace& operator=(Trace&&) = default;

  std::optional<sf::Vector2f> findIntersection(const Trace& other_trace) const;
  void shiftTo(const sf::Vector2f& new_pos);
  std::size_t getId() const noexcept;

 public:
  static constexpr auto kEps = 1.f;

  enum class TraceType {
    kVertical = 0,
    kHorizontal = 1,
    kCommon = 2,
  };

  sf::VertexArray line;
  std::optional<sf::Vector2f> intersection_point;

 private:
  bool belongsToLine(sf::Vector2f point,
                     const sf::VertexArray& line) const noexcept;

  static std::optional<sf::Vector2f> findIntersectionImpl(const Trace& left,
                                                          const Trace& right);

 private:
  TraceType trace_type;
  float slope;
  float height;
  std::size_t id_;
};

}  // namespace ink
