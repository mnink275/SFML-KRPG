#pragma once

#include <array>
#include <iostream>

#include "Aircraft.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "RoomNode.h"

class World final : private sf::NonCopyable {
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	void loadTextures();
	void buildScene();
	void changeRoom();

	enum Rooms {
		DesertRoom,
		LavaRoom,
		RoomCount
	};

	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextures;
	SceneNode mSceneGraph;
	std::array<RoomNode*, RoomCount> mRoomNodes;
	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;

	Aircraft* mPlayerAircraft;
};