#pragma once

#include <Commands/Category/Category.hpp>

namespace ink {

enum class ComponentCategory : CategoryUnderlying {
  None = 0,
  kPhysic = 1 << 0,
  kGraphic = 1 << 1,
  kInput = 1 << 2,
  kCombat = 1 << 3,
};

}  // namespace ink
