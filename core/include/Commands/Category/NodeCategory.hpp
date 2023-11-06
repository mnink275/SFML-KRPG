#pragma once

#include <Commands/Category/Category.hpp>

namespace ink {

enum class NodeCategory : CategoryUnderlying {
  kNone = 0,
  kRoom = 1 << 0,
  kUnit = 1 << 1,
  kBullet = 1 << 2,
};

}  // namespace ink
