#include "Player.hpp"

Textures::ID toTextureID(const Player::Type type) {
  switch (type) {
    case Player::Eagle:
      return Textures::Eagle;
    case Player::Raptor:
      return Textures::Raptor;
  }
  return Textures::Eagle;
}

Player::Player(const Type type, const TextureHolder& textures)
    : type_(type), sprite_(textures.get(toTextureID(type))) {
  const sf::FloatRect bounds = sprite_.getLocalBounds();
  sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::drawCurrent(sf::RenderTarget& target,
                         const sf::RenderStates states) const {
  target.draw(sprite_, states);
}