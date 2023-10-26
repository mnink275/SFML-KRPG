#pragma once

#include <Commands/Command.hpp>
#include <Components/PhysicsComponent.hpp>

namespace ink {

class PhysicsCommand : public Command {
 public:
  virtual ~PhysicsCommand() = default;
  void virtual execute(component::PhysicsComponent* physics) const noexcept = 0;
};

}  // namespace ink
