#pragma once

namespace sf {
class Texture;
}  // namespace sf

namespace ink {

namespace Textures {
// WARNING: do not change the order!
enum ID {
  Desert,
  Stone,
  Lava,

  Peepo,
  Door,
  Bullet,
};

}  // namespace Textures

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

}  // namespace ink
