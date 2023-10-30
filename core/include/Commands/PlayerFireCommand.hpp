#pragma once

#include <SFML/Window/Event.hpp>

#include <Commands/CombatCommand.hpp>
#include <Components/PlayerCombat.hpp>

namespace ink::component {

class PlayerFireCommand final : public CombatCommand {
 public:
  PlayerFireCommand(sf::Keyboard::Key key, bool is_pressed,
                    const sf::Vector2f& owner_position)
      : key_(key), is_pressed_(is_pressed), owner_position_(owner_position) {}

  ~PlayerFireCommand() override = default;

  void execute(
      component::CombatComponent* combat_base) const noexcept override {
    auto* combat = static_cast<component::PlayerCombat*>(combat_base);
    combat->onAttack(owner_position_);
  }

 private:
  sf::Keyboard::Key key_;
  bool is_pressed_;
  const sf::Vector2f& owner_position_;
};

}  // namespace ink::component
