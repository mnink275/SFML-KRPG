#pragma once

namespace ink {

using CategoryType = unsigned int;

enum class Category : CategoryType {
  None = 0,
  RoomContext = 1 << 0,
  PlayerContex = 1 << 1,
};

}  // namespace ink
