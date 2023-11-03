#pragma once

namespace ink::component {

using CategoryType = unsigned int;

enum class Category : CategoryType {
  None = 0,
  kPhysic = 1 << 0,
  kGraphic = 1 << 1,
  kInput = 1 << 2,
  kCombat = 1 << 3,
};

}  // namespace ink::component
