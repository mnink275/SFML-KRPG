#pragma once

#include <array>
#include <iostream>

#include "SceneNode.h"
#include "SpriteNode.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class RoomNode final : public SceneNode {
public:
	RoomNode();

	void buildRoom(sf::Texture& texture, sf::FloatRect bounds);
	void setPlayer(std::unique_ptr<SceneNode>&& player);

private:
	enum Layer {
		Background,
		Air,
		LayerCount
	};

	std::array<SceneNode*, LayerCount> mRoomLayers;
};

