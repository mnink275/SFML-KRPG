#pragma once

#include <Commands/Category/Category.hpp>

namespace ink {

enum class NodeCategory : CategoryUnderlying {
  None = 0,
  Room = 1 << 0,
  Player = 1 << 1,
};

}  // namespace ink
