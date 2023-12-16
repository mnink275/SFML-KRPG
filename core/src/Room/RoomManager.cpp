#include <Room/RoomManager.hpp>

#include <memory>
#include <random>
#include <variant>

#include <fmt/format.h>

#include <Commands/Category/NodeCategory.hpp>
#include <Entities/Unit.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/ConnectionTypes.hpp>
#include <SceneNode.hpp>

namespace ink {

namespace {

constexpr auto walls_initer = [](const sf::FloatRect& bounds,
                                 const float wall_thickness) {
  const auto width = bounds.width;
  const auto height = bounds.height;
  return std::vector<sf::FloatRect>{
      {{0.0f, 0.0f}, {wall_thickness, height}},                      // left
      {{0.0f, 0.0f}, {width, wall_thickness}},                       // top
      {{width - wall_thickness, 0.0f}, {wall_thickness, height}},    // right
      {{0.0f, height - wall_thickness}, {width, wall_thickness}},    // bottom
      {{3 * width / 4, height / 2}, {wall_thickness, height / 2}}};  // middle
};

}  // namespace

RoomManager::RoomManager(SceneNode& scene_graph, sf::FloatRect world_bounds,
                         TextureHolder& textures, NodeCategory category)
    : SceneNode(category),
      scene_graph_(scene_graph),
      curr_room_id_(0),
      rooms_count_(0),
      world_bounds_(std::move(world_bounds)),
      textures_(textures),
      wall_thickness_(10.f),
      walls_(std::invoke(walls_initer, world_bounds_, wall_thickness_)) {}

void RoomManager::attachUnit(std::unique_ptr<Unit> unit) {
  // connect entities to the Graph
  if (unit->GetOwnerType() == Owner::kPlayer) {
    room_nodes_[curr_room_id_]->setPlayer(std::move(unit));
  } else {
    room_nodes_[curr_room_id_]->attachChild(std::move(unit));
  }
}

void RoomManager::createInitialRoom() {
  createRoom(static_cast<std::size_t>(Textures::kDesert));
  scene_graph_.attachChild(std::move(room_storage_[curr_room_id_]));
}

void RoomManager::changeRoomTo(std::size_t next_room_id) {
  // re-set the player
  auto player = room_nodes_[curr_room_id_]->popPlayer();
  room_nodes_[next_room_id]->setPlayer(std::move(player));
  // detach a previous room
  auto prev_room = scene_graph_.detachChild(*room_nodes_[curr_room_id_]);
  room_storage_[curr_room_id_] = std::move(prev_room);
  // attach a new room
  auto new_room = std::move(room_storage_[next_room_id]);
  scene_graph_.attachChild(std::move(new_room));

  curr_room_id_ = next_room_id;
}

void RoomManager::checkDoorInteraction() {
  RoomNode* curr_room = room_nodes_[curr_room_id_];
  auto result = curr_room->CheckDoorInteraction();
  if (std::holds_alternative<std::monostate>(result)) return;
  if (std::holds_alternative<ConnectionType>(result)) {
    auto connection = std::get<ConnectionType>(result);
    createConnectionTo(connection);
    checkDoorInteraction();
  } else {
    changeRoomTo(std::get<std::size_t>(result));
  }
}

const std::vector<sf::FloatRect>& RoomManager::getCurrentRoomWalls()
    const noexcept {
  return walls_;
}

std::size_t RoomManager::createRandomRoom() {
  static const std::size_t fixed_seed = 500;
  static std::mt19937 gen(fixed_seed);
  static std::uniform_int_distribution<> randomizer(0, kRoomCount - 1);
  std::size_t room_type_id = 0;
  while (room_type_id == curr_room_id_) {
    room_type_id = randomizer(gen);
  }

  return createRoom(room_type_id);
}

std::size_t RoomManager::createRoom(std::size_t room_type_id) {
  fmt::println("New room id: {}", room_type_id);
  const auto texture_type = static_cast<Textures>(room_type_id);

  auto room_id = rooms_count_++;
  auto room = std::make_unique<RoomNode>(
      NodeCategory::kRoom, textures_, textures_.get(texture_type),
      world_bounds_, room_id, walls_, wall_thickness_);
  room_nodes_.push_back(room.get());
  room_storage_.push_back(std::move(room));

  return room_id;
}

void RoomManager::createConnectionTo(ConnectionType connection) {
  auto random_room_id = createRandomRoom();
  room_nodes_[curr_room_id_]->createConnection(random_room_id, connection);
  room_nodes_[random_room_id]->createConnection(curr_room_id_,
                                                getMirrorType(connection));
}

}  // namespace ink
