#include "World.h"

World::World(sf::RenderWindow& window)
	: mWindow(window),
	mWorldView(window.getDefaultView()),
	mWorldBounds(
	0.f, // left X position
	0.f, // top Y position
	mWorldView.getSize().x, // width
	mWorldView.getSize().y // height
	),
	mSpawnPosition(
		mWorldView.getSize().x / 2.f, // X
		mWorldBounds.height - mWorldView.getSize().y / 2.f // Y
	),
	mPlayerAircraft(nullptr) {
	loadTextures();
	buildScene();
	mWorldView.setCenter(mSpawnPosition);
}


void World::update(sf::Time dt) {
	sf::Vector2f position = mPlayerAircraft->getPosition();
	std::cout << position.x << " " << position.y << "\n";
	if (position.y < 0) {
		changeRoom();
	}

	mSceneGraph.update(dt);
}

//
//void World::changeRoom() {
//	// Prepare the tiled background
//	sf::Texture& texture = mTextures.get(Textures::Lava);
//	sf::IntRect textureRect(mWorldBounds, mWorldBounds);
//	texture.setRepeated(true);
//
//	// Add the background sprite to the scene
//	mSceneLayers[Background]->detachChild(*curr_texture);
//	auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
//	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
//	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
//
//	auto player_position = mPlayerAircraft->getPosition();
//	player_position.y = mWorldBounds.height;
//	mPlayerAircraft->setPosition(player_position);
//}


void World::draw() {
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}


void World::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	float player_velocity_shift = 200.f;
	if (!isPressed) {
		mPlayerAircraft->setVelocity(0.f, 0.f);
		return;
	}

	switch (key) {
	case sf::Keyboard::Key::A:
		mPlayerAircraft->setVelocity(-player_velocity_shift, 0.f);
		break;
	case sf::Keyboard::Key::D:
		mPlayerAircraft->setVelocity(player_velocity_shift, 0.f);
		break;
	case sf::Keyboard::Key::W:
		mPlayerAircraft->setVelocity(0.f, -player_velocity_shift);
		break;
	case sf::Keyboard::Key::S:
		mPlayerAircraft->setVelocity(0.f, player_velocity_shift);
		break;
	}
}


void World::loadTextures() {
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
	mTextures.load(Textures::Lava, "Media/Textures/Lava.png");
}


void World::buildScene() {
	// creating rooms
	auto desert_room = std::make_unique<RoomNode>();
	desert_room->buildRoom(mTextures.get(Textures::Desert), mWorldBounds);
	mRoomNodes[DesertRoom] = desert_room.get();
	mSceneGraph.attachChild(std::move(desert_room));

	auto lava_room = std::make_unique<RoomNode>();
	lava_room->buildRoom(mTextures.get(Textures::Lava), mWorldBounds);
	mRoomNodes[DesertRoom] = lava_room.get();

	// Add player's aircraft
	auto leader = std::make_unique<Aircraft>(Aircraft::Eagle, mTextures);
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(0.f, 0.f);
	mRoomNodes[Rooms::DesertRoom]->setPlayer(std::move(leader));
	//mRoomNodes[DesertRoom]->attachChild(std::move(leader));
}