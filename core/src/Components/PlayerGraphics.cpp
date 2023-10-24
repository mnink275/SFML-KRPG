#include <Components/PlayerGraphics.hpp>

namespace ink::component {

PlayerGraphics::PlayerGraphics(const sf::Texture& texture) : sprite_(texture) {}

void PlayerGraphics::draw(sf::RenderTarget& target,
                          const sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace ink::component
