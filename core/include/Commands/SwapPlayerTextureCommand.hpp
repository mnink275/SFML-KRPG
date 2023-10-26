#pragma once

#include <Commands/GraphicsCommand.hpp>
#include <Components/PlayerGraphics.hpp>

namespace ink {

class SwapPlayerTextureCommand final : public GraphicsCommand {
 public:
  SwapPlayerTextureCommand(bool is_turned_right);

  void execute(
      component::GraphicsComponent* graphics_base) const noexcept override;

 public:
  bool is_turned_right_;
};

}  // namespace ink
