#pragma once

#include <Commands/GraphicsCommand.hpp>
#include <Components/PlayerGraphics.hpp>

namespace ink {

class SwapPlayerTextureCommand final : public GraphicsCommand {
 public:
  SwapPlayerTextureCommand(bool is_turned_right)
      : is_turned_right_(is_turned_right) {}

  void execute(component::GraphicsComponent* graphics_base) override {
    auto* graphics = static_cast<component::PlayerGraphics*>(graphics_base);
    graphics->is_turned_right = is_turned_right_;
  }

 public:
  bool is_turned_right_;
};

}  // namespace ink
