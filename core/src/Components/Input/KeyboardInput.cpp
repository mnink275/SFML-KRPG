#include <Components/Input/KeyboardInput.hpp>

#include <iostream>

#include <Components/Collision/CollisionComponent.hpp>
#include <Components/Combat/CombatComponent.hpp>
#include <Components/Graphics/GraphicsComponent.hpp>
#include <Components/Physics/PhysicsComponent.hpp>

namespace ink::component {

namespace {

struct MoveCommand final {
  MoveCommand(sf::Vector2f multipliers) : multipliers(multipliers) {}

  void operator()(component::PhysicsComponent& physics, sf::Time) const {
    static constexpr float kPlayerVelocityShift = 400.f;
    physics.velocity += multipliers * kPlayerVelocityShift;
  }

  sf::Vector2f multipliers;
};

struct FireCommand final {
  void operator()(component::CombatComponent& combat, sf::Time) const {
    combat.is_attacking = true;
  }
};

struct BodyRotationCommand final {
  BodyRotationCommand(EyesDirection eyes_direction)
      : eyes_direction(eyes_direction) {}

  void operator()(component::GraphicsComponent& graphics, sf::Time) const {
    graphics.eyes_direction = eyes_direction;
  }

  EyesDirection eyes_direction;
};

struct EnableInteractionCommand final {
  EnableInteractionCommand(bool interact_with) : interact_with(interact_with) {}

  void operator()(component::CollisionComponent& collision, sf::Time) const {
    collision.interact_with = interact_with;
  }

  bool interact_with;
};

}  // namespace

KeyboardInput::KeyboardInput() {
  // TODO: get rid of repetition: ComponentCategory + PhysicsComponent
  createCommand(sf::Keyboard::A, ComponentCategory::kPhysics,
                SendTo<PhysicsComponent>(MoveCommand{{-1.f, 0.f}}));
  createCommand(
      sf::Keyboard::A, ComponentCategory::kGraphics,
      SendTo<GraphicsComponent>(BodyRotationCommand{EyesDirection::kLeft}));

  createCommand(sf::Keyboard::D, ComponentCategory::kPhysics,
                SendTo<PhysicsComponent>(MoveCommand{{1.f, 0.f}}));
  createCommand(
      sf::Keyboard::D, ComponentCategory::kGraphics,
      SendTo<GraphicsComponent>(BodyRotationCommand{EyesDirection::kRight}));

  createCommand(sf::Keyboard::W, ComponentCategory::kPhysics,
                SendTo<PhysicsComponent>(MoveCommand{{0.f, -1.f}}));

  createCommand(sf::Keyboard::S, ComponentCategory::kPhysics,
                SendTo<PhysicsComponent>(MoveCommand{{0.f, 1.f}}));

  createCommand(sf::Keyboard::Space, ComponentCategory::kCombat,
                SendTo<CombatComponent>(FireCommand{}));
}

void KeyboardInput::handleInput(CommandQueue<NodeCommand>& /*command_queue*/,
                                const sf::Keyboard::Key key,
                                const bool is_pressed) {
  if (isRealtimeAction(key)) return;

  switch (key) {
    case sf::Keyboard::Key::E: {
      // TODO: move to component fields
      ComponentCommand command;
      command.category = ComponentCategory::kCollision;
      command.action =
          SendTo<CollisionComponent>(EnableInteractionCommand{is_pressed});
      sendCommand(command);
      break;
    }
    default: {
      std::cout << "The key isn't implemented!\n";
    }
  }
}

void KeyboardInput::handleRealtimeInput(
    sf::Time /*dt*/, CommandQueue<NodeCommand>& /*commands*/) {
  for (auto&& [key, command_list] : commands_) {
    if (!isRealtimeAction(key) || !sf::Keyboard::isKeyPressed(key)) continue;
    for (auto&& command : command_list) sendCommand(command);
  }
}

bool KeyboardInput::isRealtimeAction(sf::Keyboard::Key key) const noexcept {
  switch (key) {
    case sf::Keyboard::Key::A:
    case sf::Keyboard::Key::D:
    case sf::Keyboard::Key::W:
    case sf::Keyboard::Key::S:
    case sf::Keyboard::Key::Space:
      return true;
    default:
      return false;
  }
}

}  // namespace ink::component
