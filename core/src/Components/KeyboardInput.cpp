#include <Components/KeyboardInput.hpp>

#include <iostream>

#include <Commands/Command.hpp>
#include <Components/CombatComponent.hpp>
#include <Components/GraphicsComponent.hpp>
#include <Components/PhysicsComponent.hpp>

namespace ink::component {

namespace {

struct PlayerMoveCommand final {
  PlayerMoveCommand(sf::Keyboard::Key key, bool is_pressed)
      : key(key), is_pressed(is_pressed) {}

  void operator()(component::PhysicsComponent& physics, sf::Time) const {
    static constexpr float kPlayerVelocityShift = 400.f;
    float velocity_diff = 0.f;
    if (is_pressed) velocity_diff = kPlayerVelocityShift;
    switch (key) {
      case sf::Keyboard::Key::A:
        physics.velocity.to_left_ = velocity_diff;
        break;
      case sf::Keyboard::Key::D:
        physics.velocity.to_right_ = velocity_diff;
        break;
      case sf::Keyboard::Key::W:
        physics.velocity.to_up_ = velocity_diff;
        break;
      case sf::Keyboard::Key::S:
        physics.velocity.to_down_ = velocity_diff;
        break;
      default:
        std::cout << "Error in PlayerMoveCommand: only WASD keys allowed\n";
        assert(false);
    }
  }

  sf::Keyboard::Key key;
  bool is_pressed;
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
  // TODO: create key binding
  player_move_.category = static_cast<CategoryType>(Category::kPhysic);

  player_fire_.category = static_cast<CategoryType>(Category::kCombat);
  player_fire_.action = SendTo<component::CombatComponent>(PlayerFireCommand{});

  player_body_rotation_.category =
      static_cast<CategoryType>(Category::kGraphic);
}

void KeyboardInput::handlePlayerInput(
    CommandQueue<NodeCommand>& /*command_queue*/, const sf::Keyboard::Key key,
    const bool is_pressed) {
  switch (key) {
    case sf::Keyboard::Key::A:
      player_move_.action = SendTo<component::PhysicsComponent>(
          PlayerMoveCommand{key, is_pressed});
      sendCommand(player_move_);

      player_body_rotation_.action = SendTo<component::GraphicsComponent>(
          PlayerBodyRotationCommand{EyesDirection::kLeft});
      sendCommand(player_body_rotation_);
      break;
    case sf::Keyboard::Key::D:
      player_move_.action = SendTo<component::PhysicsComponent>(
          PlayerMoveCommand{key, is_pressed});
      sendCommand(player_move_);

      player_body_rotation_.action = SendTo<component::GraphicsComponent>(
          PlayerBodyRotationCommand{EyesDirection::kRight});
      sendCommand(player_body_rotation_);
      break;
    case sf::Keyboard::Key::W:
      player_move_.action = SendTo<component::PhysicsComponent>(
          PlayerMoveCommand{key, is_pressed});
      sendCommand(player_move_);
      break;
    case sf::Keyboard::Key::S:
      player_move_.action = SendTo<component::PhysicsComponent>(
          PlayerMoveCommand{key, is_pressed});
      sendCommand(player_move_);
      break;
    case sf::Keyboard::Key::F:
      sendCommand(player_fire_);
      break;
    // case sf::Keyboard::Key::E:
    //   interact_with_ = is_pressed;
    //   break;
    default:
      std::cout << "The key isn't implemented!\n";
  }
}

}  // namespace ink::component
