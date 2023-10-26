#pragma once

#include <Components/PhysicsComponent.hpp>
#include <Commands/Command.hpp>

namespace ink {

class PhysicsCommand : public Command {
 public:
  virtual ~PhysicsCommand() = default;
  void virtual execute(component::PhysicsComponent* physics) = 0;
};

}  // namespace ink
