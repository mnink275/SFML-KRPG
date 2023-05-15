#include "RoomNode.h"


RoomNode::RoomNode() {

}


void RoomNode::buildRoom(sf::Texture& texture, sf::FloatRect bounds) {
	// Prepare the tiled background
	sf::IntRect textureRect(bounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
	backgroundSprite->setPosition(bounds.left, bounds.top);
	mRoomLayers[Background] = backgroundSprite.get();
	attachChild(std::move(backgroundSprite));

	//sf::Texture& texture2 = textures.get(Textures::Lava);
	//sf::IntRect textureRect2(bounds);
	//texture2.setRepeated(true);

	//// Add the background sprite to the scene
	//auto backgroundSprite2 = std::make_unique<SpriteNode>(texture2, textureRect2);
	//backgroundSprite2->setPosition(bounds.left + 100, bounds.top + 100);
	//attachChild(std::move(backgroundSprite2));
}


void RoomNode::setPlayer(Ptr player) {
	mRoomLayers[Air] = player.get();
	mRoomLayers[Background]->attachChild(std::move(player));
}


SceneNode::Ptr RoomNode::getPlayer() {
	return mRoomLayers[Background]->detachChild(*mRoomLayers[Air]);
}