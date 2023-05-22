#include "World.hpp"

World::World(sf::RenderWindow& window)
    : window_(window),
      world_view_(window.getDefaultView()),
      world_bounds_(0.f,                      // left X position
                    0.f,                      // top Y position
                    world_view_.getSize().x,  // width
                    world_view_.getSize().y   // height
                    ),
      spawn_position_(world_view_.getSize().x / 2.f,                        // X
                      world_bounds_.height - world_view_.getSize().y / 2.f  // Y
                      ),
      player_aircraft_(nullptr) {
  loadTextures();
  buildScene();
  world_view_.setCenter(spawn_position_);
}

void World::update(const sf::Time dt) {
  const sf::Vector2f position = player_aircraft_->getPosition();
  // std::cout << position.x << " " << position.y << "\n";
  if (position.y < 0 && interact_with_) {
    interact_with_ = false;
    changeRoom(DesertRoom, LavaRoom);
  } else if (position.y > world_bounds_.height && interact_with_) {
    interact_with_ = false;
    changeRoom(LavaRoom, DesertRoom);
  }

  scene_graph_.update(dt);
}

void World::changeRoom(const Rooms prev_type, const Rooms new_type) {
  // re-set the player
  auto player = room_nodes_[prev_type]->getPlayer();
  room_nodes_[new_type]->setPlayer(std::move(player));
  // detach a previous room
  auto prev_room = scene_graph_.detachChild(*room_nodes_[prev_type]);
  room_storage_[prev_type] = std::move(prev_room);
  // attach a new room
  auto new_room = std::move(room_storage_[new_type]);
  scene_graph_.attachChild(std::move(new_room));

  auto player_position = player_aircraft_->getPosition();
  player_position.y = world_bounds_.height;
  player_aircraft_->setPosition(player_position);
}

void World::draw() const {
  window_.setView(world_view_);
  window_.draw(scene_graph_);
}

void World::handlePlayerInput(const sf::Keyboard::Key key,
                              const bool is_pressed) {
  constexpr float kPlayerVelocityShift = 200.f;
  if (!is_pressed) {
    player_aircraft_->setVelocity(0.f, 0.f);
    return;
  }

  switch (key) {
    case sf::Keyboard::Key::A:
      player_aircraft_->setVelocity(-kPlayerVelocityShift, 0.f);
      break;
    case sf::Keyboard::Key::D:
      player_aircraft_->setVelocity(kPlayerVelocityShift, 0.f);
      break;
    case sf::Keyboard::Key::W:
      player_aircraft_->setVelocity(0.f, -kPlayerVelocityShift);
      break;
    case sf::Keyboard::Key::S:
      player_aircraft_->setVelocity(0.f, kPlayerVelocityShift);
      break;
    case sf::Keyboard::Key::E:
      interact_with_ = true;
      break;
    default:
      std::cout << "The key isn't implemented!\n";
  }
}

void World::loadTextures() {
  const auto kTexturePath = std::string(RESOURCE_FOLDER);
  textures_.load(Textures::Eagle, kTexturePath + "/texture/Eagle.png");
  textures_.load(Textures::Raptor, kTexturePath + "/texture/Raptor.png");
  textures_.load(Textures::Desert, kTexturePath + "/texture/Desert.png");
  textures_.load(Textures::Lava, kTexturePath + "/texture/Lava.png");
}

void World::buildScene() {
  // creating rooms
  auto desert_room = std::make_unique<RoomNode>();
  desert_room->buildRoom(textures_.get(Textures::Desert), world_bounds_);
  room_nodes_[DesertRoom] = desert_room.get();
  room_storage_[DesertRoom] = std::move(desert_room);

  auto lava_room = std::make_unique<RoomNode>();
  lava_room->buildRoom(textures_.get(Textures::Lava), world_bounds_);
  room_nodes_[LavaRoom] = lava_room.get();
  room_storage_[LavaRoom] = std::move(lava_room);

  // Add player's aircraft
  auto leader = std::make_unique<Aircraft>(Aircraft::Eagle, textures_);
  player_aircraft_ = leader.get();
  player_aircraft_->setPosition(spawn_position_);
  player_aircraft_->setVelocity(0.f, 0.f);

  // connect entities to the Graph
  room_nodes_[DesertRoom]->setPlayer(std::move(leader));
  scene_graph_.attachChild(std::move(room_storage_[DesertRoom]));
  // room_nodes_[DesertRoom]->attachChild(std::move(leader));
}