#include "World.hpp"

World::World(sf::RenderWindow& window)
    : mWindow(window),
      mWorldView(window.getDefaultView()),
      mWorldBounds(0.f,                     // left X position
                   0.f,                     // top Y position
                   mWorldView.getSize().x,  // width
                   mWorldView.getSize().y   // height
                   ),
      mSpawnPosition(mWorldView.getSize().x / 2.f,                       // X
                     mWorldBounds.height - mWorldView.getSize().y / 2.f  // Y
                     ),
      mPlayerAircraft(nullptr) {
  loadTextures();
  buildScene();
  mWorldView.setCenter(mSpawnPosition);
}

void World::update(const sf::Time dt) {
  const sf::Vector2f position = mPlayerAircraft->getPosition();
  std::cout << position.x << " " << position.y << "\n";
  if (position.y < 0 && interact_with) {
    interact_with = false;
    changeRoom(DesertRoom, LavaRoom);
  } else if (position.y > mWorldBounds.height && interact_with) {
    interact_with = false;
    changeRoom(LavaRoom, DesertRoom);
  }

  mSceneGraph.update(dt);
}

void World::changeRoom(const Rooms prev_type, const Rooms new_type) {
  // re-set the player
  auto player = mRoomNodes[prev_type]->getPlayer();
  mRoomNodes[new_type]->setPlayer(std::move(player));
  // dettach a previous room
  auto prev_room = mSceneGraph.detachChild(*mRoomNodes[prev_type]);
  room_storage[prev_type] = std::move(prev_room);
  // attach a new room
  auto new_room = std::move(room_storage[new_type]);
  mSceneGraph.attachChild(std::move(new_room));

  auto player_position = mPlayerAircraft->getPosition();
  player_position.y = mWorldBounds.height;
  mPlayerAircraft->setPosition(player_position);
}

void World::draw() const {
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
    case sf::Keyboard::Key::E:
      interact_with = true;
      break;
  }
}

void World::loadTextures() {
  std::string texturePath = std::string(RESOURCE_FOLDER);
  mTextures.load(Textures::Eagle, texturePath + "/texture/Eagle.png");
  mTextures.load(Textures::Raptor, texturePath + "/texture/Raptor.png");
  mTextures.load(Textures::Desert, texturePath + "/texture/Desert.png");
  mTextures.load(Textures::Lava, texturePath + "/texture/Lava.png");
}

void World::buildScene() {
  // creating rooms
  auto desert_room = std::make_unique<RoomNode>();
  desert_room->buildRoom(mTextures.get(Textures::Desert), mWorldBounds);
  mRoomNodes[DesertRoom] = desert_room.get();
  room_storage[DesertRoom] = std::move(desert_room);

  auto lava_room = std::make_unique<RoomNode>();
  lava_room->buildRoom(mTextures.get(Textures::Lava), mWorldBounds);
  mRoomNodes[LavaRoom] = lava_room.get();
  room_storage[LavaRoom] = std::move(lava_room);

  // Add player's aircraft
  auto leader = std::make_unique<Aircraft>(Aircraft::Eagle, mTextures);
  mPlayerAircraft = leader.get();
  mPlayerAircraft->setPosition(mSpawnPosition);
  mPlayerAircraft->setVelocity(0.f, 0.f);

  // connect entities to the Graph
  mRoomNodes[Rooms::DesertRoom]->setPlayer(std::move(leader));
  mSceneGraph.attachChild(std::move(room_storage[DesertRoom]));
  // mRoomNodes[DesertRoom]->attachChild(std::move(leader));
}