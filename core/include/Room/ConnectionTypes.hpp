#pragma once

#include <cstddef>

#include <fmt/format.h>

#include <Utils/Assert.hpp>
#include <Utils/ToString.hpp>

namespace ink {

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
      ASSERT_MSG(false, fmt::format("Unhandler ConnectionType with id: {}",
                                    utils::toString(connection)));
  }
}

inline constexpr auto ConnectionsCount =
    static_cast<std::size_t>(ConnectionType::Count);

}  // namespace ink
