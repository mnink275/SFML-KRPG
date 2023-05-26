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
      player_(nullptr),
      current_room_type_(DesertRoom) {
  loadTextures();
  buildScene();
  world_view_.setCenter(spawn_position_);
}

void World::update(const sf::Time dt) {
  boundChecking();
  checkDoorInteraction();

  scene_graph_.update(dt);
}

void World::checkDoorInteraction() {
  if (interact_with_) {
    interact_with_ = false;
    RoomNode* curr_room = room_nodes_[current_room_type_];
    if (auto next_room_type = curr_room->isDoorInteraction()) {
      changeRoom(current_room_type_, next_room_type.value());
    }
  }
}

void World::changeRoom(const Room prev_type, const Room new_type) {
  // re-set the player
  auto player = room_nodes_[prev_type]->popPlayer();
  room_nodes_[new_type]->setPlayer(std::move(player));
  // detach a previous room
  auto prev_room = scene_graph_.detachChild(*room_nodes_[prev_type]);
  room_storage_[prev_type] = std::move(prev_room);
  // attach a new room
  auto new_room = std::move(room_storage_[new_type]);
  scene_graph_.attachChild(std::move(new_room));

  current_room_type_ = new_type;
}

void World::draw() const {
  window_.setView(world_view_);
  window_.draw(scene_graph_);
}

void World::handlePlayerInput(const sf::Keyboard::Key key,
                              const bool is_pressed) {
  constexpr float kPlayerVelocityShift = 200.f;

  switch (key) {
    case sf::Keyboard::Key::A:
      if (is_pressed)
        player_->setVelocityX(-kPlayerVelocityShift);
      else
        player_->setVelocityX(0.f);
      break;
    case sf::Keyboard::Key::D:
      if (is_pressed)
        player_->setVelocityX(kPlayerVelocityShift);
      else
        player_->setVelocityX(0.f);
      break;
    case sf::Keyboard::Key::W:
      if (is_pressed)
        player_->setVelocityY(-kPlayerVelocityShift);
      else
        player_->setVelocityY(0.f);
      break;
    case sf::Keyboard::Key::S:
      if (is_pressed)
        player_->setVelocityY(kPlayerVelocityShift);
      else
        player_->setVelocityY(0.f);
      break;
    case sf::Keyboard::Key::E:
      if (is_pressed)
        interact_with_ = true;
      else
        interact_with_ = false;
      break;
    default:
      std::cout << "The key isn't implemented!\n";
  }
}

void World::loadTextures() {
  const auto kTexturePath = std::string(RESOURCE_FOLDER);
  textures_.load(Textures::Peepo,
                 kTexturePath + "/texture/StaregeGun64x64.png");
  textures_.load(Textures::Stone, kTexturePath + "/texture/StoneFloor.jpg");
  textures_.load(Textures::Desert, kTexturePath + "/texture/DesertFloor.jpg");
  textures_.load(Textures::Door, kTexturePath + "/texture/Door.png");
}

void World::createRooms() {
  // TODO: refactor to factory pattern
  auto desert_room = std::make_unique<RoomNode>(
      textures_, textures_.get(Textures::Desert), world_bounds_, StoneRoom);
  room_nodes_[DesertRoom] = desert_room.get();
  room_storage_[DesertRoom] = std::move(desert_room);

  auto stone_room = std::make_unique<RoomNode>(
      textures_, textures_.get(Textures::Stone), world_bounds_, DesertRoom);
  room_nodes_[StoneRoom] = stone_room.get();
  room_storage_[StoneRoom] = std::move(stone_room);
}

void World::buildScene() {
  // create the rooms
  createRooms();

  // add the player
  auto player = std::make_unique<Player>(Player::Peepo, textures_);
  player_ = player.get();
  player_->setPosition(spawn_position_);

  // connect entities to the Graph
  room_nodes_[current_room_type_]->setPlayer(std::move(player));

  room_nodes_[DesertRoom]->createConnection(StoneRoom, Top);
  room_nodes_[StoneRoom]->createConnection(DesertRoom, Bottom);

  scene_graph_.attachChild(std::move(room_storage_[current_room_type_]));
}

void World::boundChecking() const {
  const auto& position = player_->getPosition();
  if (position.x < 0)
    player_->setPosition(0, position.y);
  else if (position.x > world_bounds_.width)
    player_->setPosition(world_bounds_.width, position.y);
  if (position.y < 0)
    player_->setPosition(position.x, 0);
  else if (position.y > world_bounds_.height)
    player_->setPosition(position.x, world_bounds_.height);
}