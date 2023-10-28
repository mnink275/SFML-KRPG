#include <Components/MouseKeyboardInput.hpp>

#include <iostream>

#include <Commands/SwapPlayerTextureCommand.hpp>
#include <Commands/VelocityDiffCommand.hpp>
#include <Entities/GameObject.hpp>

namespace ink::component {

void MouseKeyboardInput::handlePlayerInput(GameObject* object,
                                           const sf::Keyboard::Key key,
                                           const bool is_pressed) {
  static constexpr float kPlayerVelocityShift = 400.f;

  float velocity_diff = 0.f;
  switch (key) {
    case sf::Keyboard::Key::A:
      if (is_pressed) velocity_diff = -kPlayerVelocityShift;
      object->execute(
          std::make_unique<VelocityDiffCommand>(velocity_diff, key));
      object->execute(std::make_unique<SwapPlayerTextureCommand>(false));
      break;
    case sf::Keyboard::Key::D:
      if (is_pressed) velocity_diff = kPlayerVelocityShift;
      object->execute(
          std::make_unique<VelocityDiffCommand>(velocity_diff, key));
      object->execute<SwapPlayerTextureCommand>(
          std::make_unique<SwapPlayerTextureCommand>(true));
      break;
    case sf::Keyboard::Key::W:
      if (is_pressed) velocity_diff = -kPlayerVelocityShift;
      object->execute(
          std::make_unique<VelocityDiffCommand>(velocity_diff, key));
      break;
    case sf::Keyboard::Key::S:
      if (is_pressed) velocity_diff = kPlayerVelocityShift;
      object->execute(
          std::make_unique<VelocityDiffCommand>(velocity_diff, key));
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
