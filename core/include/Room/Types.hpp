#pragma once

#include <cstddef>

namespace ink::room {

enum class Type { kDesertRoom, kStoneRoom, kLavaRoom, kCount };

inline constexpr auto kRoomCount=
    static_cast<std::size_t>(Type::kCount);

}  // namespace ink::room
