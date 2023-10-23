#pragma once

namespace sf {
class Texture;
}  // sf namespace

namespace ink {

namespace Textures {
// WARNING: do not change the order!
enum ID {
  Desert,
  Stone,
  Lava,

  Peepo,
  Door,
};

}  // Texture namespace

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

}  // namespace ink
