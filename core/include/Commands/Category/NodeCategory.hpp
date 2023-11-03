#pragma once

#include <Commands/Category/Category.hpp>

namespace ink {

enum class NodeCategory : CategoryUnderlying {
  None = 0,
  RoomContext = 1 << 0,
  PlayerContex = 1 << 1,
};

}  // namespace ink
