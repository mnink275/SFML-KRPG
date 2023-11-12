#include <Components/Input/AIKeyboardInput.hpp>

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

struct StateChangeCommand final {
  StateChangeCommand(ObjectState object_state) : object_state(object_state) {}

  void operator()(component::GraphicsComponent& graphics, sf::Time) const {
    graphics.object_state = object_state;
  }

  ObjectState object_state;
};

struct EyesDirectionChangeCommand final {
  EyesDirectionChangeCommand(EyesDirection eyes_direction)
      : eyes_direction(eyes_direction) {}

  void operator()(component::GraphicsComponent& graphics, sf::Time) const {
    graphics.eyes_direction = eyes_direction;
  }

  EyesDirection eyes_direction;
};

}  // namespace

AIKeyboardInput::AIKeyboardInput() {
  createCommand(sf::Keyboard::A, ComponentCategory::kPhysics,
                SendTo<PhysicsComponent>(MoveCommand{{-1.f, 0.f}}));
  createCommand(
      sf::Keyboard::A, ComponentCategory::kGraphics,
      SendTo<GraphicsComponent>(StateChangeCommand{ObjectState::kMoving}));
  createCommand(sf::Keyboard::A, ComponentCategory::kGraphics,
                SendTo<GraphicsComponent>(
                    EyesDirectionChangeCommand{EyesDirection::kLeft}));

  createCommand(sf::Keyboard::D, ComponentCategory::kPhysics,
                SendTo<PhysicsComponent>(MoveCommand{{1.f, 0.f}}));
  createCommand(
      sf::Keyboard::D, ComponentCategory::kGraphics,
      SendTo<GraphicsComponent>(StateChangeCommand{ObjectState::kMoving}));
  createCommand(sf::Keyboard::D, ComponentCategory::kGraphics,
                SendTo<GraphicsComponent>(
                    EyesDirectionChangeCommand{EyesDirection::kRight}));

  createCommand(sf::Keyboard::W, ComponentCategory::kPhysics,
                SendTo<PhysicsComponent>(MoveCommand{{0.f, -1.f}}));
  createCommand(
      sf::Keyboard::W, ComponentCategory::kGraphics,
      SendTo<GraphicsComponent>(StateChangeCommand{ObjectState::kMoving}));

  createCommand(sf::Keyboard::S, ComponentCategory::kPhysics,
                SendTo<PhysicsComponent>(MoveCommand{{0.f, 1.f}}));
  createCommand(
      sf::Keyboard::S, ComponentCategory::kGraphics,
      SendTo<GraphicsComponent>(StateChangeCommand{ObjectState::kMoving}));

  createCommand(sf::Keyboard::Space, ComponentCategory::kCombat,
                SendTo<CombatComponent>(FireCommand{}));
}

void AIKeyboardInput::handleInput(CommandQueue<NodeCommand>& /*command_queue*/,
                                  const sf::Keyboard::Key /*key*/,
                                  const bool /*is_pressed*/) {}

void AIKeyboardInput::handleRealtimeInput(
    sf::Time dt, CommandQueue<NodeCommand>& /*commands*/) {
  static auto kIdleInterval = sf::seconds(2.f);
  static auto kMoveInterval = sf::seconds(1.f);
  static auto timer = sf::Time::Zero;
  timer += dt;
  switch (state) {
    case State::kIdle:
      if (timer > kIdleInterval) {
        timer -= kIdleInterval;
        state = State::kMoveDown;
      }
      break;
    case State::kMoveDown:
      if (timer > kMoveInterval) {
        timer -= kMoveInterval;
        state = State::kMoveRight;
      }
      for (auto&& command : commands_[sf::Keyboard::S]) sendCommand(command);
      break;
    case State::kMoveRight:
      if (timer > kMoveInterval) {
        timer -= kMoveInterval;
        state = State::kMoveUp;
      }
      for (auto&& command : commands_[sf::Keyboard::D]) sendCommand(command);
      break;
    case State::kMoveUp:
      if (timer > kMoveInterval) {
        timer -= kMoveInterval;
        state = State::kMoveLeft;
      }
      for (auto&& command : commands_[sf::Keyboard::W]) sendCommand(command);
      break;
    case State::kMoveLeft:
      if (timer > kMoveInterval) {
        timer -= kMoveInterval;
        state = State::kIdle;
      }
      for (auto&& command : commands_[sf::Keyboard::A]) sendCommand(command);
      break;
  }
}

}  // namespace ink::component
