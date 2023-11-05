#include <Components/KeyboardInput.hpp>

#include <iostream>

#include <Commands/Command.hpp>
#include <Components/CombatComponent.hpp>
#include <Components/GraphicsComponent.hpp>
#include <Components/PhysicsComponent.hpp>

namespace ink::component {

namespace {

struct PlayerMoveCommand final {
  PlayerMoveCommand(sf::Vector2f multipliers) : multipliers(multipliers) {}

  void operator()(component::PhysicsComponent& physics, sf::Time) const {
    static constexpr float kPlayerVelocityShift = 400.f;
    physics.velocity += multipliers * kPlayerVelocityShift;
  }

  sf::Vector2f multipliers;
};

struct StopMoveCommand final {
  void operator()(component::PhysicsComponent& physics, sf::Time) const {
    physics.velocity = {0, 0};
  }
};

struct PlayerFireCommand final {
  void operator()(component::CombatComponent& combat, sf::Time) const {
    combat.is_attacking = true;
  }
};

struct PlayerBodyRotationCommand final {
  PlayerBodyRotationCommand(EyesDirection eyes_direction)
      : eyes_direction(eyes_direction) {}

  void operator()(component::GraphicsComponent& graphics, sf::Time) const {
    graphics.eyes_direction = eyes_direction;
  }

  EyesDirection eyes_direction;
};

}  // namespace

KeyboardInput::KeyboardInput() {
  createCommand(sf::Keyboard::A, ComponentCategory::kPhysic,
                SendTo<PhysicsComponent>(PlayerMoveCommand{{-1.f, 0.f}}));
  createCommand(sf::Keyboard::A, ComponentCategory::kGraphic,
                SendTo<GraphicsComponent>(
                    PlayerBodyRotationCommand{EyesDirection::kLeft}));

  createCommand(sf::Keyboard::D, ComponentCategory::kPhysic,
                SendTo<PhysicsComponent>(PlayerMoveCommand{{1.f, 0.f}}));
  createCommand(sf::Keyboard::D, ComponentCategory::kGraphic,
                SendTo<GraphicsComponent>(
                    PlayerBodyRotationCommand{EyesDirection::kRight}));

  createCommand(sf::Keyboard::W, ComponentCategory::kPhysic,
                SendTo<PhysicsComponent>(PlayerMoveCommand{{0.f, -1.f}}));

  createCommand(sf::Keyboard::S, ComponentCategory::kPhysic,
                SendTo<PhysicsComponent>(PlayerMoveCommand{{0.f, 1.f}}));

  createCommand(sf::Keyboard::Space, ComponentCategory::kCombat,
                SendTo<CombatComponent>(PlayerFireCommand{}));

  stop_.category = ComponentCategory::kPhysic;
  stop_.action = SendTo<PhysicsComponent>(StopMoveCommand{});
}

void KeyboardInput::handleInput(CommandQueue<NodeCommand>& /*command_queue*/,
                                const sf::Keyboard::Key key,
                                const bool /*is_pressed*/) {
  if (isRealtimeAction(key)) return;

  switch (key) {
    // case sf::Keyboard::Key::E:
    //   interact_with_ = is_pressed;
    //   break;
    default:
      std::cout << "The key isn't implemented!\n";
  }
}

void KeyboardInput::handleRealtimeInput(
    CommandQueue<NodeCommand>& /*commands*/) {
  sendCommand(stop_);
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

void KeyboardInput::createCommand(sf::Keyboard::Key key,
                                  ComponentCommand::Receiver receiver_category,
                                  ComponentCommand::Action action) {
  commands_[key].emplace_back(receiver_category, action);
}

}  // namespace ink::component
