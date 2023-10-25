#include <Components/MouseKeyboardInput.hpp>

#include <iostream>

namespace ink::component {

void MouseKeyboardInput::handlePlayerInput(const sf::Keyboard::Key key,
                                           const bool is_pressed,
                                           VelocityModule& velocity) {
  static constexpr float kPlayerVelocityShift = 400.f;

  float velocity_diff = 0.f;
  switch (key) {
    case sf::Keyboard::Key::A:
      if (is_pressed) velocity_diff = -kPlayerVelocityShift;
      velocity.to_left_ = velocity_diff;
      break;
    case sf::Keyboard::Key::D:
      if (is_pressed) velocity_diff = kPlayerVelocityShift;
      velocity.to_right_ = velocity_diff;
      break;
    case sf::Keyboard::Key::W:
      if (is_pressed) velocity_diff = -kPlayerVelocityShift;
      velocity.to_up_ = velocity_diff;
      break;
    case sf::Keyboard::Key::S:
      if (is_pressed) velocity_diff = kPlayerVelocityShift;
      velocity.to_down_ = velocity_diff;
      break;
    // case sf::Keyboard::Key::E:
    //   interact_with_ = is_pressed;
    //   break;
    // case sf::Keyboard::Key::F:
    //   player_->OnAttack();
    //   break;
    default:
      std::cout << "The key isn't implemented!\n";
  }
}

}  // namespace ink::component
