#pragma once

#include <cstddef>

namespace ink::room {

enum class ConnectionType { Top, Right, Bottom, Left, Count };

inline constexpr auto ConnectionsCount =
    static_cast<std::size_t>(ConnectionType::Count);

}  // namespace ink::room
