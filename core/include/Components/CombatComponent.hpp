#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <Entities/VelocityModule.hpp>

namespace ink::component {

class CombatComponent {
 public:
  virtual ~CombatComponent() = default;

  virtual void onAttack(const sf::Vector2f& owner_position) = 0;
};

}  // namespace ink::component
