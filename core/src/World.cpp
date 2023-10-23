#include <World.hpp>

#include <Entities/PlayerContext.hpp>

namespace ink {

World::World(sf::RenderWindow& window)
    : window_(window),
      world_view_(window.getDefaultView()),
      world_bounds_({0.f, 0.f},
                    {world_view_.getSize().x, world_view_.getSize().y}),
      spawn_position_(world_view_.getSize().x / 2.f,
                      world_bounds_.height - world_view_.getSize().y / 2.f),
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
  static constexpr float kPlayerVelocityShift = 400.f;

  float velocity = 0.f;
  switch (key) {
    case sf::Keyboard::Key::A:
      if (is_pressed) velocity = -kPlayerVelocityShift;
      player_->setPlayerVelocity(velocity, Direction::kToLeft);
      break;
    case sf::Keyboard::Key::D:
      if (is_pressed) velocity = kPlayerVelocityShift;
      player_->setPlayerVelocity(velocity, Direction::kToRight);
      break;
    case sf::Keyboard::Key::W:
      if (is_pressed) velocity = -kPlayerVelocityShift;
      player_->setPlayerVelocity(velocity, Direction::kToUp);
      break;
    case sf::Keyboard::Key::S:
      if (is_pressed) velocity = kPlayerVelocityShift;
      player_->setPlayerVelocity(velocity, Direction::kToDown);
      break;
    case sf::Keyboard::Key::E:
      interact_with_ = is_pressed;
      break;
    default:
      std::cout << "The key isn't implemented!\n";
  }
}

void World::loadTextures() {
  const auto kTexturePath = std::string(RESOURCE_FOLDER);
  textures_.load(Textures::Desert, kTexturePath + "/texture/DesertFloor.jpg");
  textures_.load(Textures::Stone, kTexturePath + "/texture/StoneFloor.jpg");
  textures_.load(Textures::Lava, kTexturePath + "/texture/LavaFloor.png");
  textures_.load(Textures::Peepo,
                 kTexturePath + "/texture/StaregeGun64x64.png");
  textures_.load(Textures::Door, kTexturePath + "/texture/Door.png");
}

void World::createRooms() {
  // rooms factory
  for (int i = 0; i < RoomCount; ++i) {
    const auto texture_type = static_cast<Textures::ID>(i);
    const auto room_type = static_cast<Room>(i);

    auto room = std::make_unique<RoomNode>(
        textures_, textures_.get(texture_type), world_bounds_, room_type);
    room_nodes_[room_type] = room.get();
    room_storage_[room_type] = std::move(room);
  }
}

void World::createRoomConnections() const {
  room_nodes_[DesertRoom]->createConnection(StoneRoom, Top);
  room_nodes_[StoneRoom]->createConnection(DesertRoom, Bottom);

  room_nodes_[DesertRoom]->createConnection(LavaRoom, Right);
  room_nodes_[LavaRoom]->createConnection(DesertRoom, Left);
}

void World::buildScene() {
  // create and connect the rooms
  createRooms();
  createRoomConnections();

  // add the player
  auto player = std::make_unique<Player>(Player::Peepo, textures_);
  player_ = player.get();
  player_->setPosition(spawn_position_);

  // connect entities to the Graph
  room_nodes_[current_room_type_]->setPlayer(std::move(player));
  scene_graph_.attachChild(std::move(room_storage_[current_room_type_]));
}

void World::boundChecking() const {
  const auto& position = player_->getPosition();
  if (position.x < 0)
    player_->setPosition({0, position.y});
  else if (position.x > world_bounds_.width)
    player_->setPosition({world_bounds_.width, position.y});
  if (position.y < 0)
    player_->setPosition({position.x, 0});
  else if (position.y > world_bounds_.height)
    player_->setPosition({position.x, world_bounds_.height});
}

}  // namespace ink
