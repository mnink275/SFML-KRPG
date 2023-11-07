#pragma once

namespace sf {
class Texture;
}  // namespace sf

namespace ink {

// WARNING: do not change the order!
enum Textures {
  kDesert,
  kStone,
  kLava,

  kPeepoLeft,
  kPeepoRight,
  kDoor,
  kBullet,
  kWall,
};

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures>;

}  // namespace ink
