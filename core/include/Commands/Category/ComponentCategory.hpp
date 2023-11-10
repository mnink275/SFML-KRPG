#pragma once

#include <Commands/Category/Category.hpp>

namespace ink {

enum class ComponentCategory : CategoryUnderlying {
  None = 0,
  kPhysics = 1 << 0,
  kGraphics = 1 << 1,
  kInput = 1 << 2,
  kCombat = 1 << 3,
  kCollision = 1 << 4,
};

}  // namespace ink
