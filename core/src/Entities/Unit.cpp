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
  void operator()(RoomManager& room_manager, sf::Time) const {
    room_manager.checkDoorInteraction();
  }
};

}  // namespace

Unit::Unit(ComponentManager manager, const FontHolder& fonts,
           NodeCategory category, OwnerType owner)
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

OwnerType Unit::GetOwnerType() const noexcept { return owner_; }

void Unit::selfDamage(int value) {
  auto combat = manager_.findComponent<component::CombatComponent>();
  combat->health -= value;
  if (combat->health <= 0) destroy();
}

void Unit::selfHeal(int value) {
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
  sf::Text health_amount{fonts_.get(Fonts::kExpressway),
                         "HP: " + std::to_string(combat->health), 25};
  target.draw(health_amount, states);
}

void Unit::updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) {
  handleRealtimeInput(dt, commands);
  auto graphics = manager_.findComponent<component::GraphicsComponent>();
  graphics->update(dt);

  while (!command_queue_.isEmpty()) {
    auto command = command_queue_.pop();
    manager_.onCommand(command, dt);
  }

  auto physics = manager_.findComponent<component::PhysicsComponent>();
  auto transforms = physics->getTransform(dt);
  Transformable::move(transforms);

  auto combat = manager_.findComponent<component::CombatComponent>();
  combat->updateTimeSineLastAttack(dt);
  if (combat->is_attacking) {
    combat->is_attacking = false;
    commands.push(fire_command_);
  }

  if (interacted_with_door_) {
    interacted_with_door_ = false;
    commands.push(door_interaction_command_);
  }
};

}  // namespace ink
