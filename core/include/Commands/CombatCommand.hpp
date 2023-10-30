#pragma once

#include <Commands/Command.hpp>
#include <Components/CombatComponent.hpp>

namespace ink {

class CombatCommand : public Command {
 public:
  virtual ~CombatCommand() = default;
  void virtual execute(component::CombatComponent* physics) const noexcept = 0;
};

}  // namespace ink
