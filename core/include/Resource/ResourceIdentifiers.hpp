#pragma once

#include <cstddef>

namespace sf {
class Texture;
class Font;
}  // namespace sf

namespace ink {

// WARNING: do not change the order!
enum class Textures {
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

enum class Fonts {
  kArial = 0,
  kExpressway = 1,
  kSansation = 2,
};

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures>;
using FontHolder = ResourceHolder<sf::Font, Fonts>;

}  // namespace ink
