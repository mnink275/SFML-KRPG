#pragma once

// Forward declaration of SFML classes
namespace sf {
class Texture;
}  // sf namespace

namespace Textures {
enum ID {
  Peepo,
  Stone,
  Desert,
  Door,
};
}  // Texture namespace

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
