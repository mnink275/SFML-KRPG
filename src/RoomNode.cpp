#include "RoomNode.hpp"

void RoomNode::buildRoom(sf::Texture& texture, const sf::FloatRect bounds) {
  // prepare the tiled background
  sf::IntRect texture_rect(bounds);
  texture.setRepeated(true);

  // add the background sprite to the scene
  auto background_sprite = std::make_unique<SpriteNode>(texture, texture_rect);
  background_sprite->setPosition(bounds.left, bounds.top);
  room_layers_[Background] = background_sprite.get();
  attachChild(std::move(background_sprite));
}

void RoomNode::setPlayer(Ptr player) {
  room_layers_[Air] = player.get();
  room_layers_[Background]->attachChild(std::move(player));
}

SceneNode::Ptr RoomNode::popPlayer() const {
  return room_layers_[Background]->detachChild(*room_layers_[Air]);
}