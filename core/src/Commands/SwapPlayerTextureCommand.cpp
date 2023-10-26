#include <Commands/SwapPlayerTextureCommand.hpp>

namespace ink {

SwapPlayerTextureCommand::SwapPlayerTextureCommand(bool is_turned_right)
    : is_turned_right_(is_turned_right) {}

void SwapPlayerTextureCommand::execute(
    component::GraphicsComponent* graphics_base) const noexcept {
  auto* graphics = static_cast<component::PlayerGraphics*>(graphics_base);
  graphics->is_turned_right = is_turned_right_;
}

}  // namespace ink
