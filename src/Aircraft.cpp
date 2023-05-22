#include "Aircraft.hpp"

Textures::ID toTextureID(const Aircraft::Type type) {
  switch (type) {
    case Aircraft::Eagle:
      return Textures::Eagle;
    case Aircraft::Raptor:
      return Textures::Raptor;
  }
  return Textures::Eagle;
}

Aircraft::Aircraft(const Type type, const TextureHolder& textures)
    : type_(type), sprite_(textures.get(toTextureID(type))) {
  const sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target,
                           const sf::RenderStates states) const {
  target.draw(sprite_, states);
}