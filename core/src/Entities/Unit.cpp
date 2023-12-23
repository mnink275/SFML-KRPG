#include <Entities/Unit.hpp>

#include <Combat/Projectile.hpp>
#include <Components/Combat/CombatComponent.hpp>
#include <Components/Graphics/GraphicsComponent.hpp>
#include <Components/Input/InputComponent.hpp>
#include <Components/Physics/PhysicsComponent.hpp>
#include <Resource/ResourceHolder.hpp>
#include <Room/RoomManager.hpp>

namespace ink {

namespace {

struct DoorInteractionCommand final {
  void operator()(RoomManager& room_manager, sf::Time /*dt*/) const {
    room_manager.checkDoorInteraction();
  }
};

}  // namespace

Unit::Unit(ComponentManager manager, const FontHolder& fonts,
           NodeCategory category, Owner owner)
    : GameObject(std::move(manager), category),
      fonts_(fonts),
      owner_(owner),
      interacted_with_door_(false) {
  manager_.setCommandQueue(&command_queue_);
  fire_command_.category = NodeCategory::kRoom;
  fire_command_.action = [this](SceneNode& node, sf::Time) {
    auto combat = manager_.findComponent<component::CombatComponent>();
    auto graphics = manager_.findComponent<component::GraphicsComponent>();
    combat->onAttack(node, getPosition(), graphics->eyes_direction);
  };

  door_interaction_command_.category = NodeCategory::kRoomManager;
  door_interaction_command_.action =
      SendTo<RoomManager>(DoorInteractionCommand{});
}

void Unit::handleInput(CommandQueue<NodeCommand>& commands,
                       const sf::Keyboard::Key key, const bool is_pressed) {
  auto input = manager_.findComponent<component::InputComponent>();
  input->handleInput(commands, key, is_pressed);
}

Owner Unit::GetOwnerType() const noexcept { return owner_; }

void Unit::selfDamage(std::size_t value) {
  auto combat = manager_.findComponent<component::CombatComponent>();
  if (combat->health <= value) {
    destroy();
  } else {
    combat->health -= value;
  }
}

void Unit::selfHeal(std::size_t value) {
  auto combat = manager_.findComponent<component::CombatComponent>();
  combat->health += value;
}

void Unit::enableDoorInteraction(bool interact_with) noexcept {
  interacted_with_door_ = interact_with;
}

void Unit::handleRealtimeInput(sf::Time dt,
                               CommandQueue<NodeCommand>& commands) {
  auto input = manager_.findComponent<component::InputComponent>();
  input->handleRealtimeInput(dt, commands);
}

void Unit::drawCurrent(sf::RenderTarget& target,
                       const sf::RenderStates states) const {
  auto graphics = manager_.findComponent<component::GraphicsComponent>();
  graphics->draw(target, states);

  // TODO: move to InfoComponent
  auto combat = manager_.findComponent<component::CombatComponent>();
  const std::size_t text_size = 25;
  sf::Text health_amount{fonts_.get(Fonts::kExpressway),
                         "HP: " + std::to_string(combat->health), text_size};
  target.draw(health_amount, states);
}

void Unit::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) {
  // Stage 1: actions handling via sending ComponentCommands
  handleRealtimeInput(dt, commands);

  auto combat = manager_.findComponent<component::CombatComponent>();
  if (combat->isReadyToAttack()) {
    combat->onAttackUpdate();
    commands.push(fire_command_);
  }

  // Stage 2: ComponentCommands processing
  using namespace std::placeholders;
  command_queue_.handle(
      [this](const auto& command, sf::Time time) {
        manager_.onCommand(command, time);
      },
      dt);

  // Stage 3: updates using new information
  auto graphics = manager_.findComponent<component::GraphicsComponent>();
  graphics->update(dt);

  auto physics = manager_.findComponent<component::PhysicsComponent>();
  auto transforms = physics->getTransform(dt);
  Transformable::move(transforms);

  combat->update(dt);

  if (interacted_with_door_) {
    interacted_with_door_ = false;
    commands.push(door_interaction_command_);
  }
};

}  // namespace ink
