#pragma once

#include <Commands/Command.hpp>
#include <Components/GraphicsComponent.hpp>

namespace ink {

class GraphicsCommand : public Command {
 public:
  virtual ~GraphicsCommand() = default;
  void virtual execute(component::GraphicsComponent* physics) = 0;
};

}  // namespace ink
