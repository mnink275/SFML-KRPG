#pragma once

#include <cassert>
#include <cstddef>

namespace ink::room {

enum class ConnectionType { Top, Right, Bottom, Left, Count };

inline static ConnectionType getMirrorType(ConnectionType connection) {
  switch (connection) {
    case ConnectionType::Top:
      return ConnectionType::Bottom;
    case ConnectionType::Bottom:
      return ConnectionType::Top;
    case ConnectionType::Right:
      return ConnectionType::Left;
    case ConnectionType::Left:
      return ConnectionType::Right;
    default:
      assert(false);
  }
}

inline constexpr auto ConnectionsCount =
    static_cast<std::size_t>(ConnectionType::Count);

}  // namespace ink::room
