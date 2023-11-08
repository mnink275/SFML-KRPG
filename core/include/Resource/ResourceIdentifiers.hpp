#pragma once

#include <cstddef>

namespace sf {
class Texture;
}  // namespace sf

namespace ink {

// WARNING: do not change the order!
enum Textures {
  // rooms backgrounds
  kDesert = 0,
  kStone = 1,
  kLava = 2,
  kIce = 3,
  kStoneOnGrass = 4,
  kCount,

  // other
  kPeepoLeft,
  kPeepoRight,
  kDoor,
  kBullet,
  kWall,
};

inline constexpr auto kRoomCount = static_cast<std::size_t>(Textures::kCount);

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures>;

}  // namespace ink
