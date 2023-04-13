#include "World.h"

World::World(sf::RenderWindow& window) : mWindow(window)
, mWorldView(window.getDefaultView())
, mScrollSpeed(0.f)
, mWorldBounds(
	0.f, // left X position
	0.f, // top Y position
	mWorldView.getSize().x, // width
	2000.f) // height
, mSpawnPosition(
		mWorldView.getSize().x / 2.f, // X
		mWorldBounds.height - mWorldView.getSize().y / 2.f) // Y
, mPlayerAircraft(nullptr) {
	loadTextures();
	buildScene();
	mWorldView.setCenter(mSpawnPosition);
}


void World::update(sf::Time dt) {
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
	/*if (position.x <= mWorldBounds.left + 150
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150) {
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}*/
	mSceneGraph.update(dt);
}


void World::draw() {
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}


void World::loadTextures() {
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
}


void World::buildScene() {
	for (std::size_t i = 0; i < LayerCount; ++i) {
		auto layer = std::make_unique<SceneNode>();
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}
	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's aircraft
	auto leader = std::make_unique<Aircraft>(Aircraft::Eagle, mTextures);
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// Add two escorting aircrafts, placed relatively to the main plane
	auto leftEscort = std::make_unique<Aircraft>(Aircraft::Raptor, mTextures);
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	auto rightEscort = std::make_unique<Aircraft>(Aircraft::Raptor, mTextures);
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
}