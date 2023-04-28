#pragma once

#include "Aircraft.h"
#include "ResourceHolder.h"
#include "SpriteNode.h"
#include <array>
#include <iostream>

class World : private sf::NonCopyable {
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	void loadTextures();
	void buildScene();
	void createNewArea();

	enum Layer {
		Background,
		Air,
		LayerCount
	};

	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextures;
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;
	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
};