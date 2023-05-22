#include "RoomNode.hpp"

void RoomNode::buildRoom(sf::Texture& texture, const sf::FloatRect bounds) {
  // Prepare the tiled background
  sf::IntRect texture_rect(bounds);
  texture.setRepeated(true);

  // Add the background sprite to the scene
  auto background_sprite = std::make_unique<SpriteNode>(texture, texture_rect);
  background_sprite->setPosition(bounds.left, bounds.top);
  room_layers_[Background] = background_sprite.get();
  attachChild(std::move(background_sprite));

  // sf::Texture& texture2 = textures.get(Textures::Lava);
  // sf::IntRect textureRect2(bounds);
  // texture2.setRepeated(true);

  //// Add the background sprite to the scene
  // auto backgroundSprite2 = std::make_unique<SpriteNode>(texture2,
  // textureRect2); backgroundSprite2->setPosition(bounds.left + 100, bounds.top
  // + 100); attachChild(std::move(backgroundSprite2));
}

void RoomNode::setPlayer(Ptr player) {
  room_layers_[Air] = player.get();
  room_layers_[Background]->attachChild(std::move(player));
}

SceneNode::Ptr RoomNode::getPlayer() const {
  return room_layers_[Background]->detachChild(*room_layers_[Air]);
}