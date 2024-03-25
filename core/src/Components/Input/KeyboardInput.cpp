#include <Components/Input/KeyboardInput.hpp>

#include <fmt/format.h>

#include <Components/Collision/CollisionComponent.hpp>
#include <Components/Combat/CombatComponent.hpp>
#include <Components/Graphics/GraphicsComponent.hpp>
#include <Components/Physics/PhysicsComponent.hpp>

namespace ink::component {

namespace {

struct MoveCommand final {
  explicit MoveCommand(sf::Vector2f multipliers) : multipliers(multipliers) {}

  void operator()(component::PhysicsComponent& physics, sf::Time /*dt*/) const {
    static constexpr float kPlayerVelocityShift = 400.f;
    physics.velocity += multipliers * kPlayerVelocityShift;
  }

  sf::Vector2f multipliers;
};

struct FireCommand final {
  void operator()(component::CombatComponent& combat, sf::Time /*dt*/) const {
    combat.attack_requested = true;
  }
};

struct StateChangeCommand final {
  explicit StateChangeCommand(ObjectState object_state)
      : object_state(object_state) {}

  void operator()(component::GraphicsComponent& graphics,
                  sf::Time /*dt*/) const {
    graphics.setObjectState(object_state);
  }

  ObjectState object_state;
};

struct EyesDirectionChangeCommand final {
  explicit EyesDirectionChangeCommand(EyesDirection eyes_direction)
      : eyes_direction(eyes_direction) {}

  void operator()(component::GraphicsComponent& graphics,
                  sf::Time /*dt*/) const {
    graphics.eyes_direction = eyes_direction;
  }

  EyesDirection eyes_direction;
};

struct EnableInteractionCommand final {
  explicit EnableInteractionCommand(bool interact_with)
      : interact_with(interact_with) {}

  void operator()(component::CollisionComponent& collision,
                  sf::Time /*dt*/) const {
    collision.interact_with = interact_with;
  }

  bool interact_with;
};

}  // namespace

KeyboardInput::KeyboardInput() {
  ForKey(sf::Keyboard::A)
      .BindCommandTo<PhysicsComponent>(MoveCommand{{-1.f, 0.f}})
      .BindCommandTo<GraphicsComponent>(
          StateChangeCommand{ObjectState::kMoving})
      .BindCommandTo<GraphicsComponent>(
          EyesDirectionChangeCommand{EyesDirection::kLeft});

  ForKey(sf::Keyboard::D)
      .BindCommandTo<PhysicsComponent>(MoveCommand{{1.f, 0.f}})
      .BindCommandTo<GraphicsComponent>(
          StateChangeCommand{ObjectState::kMoving})
      .BindCommandTo<GraphicsComponent>(
          EyesDirectionChangeCommand{EyesDirection::kRight});

  ForKey(sf::Keyboard::W)
      .BindCommandTo<PhysicsComponent>(MoveCommand{{0.f, -1.f}})
      .BindCommandTo<GraphicsComponent>(
          StateChangeCommand{ObjectState::kMoving});

  ForKey(sf::Keyboard::S)
      .BindCommandTo<PhysicsComponent>(MoveCommand{{0.f, 1.f}})
      .BindCommandTo<GraphicsComponent>(
          StateChangeCommand{ObjectState::kMoving});

  ForKey(sf::Keyboard::Space).BindCommandTo<CombatComponent>(FireCommand{});

  do_idle_.category = ComponentCategory::kGraphics;
  do_idle_.action =
      SendTo<GraphicsComponent>(StateChangeCommand{ObjectState::kIdle});
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
      fmt::println("The key isn't implemented!");
    }
  }
}

void KeyboardInput::handleRealtimeInput(
    sf::Time /*dt*/, CommandQueue<NodeCommand>& /*commands*/) {
  // idle if move commands (WASD) haven't been pressed
  sendCommand(do_idle_);

  for (auto&& [key, command_list] : commands_) {
    if (!isRealtimeAction(key) || !sf::Keyboard::isKeyPressed(key)) continue;
    for (auto&& command : command_list) sendCommand(command);
  }
}

bool KeyboardInput::isRealtimeAction(sf::Keyboard::Key key) noexcept {
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
